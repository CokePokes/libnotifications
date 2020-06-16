# libnotifications
App Notification Library for Jailbroken Devices

`Requires iOS10+`

This library can be used in a process or a tweak. You can set up a rocketbootstrap server in SpringBoard if you're using in a sandboxed process & run this code there. 

How to use in your tweak:

```objc

#include <dlfcn.h>

@interface CPNotification : NSObject
+ (void)showAlertWithTitle:(NSString*)title message:(NSString*)message userInfo:(NSDictionary*)userInfo badgeCount:(int)badgeCount soundName:(NSString*)soundName delay:(double)delay repeats:(BOOL)repeats bundleId:(nonnull NSString*)bundleId uuid:(NSString*)uuid silent:(BOOL)silent;
+ (void)hideAlertWithBundleId:(NSString *)bundleId uuid:(NSString*)uuid;
@end

- (void)showNotification {

	void *handle = dlopen("/usr/lib/libnotifications.dylib", RTLD_LAZY);
	if (handle != NULL) {                                            
    
 	   NSString *uid = [[NSUUID UUID] UUIDString];        
  	  [objc_getClass("CPNotification") showAlertWithTitle:@"Holy Smokes!"
  	                                              message:@"This is the message!"
	                                               userInfo:@{@"" : @""}
	                                             badgeCount:1
	                                              soundName:nil //research UNNotificationSound
	                                                  delay:1.00 //cannot be zero & cannot be < 60 if repeats is YES
	                                                repeats:NO
	                                               bundleId:@"com.apple.MobileSMS"
	                                                   uuid:uid //specify if you need to use hideAlertWithBundleId and store the string for later use
	                                                 silent:NO];
					       				       
	     dlclose(handle);
	}
}





```

The app must have notification privileges. To do this you can add this BOOL to the Info.plist file for an app in /Applications: 
```
<key>SBAppUsesLocalNotifications</key>
<true/>
```

