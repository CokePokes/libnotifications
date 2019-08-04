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

#define CPLog(fmt, ...) NSLog((@"\e[4#1mlibnotificationd\e[m \E[3#2m[Line %d]:\e[m " fmt), __LINE__, ##__VA_ARGS__);

@interface LSBundleProxy : NSObject <NSSecureCoding> {
}
+(id)bundleProxyForIdentifier:(id)arg1 ;
@end

@interface UNUserNotificationCenter (Undocumented)
-(id)initWithBundleIdentifier:(id)arg1 ;
-(id)initWithBundleProxy:(id)arg1 ;
@end

extern mach_port_t SBSSpringBoardServerPort();

static NSString * fromBase64String(NSString *string) {
    NSData *decodedData = [[NSData alloc] initWithBase64EncodedString:string options:0];
    NSString *decodedString = [[NSString alloc] initWithData:decodedData encoding:NSUTF8StringEncoding];
    return decodedString;
}

static NSDictionary * dicFromDicString(NSString*string) {
    NSError * err;
    NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary * response;
    if (data != nil){
        response = (NSDictionary *)[NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&err];
    }
    return response;
}

static void showNotificationWithXPCObject(xpc_object_t object) {
    
    NSDictionary *dic = [NSDictionary dictionaryWithXPCObject:object];
    
    NSString *title = [dic objectForKey:@"title"];
    NSString *message = [dic objectForKey:@"message"];
    NSDictionary *userInfo = [dic objectForKey:@"userInfo"];
    NSString *bundleId = [dic objectForKey:@"bundleId"];
    
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
        void *usernotificationsHandle = dlopen("/System/Library/Frameworks/UserNotifications.framework/UserNotifications", RTLD_LAZY);
        if (usernotificationsHandle != NULL) {
            LSBundleProxy *bundleProxy = [objc_getClass("LSBundleProxy") bundleProxyForIdentifier:bundleId];
            UNUserNotificationCenter *center = [[objc_getClass("UNUserNotificationCenter") alloc] initWithBundleProxy:bundleProxy];
            
            [center requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge) completionHandler:^(BOOL granted, NSError * _Nullable error){
                if(!error){
                    [[objc_getClass("UIApplication") sharedApplication] registerForRemoteNotifications];
                } else {
                    CPLog(@"ERROR: requestAuthorizationWithOptions: %@", error.localizedDescription);
                }
            }];
            
            UNMutableNotificationContent *objNotificationContent = [[objc_getClass("UNMutableNotificationContent") alloc] init];
            if (title)
                objNotificationContent.title = title;
            if (message)
                objNotificationContent.body = message;
            objNotificationContent.sound = [objc_getClass("UNNotificationSound") defaultSound]; //make this an option maybe
            if (userInfo)
                objNotificationContent.userInfo = userInfo;
            objNotificationContent.badge = [NSNumber numberWithInteger:1];
            
            NSTimeInterval interval = 1.0; //make this an option maybe
            UNTimeIntervalNotificationTrigger *trigger = [objc_getClass("UNTimeIntervalNotificationTrigger") triggerWithTimeInterval:interval repeats:NO];
            UNNotificationRequest *request = [objc_getClass("UNNotificationRequest") requestWithIdentifier:bundleId
                                                                                                   content:objNotificationContent trigger:trigger];
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
        NSLog(@"Failed to create service.");
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
