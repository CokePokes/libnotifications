//
//  main.m
//  libnotificationdaemon
//
//  Created by CokePokes on 8/3/19.
//  Copyright (c) 2019 ___ORGANIZATIONNAME___. All rights reserved.
//

// XPC Service: Lightweight helper tool that performs work on behalf of an application.
// see http://developer.apple.com/library/mac/#documentation/MacOSX/Conceptual/BPSystemStartup/Chapters/CreatingXPCServices.html

#include <xpc/xpc.h>
#include <Foundation/Foundation.h>
#include <dlfcn.h>
#include <objc/objc-runtime.h>

#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>
#import "NSDictionary+CDXPC.h"
#import "Headers.h"

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[objc_getClass("UIDevice") currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[objc_getClass("UIDevice") currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[objc_getClass("UIDevice") currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[objc_getClass("UIDevice") currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[objc_getClass("UIDevice") currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

#define CPLog(fmt, ...) NSLog((@"\e[4#1mlibnotificationd\e[m \E[3#2m[Line %d]:\e[m " fmt), __LINE__, ##__VA_ARGS__);

extern mach_port_t SBSSpringBoardServerPort();

static void showNotificationWithXPCObject(xpc_object_t object) {
    
    NSDictionary *dic = [NSDictionary dictionaryWithXPCObject:object];
    
    NSString *title = [dic objectForKey:@"title"];
    NSString *message = [dic objectForKey:@"message"];
    NSDictionary *userInfo = [dic objectForKey:@"userInfo"];
    NSNumber *badgeCount = [dic objectForKey:@"badgeCount"];
    NSString *soundName = [dic objectForKey:@"soundName"];
    NSString *bundleId = [dic objectForKey:@"bundleId"];
    double delay = [[dic objectForKey:@"delay"] doubleValue];
    BOOL repeats = [[dic objectForKey:@"repeats"] boolValue];


    BOOL shouldDelay = NO; //taken from CReporter
    mach_port_t port;
    while ((port = SBSSpringBoardServerPort()) == 0) {
        [NSThread sleepForTimeInterval:1.0];
        shouldDelay = YES;
    }
    
    if (shouldDelay) { //taken from CReporter
        // Wait serveral seconds to give time for SpringBoard to finish launching.
        // FIXME: This is needed due to issue mentioned above. The time
        //        interval was chosen arbitrarily and may not be long enough
        //        in some cases.
        [NSThread sleepForTimeInterval:20.0];
    }
    
    void *uikitHandle = dlopen("/System/Library/Frameworks/UIKit.framework/UIKit", RTLD_LAZY);
    if (uikitHandle != NULL) {
        
        UILocalNotification *notification = [objc_getClass("UILocalNotification") new];
        [notification setAlertTitle:title];
        [notification setAlertBody:message];
        [notification setUserInfo:userInfo];
        [notification setApplicationIconBadgeNumber:badgeCount.integerValue];
        [notification setSoundName:soundName];
        [notification setHasAction:YES];
        [notification setAlertAction:nil];
        
        if ([objc_getClass("SBSLocalNotificationClient") respondsToSelector:@selector(scheduleLocalNotification:bundleIdentifier:)]) //less than iOS9
        {
            [objc_getClass("SBSLocalNotificationClient") scheduleLocalNotification:notification
                                                                  bundleIdentifier:bundleId];
            dlclose(uikitHandle); return;
        }
        
        if (SYSTEM_VERSION_LESS_THAN(@"10.0")){ // iOS9 - 9.9
            void *userNotiServicesHandle = dlopen("/System/Library/PrivateFrameworks/UserNotificationServices.framework/UserNotificationServices", RTLD_LAZY);
            if (userNotiServicesHandle != NULL) {
                UNSNotificationScheduler *scheduler = [[objc_getClass("UNSNotificationScheduler") alloc] initWithBundleIdentifier:bundleId];
                [scheduler addScheduledLocalNotifications:@[notification] waitUntilDone:YES];
                dlclose(userNotiServicesHandle);
                dlclose(uikitHandle); return;
            }
        }
        
        void *usernotificationsHandle = dlopen("/System/Library/Frameworks/UserNotifications.framework/UserNotifications", RTLD_LAZY);
        if (usernotificationsHandle != NULL) {
            
            LSApplicationProxy *bundleProxy = [objc_getClass("LSApplicationProxy") applicationProxyForIdentifier:bundleId withContext:[objc_getClass("LSContext") currentContext]];

            UNUserNotificationCenter *center = [objc_getClass("UNUserNotificationCenter") alloc]; //currentUserNotificationSettings crashes
            
            if ([center respondsToSelector:@selector(initWithBundleProxy:)]){
                center = [center initWithBundleProxy:bundleProxy];
            } else if ([center respondsToSelector:@selector(initWithBundleIdentifier:)]){ //ios13+
                center = [center initWithBundleIdentifier:bundleId];
            }
            
            UNAuthorizationOptions options = UNAuthorizationOptionAlert|UNAuthorizationOptionSound|UNAuthorizationOptionBadge;
            [center requestAuthorizationWithOptions:options completionHandler:^(BOOL granted, NSError * _Nullable error){
                if(!error){
                    [[objc_getClass("UIApplication") sharedApplication] registerForRemoteNotifications];
                } else {
                    CPLog(@"ERROR: requestAuthorizationWithOptions: %@", error.localizedDescription);
                    void *usernotificationsFactoryHandle = dlopen("/System/Library/PrivateFrameworks/UserNotificationsServer.framework/UserNotificationsServer", RTLD_LAZY);
                    if (usernotificationsFactoryHandle != NULL) {
                        NSString *directory = @"/var/mobile/Library/UserNotifications";
                        FBSSystemService *sbservice = [objc_getClass("FBSSystemService") sharedService];
                        UNSLocationMonitor *locationMon = [[objc_getClass("UNSLocationMonitor") alloc] init];
                        UNSApplicationLauncher *appLauncher = [objc_getClass("UNSApplicationLauncher") alloc];
                        
                        if ([appLauncher respondsToSelector:@selector(initWithSystemService:locationMonitor:)]){
                            appLauncher = [appLauncher initWithSystemService:sbservice locationMonitor:locationMon]; //<=12
                        } else if ([appLauncher respondsToSelector:@selector(initWithLocationMonitor:)]){
                            appLauncher = [appLauncher initWithLocationMonitor:locationMon]; //ios13+
                        }
                        
                        UNSNotificationCategoryRepository *catRepo = [objc_getClass("UNSNotificationCategoryRepository") alloc];
                        if ([catRepo respondsToSelector:@selector(initWithDirectory:librarian:repositoryProtectionStrategy:)]){ //iOS13+
                            UNSBundleLibrarian *bundleLibrarian = [[objc_getClass("UNSBundleLibrarian") alloc] initWithDirectory:directory];
                            UNSFileHandleContentProtectionStrategy *protectionStrat = [[objc_getClass("UNSFileHandleContentProtectionStrategy") alloc] initWithFileProtectionType:NSFileProtectionNone];
                            catRepo = [catRepo initWithDirectory:directory librarian:bundleLibrarian repositoryProtectionStrategy:protectionStrat];
                        } else if ([catRepo respondsToSelector:@selector(initWithDirectory:)]) { //iOS12+
                            catRepo = [catRepo initWithDirectory:directory];
                        } else if ([catRepo respondsToSelector:@selector(init)]) { //<= iOS11
                            catRepo = [catRepo init];
                        }
                    
                        UNSNotificationRepository *notificationRepo = [objc_getClass("UNSNotificationRepository") alloc];
                        if ([notificationRepo respondsToSelector:@selector(initWithDirectory:librarian:repositoryProtectionStrategy:)]){ //iOS13+
                            UNSBundleLibrarian *bundleLibrarian = [[objc_getClass("UNSBundleLibrarian") alloc] initWithDirectory:directory];
                            UNSFileHandleContentProtectionStrategy *protectionStrat = [[objc_getClass("UNSFileHandleContentProtectionStrategy") alloc] initWithFileProtectionType:NSFileProtectionNone];
                            notificationRepo = [notificationRepo initWithDirectory:directory librarian:bundleLibrarian repositoryProtectionStrategy:protectionStrat];
                        } else if ([notificationRepo respondsToSelector:@selector(initWithDirectory:)]) { //iOS12+
                            notificationRepo = [notificationRepo initWithDirectory:directory];
                        } else if ([notificationRepo respondsToSelector:@selector(initWithSystemService:)]) { //<= iOS11
                            notificationRepo = [notificationRepo initWithSystemService:sbservice];
                        }
                        
                        UNSAttachmentsRepository *attachRepo = [objc_getClass("UNSAttachmentsRepository") alloc];
                        if ([attachRepo respondsToSelector:@selector(initWithDirectory:librarian:)]){
                            UNSBundleLibrarian *bundleLibrarian = [[objc_getClass("UNSBundleLibrarian") alloc] initWithDirectory:directory];
                            attachRepo = [attachRepo initWithDirectory:directory librarian:bundleLibrarian];
                        } else if ([attachRepo respondsToSelector:@selector(initWithDirectory:)]) { //iOS12+
                            attachRepo = [attachRepo initWithDirectory:directory];
                        } else if ([attachRepo respondsToSelector:@selector(initWithDirectoryURL:)]) { //<= iOS11
                            attachRepo = [attachRepo initWithDirectoryURL:[NSURL URLWithString:directory]];
                        }
                        
                        UNSPendingNotificationRepository *pendingRepo = [objc_getClass("UNSPendingNotificationRepository") alloc];
                        if ([pendingRepo respondsToSelector:@selector(initWithDirectory:librarian:)]){ //iOS13+
                            UNSBundleLibrarian *bundleLibrarian = [[objc_getClass("UNSBundleLibrarian") alloc] initWithDirectory:directory];
                            UNSFileHandleContentProtectionStrategy *protectionStrat = [[objc_getClass("UNSFileHandleContentProtectionStrategy") alloc] initWithFileProtectionType:NSFileProtectionNone];
                            pendingRepo = [pendingRepo initWithDirectory:directory librarian:bundleLibrarian repositoryProtectionStrategy:protectionStrat];
                        } else if ([pendingRepo respondsToSelector:@selector(initWithDirectory:)]){ //iOS12+
                            pendingRepo = [pendingRepo initWithDirectory:directory];
                        } else if ([pendingRepo respondsToSelector:@selector(init)]) { //<= iOS11
                            pendingRepo = [pendingRepo init];
                        }

                        UNSNotificationSchedulingService *schService = [objc_getClass("UNSNotificationSchedulingService") alloc];
                        if ([schService respondsToSelector:@selector(initWithNotificationRepository:pendingNotificationRepository:notificationScheduleRepository:locationMonitor:)]){ //iOS12+
                            
                            UNSNotificationScheduleRepository *scheduleRepo = [objc_getClass("UNSNotificationScheduleRepository") alloc];
                            if ([scheduleRepo respondsToSelector:@selector(initWithDirectory:librarian:)]){ //iOS13+
                                UNSBundleLibrarian *bundleLibrarian = [[objc_getClass("UNSBundleLibrarian") alloc] initWithDirectory:directory];
                                scheduleRepo = [scheduleRepo initWithDirectory:directory librarian:bundleLibrarian];
                            } else if ([scheduleRepo respondsToSelector:@selector(initWithDirectory:)]){ //<=iOS12
                                scheduleRepo = [scheduleRepo initWithDirectory:directory];
                            }
                            schService = [schService initWithNotificationRepository:notificationRepo pendingNotificationRepository:pendingRepo notificationScheduleRepository:scheduleRepo locationMonitor:locationMon];
                        } else if ([schService respondsToSelector:@selector(initWithNotificationRepository:pendingNotificationRepository:locationMonitor:)]) { //<= iOS11
                            schService = [schService initWithNotificationRepository:notificationRepo pendingNotificationRepository:pendingRepo locationMonitor:locationMon];
                        }
  
                        UNSAttachmentsService *attachService = [objc_getClass("UNSAttachmentsService") alloc];
                        if ([attachService respondsToSelector:@selector(initWithAttachmentsRepository:notificationRepository:notificationSchedulingService:pendingNotificationRepository:)]){ //iOS12+
                            attachService = [attachService initWithAttachmentsRepository:attachRepo notificationRepository:notificationRepo notificationSchedulingService:schService pendingNotificationRepository:pendingRepo];
                        } else if ([attachService respondsToSelector:@selector(initWithNotificationRepository:notificationSchedulingService:pendingNotificationRepository:)]){ //<= iOS11
                            attachService = [attachService initWithNotificationRepository:notificationRepo notificationSchedulingService:schService pendingNotificationRepository:pendingRepo];
                        }
                        
                        UNSDefaultDataProviderFactory *factory = [objc_getClass("UNSDefaultDataProviderFactory") alloc];
                        if ([factory respondsToSelector:@selector(initWithApplicationLauncher:daemonLauncher:categoryRepository:notificationRepository:attachmentsService:topicRepository:localizationService:settingsGateway:)]){ //iOS13+
                            
                            UNSDaemonLauncher *daemonLauncher = [[objc_getClass("UNSDaemonLauncher") alloc] init];
                            UNSNotificationTopicRepository *topicRepo = [objc_getClass("UNSNotificationTopicRepository") alloc];

                            if ([topicRepo respondsToSelector:@selector(initWithDirectory:librarian:repositoryProtectionStrategy:)]){
                                UNSBundleLibrarian *bundleLibrarian = [[objc_getClass("UNSBundleLibrarian") alloc] initWithDirectory:directory];
                                UNSFileHandleContentProtectionStrategy *protectionStrat = [[objc_getClass("UNSFileHandleContentProtectionStrategy") alloc] initWithFileProtectionType:NSFileProtectionNone];
                                topicRepo = [topicRepo initWithDirectory:directory librarian:bundleLibrarian repositoryProtectionStrategy:protectionStrat];
                            } else if ([topicRepo respondsToSelector:@selector(initWithDirectory:)]) {
                                topicRepo = [topicRepo initWithDirectory:directory];
                            }
                            
                            UNSSettingsGateway *settingsGetaway = [[objc_getClass("UNSSettingsGateway") alloc] init];
                            UNSLocalizationService *localService = [[objc_getClass("UNSLocalizationService") alloc] init];
                            
                            factory = [factory initWithApplicationLauncher:appLauncher daemonLauncher:daemonLauncher categoryRepository:catRepo notificationRepository:notificationRepo attachmentsService:attachService topicRepository:topicRepo localizationService:localService settingsGateway:settingsGetaway];
                            
                        } else if ([factory respondsToSelector:@selector(initWithApplicationLauncher:daemonLauncher:categoryRepository:notificationRepository:attachmentsService:topicRepository:)]){ //iOS12+
                            UNSDaemonLauncher *daemonLauncher = [[objc_getClass("UNSDaemonLauncher") alloc] init];
                            UNSNotificationTopicRepository *topicRepo = [[objc_getClass("UNSNotificationTopicRepository") alloc] initWithDirectory:directory];
                            factory = [factory initWithApplicationLauncher:appLauncher daemonLauncher:daemonLauncher categoryRepository:catRepo notificationRepository:notificationRepo attachmentsService:attachService topicRepository:topicRepo];
                        } else if ([factory respondsToSelector:@selector(initWithApplicationLauncher:categoryRepository:notificationRepository:attachmentsService:)]){ //<= iOS11
                            factory = [factory initWithApplicationLauncher:appLauncher categoryRepository:catRepo notificationRepository:notificationRepo attachmentsService:attachService];
                        }
                        
                        //UNSNotificationAuthorizationService
                        if (objc_getClass("UNSNotificationAuthorizationService")){ //ios13+
                            UNSNotificationAuthorizationService *authorizationService = [[objc_getClass("UNSNotificationAuthorizationService") alloc] initWithDataProviderFactory:factory];
                            UNSNotificationSourceDescription *sourceDescription = [objc_getClass("UNSNotificationSourceDescription") applicationSourceDescriptionWithApplication:bundleProxy];

                            [authorizationService requestAuthorizationWithOptions:options forNotificationSourceDescription:sourceDescription completionHandler:nil];
                            
                        } else if (objc_getClass("UNSNotificationSettingsService")){ //iOS12+
                            UNSNotificationSettingsService *settingService = [[objc_getClass("UNSNotificationSettingsService") alloc] initWithDataProviderFactory:factory];
                            if ([settingService respondsToSelector:@selector(requestAuthorizationWithOptions:forNotificationSourceDescription:completionHandler:)]) { //iOS12+
                                UNSNotificationSourceDescription *sourceDescription = [objc_getClass("UNSNotificationSourceDescription") applicationSourceDescriptionWithApplication:bundleProxy];
                                [settingService requestAuthorizationWithOptions:options forNotificationSourceDescription:sourceDescription completionHandler:nil];
                            } else if ([settingService respondsToSelector:@selector(requestAuthorizationWithOptions:forBundleIdentifier:completionHandler:)]){ //<= iOS11
                                [settingService requestAuthorizationWithOptions:options forBundleIdentifier:bundleId completionHandler:nil];
                            }
                        }
                                                
                        dlclose(usernotificationsFactoryHandle);
                    }
                }
            }];
            
            UNMutableNotificationContent *content = [[objc_getClass("UNMutableNotificationContent") alloc] init];
            if (title)
                content.title = title;
            if (message)
                content.body = message;
            if (soundName)
                content.sound = [objc_getClass("UNNotificationSound") soundNamed:soundName];
            else
                content.sound = [objc_getClass("UNNotificationSound") defaultSound];
            if (userInfo)
                content.userInfo = userInfo;
            if (badgeCount)
                content.badge = badgeCount;
            if (!delay || delay == 0) // delay cannot be 0, framework will complain and crash
                delay = 1.00;
            if (delay < 60.00 && repeats)
                delay = 60.00;
            
            if (@available(iOS 11.0, *)) {
                //UNTextInputNotificationAction *action = [objc_getClass("UNTextInputNotificationAction") actionWithIdentifier:@"Reply" title:@"Reply" options:UNNotificationActionOptionNone textInputButtonTitle:@"Send" textInputPlaceholder:@""]; //make this an option?
                UNNotificationCategory *showTitleCategory = [objc_getClass("UNNotificationCategory") categoryWithIdentifier:@"actionCategory" actions:@[/*action*/] intentIdentifiers:@[] options:UNNotificationCategoryOptionHiddenPreviewsShowTitle];
                [center setNotificationCategories:[NSSet setWithObject:showTitleCategory]];
                content.threadIdentifier = bundleId;
                //content.categoryIdentifier = @"actionCategory";
            }
            
            NSTimeInterval interval = delay; //make this an option maybe
            UNTimeIntervalNotificationTrigger *trigger = [objc_getClass("UNTimeIntervalNotificationTrigger") triggerWithTimeInterval:interval repeats:repeats];
            UNNotificationRequest *request = [objc_getClass("UNNotificationRequest") requestWithIdentifier:[[NSUUID UUID] UUIDString]
                                                                                                   content:content trigger:trigger];
            [center addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {
                if (!error) {
                    CPLog(@"Local Notification succeeded");
                } else {
                    CPLog(@"ERROR: addNotificationRequest:withCompletionHandler: %@", error.localizedDescription);
                }
            }];
            
            dlclose(usernotificationsHandle);
        }
    }
    dlclose(uikitHandle);
}


static void libnotificationd_peer_event_handler(xpc_connection_t peer, xpc_object_t event)
{
	xpc_type_t type = xpc_get_type(event);
	if (type == XPC_TYPE_ERROR) {
		if (event == XPC_ERROR_CONNECTION_INVALID) {
			// The client process on the other end of the connection has either
			// crashed or cancelled the connection. After receiving this error,
			// the connection is in an invalid state, and you do not need to
			// call xpc_connection_cancel(). Just tear down any associated state
			// here.
		} else if (event == XPC_ERROR_TERMINATION_IMMINENT) {
			// Handle per-connection termination cleanup.
		}
	} else {
		assert(type == XPC_TYPE_DICTIONARY);
        showNotificationWithXPCObject(event);
	}
}

static void libnotificationd_event_handler(xpc_connection_t peer)
{
	// By defaults, new connections will target the default dispatch concurrent queue.
	xpc_connection_set_event_handler(peer, ^(xpc_object_t event) {
		libnotificationd_peer_event_handler(peer, event);
	});
	
	// This will tell the connection to begin listening for events. If you
	// have some other initialization that must be done asynchronously, then
	// you can defer this call until after that initialization is done.
	xpc_connection_resume(peer);
}

int main(int argc, const char *argv[])
{
	xpc_connection_t service = xpc_connection_create_mach_service("com.cokepokes.libnotificationd",
                                                                  dispatch_get_main_queue(),
                                                                  XPC_CONNECTION_MACH_SERVICE_LISTENER);
    
    if (!service) {
        CPLog(@"ERROR: Failed to create service.");
        exit(EXIT_FAILURE);
    }
    
    xpc_connection_set_event_handler(service, ^(xpc_object_t connection) {
        libnotificationd_event_handler(connection);
    });
    
    xpc_connection_resume(service);
    
    dispatch_main();
    
    // xpc_release(service);
    
    return EXIT_SUCCESS;
}
