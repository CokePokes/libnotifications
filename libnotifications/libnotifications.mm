//
//  libnotifications.mm
//  libnotifications
//
//  Created by CokePokes on 8/2/19.
//  Copyright (c) 2019 ___ORGANIZATIONNAME___. All rights reserved.
//

// CaptainHook by Ryan Petrich
// see https://github.com/rpetrich/CaptainHook/

#if TARGET_OS_SIMULATOR
#error Do not support the simulator, please use the real iPhone Device.
#endif

#import <Foundation/Foundation.h>
#import "CaptainHook/CaptainHook.h"
#include <notify.h> // not required; for examples only
#include <xpc/xpc.h>

#import "NSDictionary+CDXPC.h"

#define CPLog(fmt, ...) NSLog((@"\e[4#1mCPNotification\e[m \E[3#2m[Line %d]:\e[m " fmt), __LINE__, ##__VA_ARGS__);

static NSString * toBase64String(NSString *string) {
    NSData *dataToEncode = [string dataUsingEncoding:NSUTF8StringEncoding];
    NSData *encodedData = [dataToEncode base64EncodedDataWithOptions:0];
    NSString *encodedString = [[NSString alloc] initWithData:encodedData encoding:NSUTF8StringEncoding];
    return encodedString;
}

static NSString * fromBase64String(NSString *string) {
    NSData *decodedData = [[NSData alloc] initWithBase64EncodedString:string options:0];
    NSString *decodedString = [[NSString alloc] initWithData:decodedData encoding:NSUTF8StringEncoding];
    return decodedString;
}

@interface NSTask : NSObject
+ (NSTask *)launchedTaskWithLaunchPath:(NSString *)path arguments:(NSArray *)arguments;
@end

@interface CPNotification : NSObject
+ (void)showAlertWithTitle:(NSString*)title message:(NSString*)message userInfo:(NSDictionary*)userInfo badgeCount:(int)badgeCount soundName:(NSString*)soundName delay:(double)delay repeats:(BOOL)repeats bundleId:(nonnull NSString*)bundleId;
@end

@implementation CPNotification

-(id)init {
	if ((self = [super init])){}
    return self;
}

+ (void)showAlertWithTitle:(NSString*)title message:(NSString*)message userInfo:(NSDictionary*)userInfo badgeCount:(int)badgeCount soundName:(NSString*)soundName delay:(double)delay repeats:(BOOL)repeats bundleId:(nonnull NSString*)bundleId {
    
    NSMutableDictionary *constructedDic = [NSMutableDictionary dictionary];
    
    if (title)
        [constructedDic setObject:title forKey:@"title"];
    
    if (message)
        [constructedDic setObject:message forKey:@"message"];
    
    if (userInfo)
        [constructedDic setObject:userInfo forKey:@"userInfo"];
    
    if (badgeCount)
        [constructedDic setObject:[NSNumber numberWithInt:badgeCount] forKey:@"badgeCount"];

    if (soundName)
        [constructedDic setObject:soundName forKey:@"soundName"];
    
    if (delay)
        [constructedDic setObject:[NSNumber numberWithDouble:delay] forKey:@"delay"];
    
    if (repeats)
        [constructedDic setObject:[NSNumber numberWithBool:repeats] forKey:@"repeats"];
    
    if (bundleId)
        [constructedDic setObject:bundleId forKey:@"bundleId"];
    else
        return; //don't proceed. BundleId is required!
    
    xpc_connection_t client = xpc_connection_create_mach_service("com.cokepokes.libnotificationd",
                                                                 NULL,
                                                                 0);
    xpc_connection_set_event_handler(client, ^(xpc_object_t event) {
        CPLog(@"ERROR: xpc_connection_set_event_handler");
    });
    xpc_connection_resume(client);
    //xpc_object_t reply = xpc_connection_send_message_with_reply_sync(client, dictToSend.XPCObject); //could set up a completion with this
    xpc_connection_send_message(client, [(NSDictionary*)constructedDic.copy XPCObject]);
}

@end

