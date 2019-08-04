# libnotifications
App Notification Library for Jailbroken Devices

How to use in your tweak:

```objc

@interface CPNotification : NSObject
+ (void)showAlertWithTitle:(NSString*)title message:(NSString*)message userInfo:(NSDictionary*)userInfo bundleId:(nonnull NSString*)bundleId;
@end

void *handle = dlopen("/usr/lib/libnotifications.dylib", RTLD_LAZY);
if (handle != NULL) {
	[objc_getClass("CPNotification") showAlertWithTitle:@"Holy Shit"
                                                    message:@"This is the message!"
                                                   userInfo:@{@"" : @""}
                                                   bundleId:@"com.cokepokes.iNutt"];
	dlclose(handle);
}
	
```
