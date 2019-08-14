//
//  Headers.h
//  libnotificationdaemon
//
//  Created by CokePokes on 8/3/19.
//  Copyright (c) 2019 ___ORGANIZATIONNAME___. All rights reserved.
//

// XPC Service: Lightweight helper tool that performs work on behalf of an application.
// see http://developer.apple.com/library/mac/#documentation/MacOSX/Conceptual/BPSystemStartup/Chapters/CreatingXPCServices.html

@protocol LAPrearmContextXPC;
@class LAClient, NSNumber, NSData, NSString;

@interface LAContext : NSObject {
    
    LAClient* _client;
    id<LAPrearmContextXPC> _prearmContext;
    BOOL _cancelButtonVisible;
    BOOL _fallbackButtonVisible;
    NSNumber* _maxBiometryFailures;
    NSData* _evaluatedPolicyDomainState;
    long long _biometryType;
    NSData* _externalizedContext;
    
}

@property (nonatomic,retain) NSData * externalizedContext;                                           //@synthesize externalizedContext=_externalizedContext - In the implementation block
@property (assign,getter=isCancelButtonVisible,nonatomic) BOOL cancelButtonVisible;                  //@synthesize cancelButtonVisible=_cancelButtonVisible - In the implementation block
@property (assign,getter=isFallbackButtonVisible,nonatomic) BOOL fallbackButtonVisible;              //@synthesize fallbackButtonVisible=_fallbackButtonVisible - In the implementation block
@property (nonatomic,retain) NSData * evaluatedPolicyDomainState;                                    //@synthesize evaluatedPolicyDomainState=_evaluatedPolicyDomainState - In the implementation block
@property (assign,nonatomic) long long biometryType;                                                 //@synthesize biometryType=_biometryType - In the implementation block
@property (nonatomic,retain) NSNumber * touchIDAuthenticationRetryLimit;
@property (assign,nonatomic) id uiDelegate;
@property (nonatomic,copy) NSString * localizedFallbackTitle;
@property (nonatomic,copy) NSString * localizedCancelTitle;
@property (nonatomic,retain) NSNumber * maxBiometryFailures;                                         //@synthesize maxBiometryFailures=_maxBiometryFailures - In the implementation block
@property (assign,nonatomic) double touchIDAuthenticationAllowableReuseDuration;
@property (nonatomic,copy) NSString * localizedReason;
@property (assign,nonatomic) BOOL interactionNotAllowed;
+(id)currentContext;

@end

@class NSSet, NSDictionary;

@interface LSBundleInfoCachedValues : NSObject <NSCopying> {
    
    NSSet* _keys;
    NSDictionary* _values;
    
}

@property (nonatomic,readonly) NSSet * allKeys;                       //@synthesize keys=_keys - In the implementation block
@property (nonatomic,readonly) NSDictionary * rawValues;              //@synthesize values=_values - In the implementation block
-(id)arrayForKey:(id)arg1 ;
-(id)URLForKey:(id)arg1 ;
-(id)numberForKey:(id)arg1 ;
-(id)_initWithKeys:(id)arg1 forDictionary:(id)arg2 ;
-(id)objectForKey:(id)arg1 ofType:(Class)arg2 ;
-(id)arrayForKey:(id)arg1 withValuesOfClass:(Class)arg2 ;
-(NSDictionary *)rawValues;
-(id)init;
-(void)dealloc;
-(id)objectForKey:(id)arg1 ;
-(id)copyWithZone:(NSZone*)arg1 ;
-(NSSet *)allKeys;
-(BOOL)boolForKey:(id)arg1 ;
-(id)stringForKey:(id)arg1 ;
-(id)dictionaryForKey:(id)arg1 ;
@end

@class LSContext;

@interface _LSLazyPropertyList : NSObject <NSCopying, NSSecureCoding>

@property (readonly) NSDictionary * propertyList;
+(id)lazyPropertyListWithContext:(LSContext*)arg1 unit:(unsigned)arg2 ;
+(id)lazyPropertyListWithPropertyListData:(id)arg1 ;
+(id)lazyPropertyListWithPropertyList:(id)arg1 ;
+(id)lazyPropertyListWithLazyPropertyLists:(id)arg1 ;
+(BOOL)supportsSecureCoding;
-(NSDictionary *)propertyList;
-(id)objectForPropertyListKey:(id)arg1 ofClass:(Class)arg2 ;
-(BOOL)_getPropertyList:(id*)arg1 ;
-(BOOL)_getValue:(id*)arg1 forPropertyListKey:(id)arg2 ;
-(id)_filterValueFromPropertyList:(id)arg1 ofClass:(Class)arg2 valuesOfClass:(Class)arg3 ;
-(id)objectsForPropertyListKeys:(id)arg1 ;
-(id)objectForPropertyListKey:(id)arg1 ofClass:(Class)arg2 valuesOfClass:(Class)arg3 ;
-(id)init;
-(void)encodeWithCoder:(id)arg1 ;
-(id)initWithCoder:(id)arg1 ;
-(id)copyWithZone:(NSZone*)arg1 ;
@end

@class NSArray;
@interface _LSCompoundLazyPropertyList : _LSLazyPropertyList {
    
    NSArray* _plists;
    
}
+(BOOL)supportsSecureCoding;
-(BOOL)_getPropertyList:(id*)arg1 ;
-(BOOL)_getValue:(id*)arg1 forPropertyListKey:(id)arg2 ;
-(id)initWithLazyPropertyLists:(id)arg1 ;
-(void)encodeWithCoder:(id)arg1 ;
-(id)initWithCoder:(id)arg1 ;
@end


@protocol OS_dispatch_queue;
@class UNSDefaultDataProviderFactory, UNSCriticalAlertAuthorizationAlertController, UNSNotificationAuthorizationAlertController, NSObject;

@interface UNSNotificationSettingsService : NSObject {
    
    UNSDefaultDataProviderFactory* _dataProviderFactory;
    UNSCriticalAlertAuthorizationAlertController* _criticalAlertAuthorizationAlertController;
    UNSNotificationAuthorizationAlertController* _notificationAuthorizationAlertController;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(id)notificationSettingsForBundleIdentifier:(id)arg1 ;
-(id)initWithDataProviderFactory:(id)arg1 ;
-(id)authorizedBundleIdentifiersForBundleIdentifiers:(id)arg1 ;
-(void)_queue_requestCriticalAlertAuthorizationForNotificationSourceDescription:(id)arg1 completionHandler:(/*^block*/id)arg2 ;
-(void)_queue_requestAuthorizationWithOptions:(unsigned long long)arg1 forNotificationSourceDescription:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(void)_queue_requestAuthorizationWithTopics:(id)arg1 forNotificationSourceDescription:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(void)_queue_requestAuthorizationWithOptions:(unsigned long long)arg1 topics:(id)arg2 forNotificationSourceDescription:(id)arg3 completionHandler:(/*^block*/id)arg4 ;
-(BOOL)_queue_isCarPlayAvailableForApplication:(id)arg1 ;
-(void)requestAuthorizationWithOptions:(unsigned long long)arg1 forNotificationSourceDescription:(id)arg2 completionHandler:(/*^block*/id)arg3 ;

-(void)requestAuthorizationWithOptions:(unsigned long long)arg1 forBundleIdentifier:(id)arg2 completionHandler:(/*^block*/id)arg3 ; // < ios11

-(void)requestAuthorizationWithTopics:(id)arg1 forNotificationSourceDescription:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(void)requestCriticalAlertAuthorizationForNotificationSourceDescription:(id)arg1 completionHandler:(/*^block*/id)arg2 ;
@end

@class NSString, NSURL, NSUUID, NSArray, _LSLazyPropertyList, _LSBundleIDValidationToken, LSApplicationProxy, NSDictionary;
@interface LSBundleProxy : NSObject <NSSecureCoding> {
}
@property (nonatomic,readonly) NSDictionary * entitlements;
@property (nonatomic,readonly) NSDictionary * environmentVariables;
@property (setter=_setInfoDictionary:,nonatomic,copy) _LSLazyPropertyList * _infoDictionary;                          //@synthesize _infoDictionary=__infoDictionary - In the implementation block
@property (setter=_setEntitlements:,nonatomic,copy) _LSLazyPropertyList * _entitlements;                          //@synthesize _infoDictionary=__infoDictionary - In the implementation block
@property (nonatomic,readonly) NSURL * bundleContainerURL;
@property (nonatomic,readonly) NSURL * bundleURL;

//-(void)_setEntitlements:(id)arg1 ;
-(_LSLazyPropertyList *)_infoDictionary;
-(_LSLazyPropertyList *)_entitlements;

+(id)bundleProxyForIdentifier:(id)arg1 ;
-(id)objectsForInfoDictionaryKeys:(id)arg1 ;

@end


@class NSString, NSArray, NSNumber, _LSLazyPropertyList, NSDate, _LSDiskUsage, _LSApplicationState, NSUUID, NSProgress, NSDictionary;

@interface LSApplicationProxy : LSBundleProxy <NSSecureCoding> {
    
    NSString* _deviceIdentifierVendorName;
    NSArray* _pluginUUIDs;
    NSNumber* _versionID;
    _LSLazyPropertyList* _siriActionDefinitionURLs;
    BOOL _userInitiatedUninstall;
    int _bundleModTime;
    NSArray* _plugInKitPlugins;
    NSString* _signerOrganization;
    NSString* _companionApplicationIdentifier;
    NSArray* _counterpartIdentifiers;
    NSDate* _registeredDate;
    NSNumber* _itemID;
    NSString* _vendorName;
    NSString* _itemName;
    NSString* _genre;
    NSNumber* _genreID;
    NSString* _minimumSystemVersion;
    NSString* _maximumSystemVersion;
    NSString* _shortVersionString;
    NSString* _preferredArchitecture;
    _LSDiskUsage* _diskUsage;
    _LSApplicationState* _appState;
    NSNumber* _purchaserDSID;
    NSNumber* _downloaderDSID;
    NSNumber* _familyID;
    unsigned long long _installType;
    unsigned long long _originalInstallType;
    NSArray* _deviceFamily;
    NSArray* _activityTypes;
    NSString* _teamID;
    NSNumber* _storeFront;
    NSNumber* _ratingRank;
    NSString* _ratingLabel;
    NSString* _sourceAppIdentifier;
    NSString* _applicationVariant;
    NSString* _watchKitVersion;
    NSString* _complicationPrincipalClass;
    NSArray* _supportedComplicationFamilies;
    NSNumber* _installFailureReason;
    NSString* _appStoreToolsBuildVersion;
    
}

@property (nonatomic,readonly) BOOL cx_hasVoIPBackgroundMode;
@property (readonly) NSArray * _inf_userActivityTypes;
@property (assign,nonatomic) BOOL userInitiatedUninstall;                                          //@synthesize userInitiatedUninstall=_userInitiatedUninstall - In the implementation block
@property (nonatomic,readonly) BOOL supportsAlternateIconNames;
@property (nonatomic,readonly) int bundleModTime;                                                  //@synthesize bundleModTime=_bundleModTime - In the implementation block
@property (nonatomic,readonly) NSString * applicationIdentifier;
@property (nonatomic,readonly) NSString * companionApplicationIdentifier;                          //@synthesize companionApplicationIdentifier=_companionApplicationIdentifier - In the implementation block
@property (nonatomic,readonly) NSArray * counterpartIdentifiers;                                   //@synthesize counterpartIdentifiers=_counterpartIdentifiers - In the implementation block
@property (nonatomic,readonly) NSDate * registeredDate;                                            //@synthesize registeredDate=_registeredDate - In the implementation block
@property (nonatomic,readonly) NSNumber * itemID;                                                  //@synthesize itemID=_itemID - In the implementation block
@property (nonatomic,readonly) NSString * vendorName;                                              //@synthesize vendorName=_vendorName - In the implementation block
@property (nonatomic,readonly) NSString * itemName;                                                //@synthesize itemName=_itemName - In the implementation block
@property (nonatomic,readonly) NSString * storeCohortMetadata;
@property (nonatomic,readonly) NSString * genre;                                                   //@synthesize genre=_genre - In the implementation block
@property (nonatomic,readonly) NSNumber * genreID;                                                 //@synthesize genreID=_genreID - In the implementation block
@property (nonatomic,readonly) NSArray * subgenres;
@property (nonatomic,readonly) NSArray * staticShortcutItems;
@property (nonatomic,readonly) NSString * minimumSystemVersion;                                    //@synthesize minimumSystemVersion=_minimumSystemVersion - In the implementation block
@property (nonatomic,readonly) NSString * maximumSystemVersion;                                    //@synthesize maximumSystemVersion=_maximumSystemVersion - In the implementation block
@property (nonatomic,readonly) NSString * shortVersionString;                                      //@synthesize shortVersionString=_shortVersionString - In the implementation block
@property (nonatomic,readonly) NSString * preferredArchitecture;                                   //@synthesize preferredArchitecture=_preferredArchitecture - In the implementation block
@property (nonatomic,readonly) NSString * applicationType;
@property (nonatomic,readonly) NSArray * directionsModes;
@property (nonatomic,readonly) NSArray * UIBackgroundModes;
@property (nonatomic,readonly) NSArray * audioComponents;
@property (nonatomic,readonly) NSUUID * deviceIdentifierForVendor;
@property (nonatomic,readonly) NSUUID * deviceIdentifierForAdvertising;
@property (nonatomic,readonly) NSProgress * installProgress;
@property (nonatomic,readonly) NSNumber * staticDiskUsage;
@property (nonatomic,readonly) NSNumber * dynamicDiskUsage;
@property (nonatomic,readonly) NSNumber * ODRDiskUsage;
@property (nonatomic,readonly) _LSDiskUsage * diskUsage;                                           //@synthesize diskUsage=_diskUsage - In the implementation block
@property (nonatomic,readonly) _LSApplicationState * appState;                                     //@synthesize appState=_appState - In the implementation block
@property (getter=isInstalled,nonatomic,readonly) BOOL installed;
@property (getter=isPlaceholder,nonatomic,readonly) BOOL placeholder;
@property (getter=isRestricted,nonatomic,readonly) BOOL restricted;
@property (getter=isRemovedSystemApp,nonatomic,readonly) BOOL removedSystemApp;
@property (nonatomic,readonly) NSArray * VPNPlugins;
@property (nonatomic,readonly) NSArray * plugInKitPlugins;                                         //@synthesize plugInKitPlugins=_plugInKitPlugins - In the implementation block
@property (nonatomic,readonly) NSArray * appTags;
@property (nonatomic,readonly) NSString * applicationDSID;
@property (nonatomic,readonly) NSNumber * purchaserDSID;                                           //@synthesize purchaserDSID=_purchaserDSID - In the implementation block
@property (nonatomic,readonly) NSNumber * downloaderDSID;                                          //@synthesize downloaderDSID=_downloaderDSID - In the implementation block
@property (nonatomic,readonly) NSNumber * familyID;                                                //@synthesize familyID=_familyID - In the implementation block
@property (nonatomic,readonly) unsigned long long installType;                                     //@synthesize installType=_installType - In the implementation block
@property (nonatomic,readonly) unsigned long long originalInstallType;                             //@synthesize originalInstallType=_originalInstallType - In the implementation block
@property (nonatomic,readonly) NSArray * requiredDeviceCapabilities;
@property (nonatomic,readonly) NSArray * deviceFamily;                                             //@synthesize deviceFamily=_deviceFamily - In the implementation block
@property (nonatomic,readonly) NSArray * activityTypes;                                            //@synthesize activityTypes=_activityTypes - In the implementation block
@property (nonatomic,readonly) NSArray * externalAccessoryProtocols;
@property (nonatomic,readonly) NSString * teamID;                                                  //@synthesize teamID=_teamID - In the implementation block
@property (nonatomic,readonly) NSNumber * storeFront;                                              //@synthesize storeFront=_storeFront - In the implementation block
@property (nonatomic,readonly) NSNumber * externalVersionIdentifier;
@property (nonatomic,readonly) NSNumber * betaExternalVersionIdentifier;
@property (nonatomic,readonly) NSNumber * ratingRank;                                              //@synthesize ratingRank=_ratingRank - In the implementation block
@property (nonatomic,readonly) NSString * ratingLabel;                                             //@synthesize ratingLabel=_ratingLabel - In the implementation block
@property (nonatomic,readonly) NSString * sourceAppIdentifier;                                     //@synthesize sourceAppIdentifier=_sourceAppIdentifier - In the implementation block
@property (nonatomic,readonly) NSString * applicationVariant;                                      //@synthesize applicationVariant=_applicationVariant - In the implementation block
@property (getter=isAppUpdate,nonatomic,readonly) BOOL appUpdate;
@property (nonatomic,readonly) BOOL hasParallelPlaceholder;
@property (getter=isNewsstandApp,nonatomic,readonly) BOOL newsstandApp;
@property (getter=isWhitelisted,nonatomic,readonly) BOOL whitelisted;
@property (getter=isAppStoreVendable,nonatomic,readonly) BOOL appStoreVendable;
@property (getter=isDeviceBasedVPP,nonatomic,readonly) BOOL deviceBasedVPP;
@property (getter=isBetaApp,nonatomic,readonly) BOOL betaApp;
@property (getter=isAdHocCodeSigned,nonatomic,readonly) BOOL adHocCodeSigned;
@property (nonatomic,readonly) BOOL supportsAudiobooks;
@property (getter=isLaunchProhibited,nonatomic,readonly) BOOL launchProhibited;
@property (nonatomic,readonly) BOOL supportsODR;
@property (nonatomic,readonly) BOOL hasSettingsBundle;
@property (nonatomic,readonly) BOOL supportsExternallyPlayableContent;
@property (nonatomic,readonly) BOOL supportsOpenInPlace;
@property (nonatomic,readonly) BOOL fileSharingEnabled;
@property (nonatomic,readonly) BOOL iconIsPrerendered;
@property (nonatomic,readonly) BOOL iconUsesAssetCatalog;
@property (getter=isPurchasedReDownload,nonatomic,readonly) BOOL purchasedReDownload;
@property (nonatomic,readonly) BOOL hasMIDBasedSINF;
@property (nonatomic,readonly) BOOL missingRequiredSINF;
@property (nonatomic,readonly) BOOL supportsPurgeableLocalStorage;
@property (getter=isDeletable,nonatomic,readonly) BOOL deletable;
@property (getter=isRemoveableSystemApp,nonatomic,readonly) BOOL removeableSystemApp;
@property (getter=isWatchKitApp,nonatomic,readonly) BOOL watchKitApp;
@property (nonatomic,readonly) NSString * watchKitVersion;                                         //@synthesize watchKitVersion=_watchKitVersion - In the implementation block
@property (readonly) NSString * complicationPrincipalClass;                                        //@synthesize complicationPrincipalClass=_complicationPrincipalClass - In the implementation block
@property (readonly) NSArray * supportedComplicationFamilies;                                      //@synthesize supportedComplicationFamilies=_supportedComplicationFamilies - In the implementation block
@property (nonatomic,readonly) BOOL hasCustomNotification;
@property (readonly) BOOL hasComplication;
@property (nonatomic,readonly) BOOL hasGlance;
@property (nonatomic,readonly) BOOL shouldSkipWatchAppInstall;
@property (getter=isGameCenterEnabled,nonatomic,readonly) BOOL gameCenterEnabled;
@property (nonatomic,readonly) BOOL gameCenterEverEnabled;
@property (nonatomic,readonly) NSNumber * installFailureReason;                                    //@synthesize installFailureReason=_installFailureReason - In the implementation block
@property (nonatomic,readonly) long long deviceManagementPolicy;
@property (nonatomic,readonly) NSDictionary * siriActionDefinitionURLs;
@property (nonatomic,readonly) NSString * appStoreToolsBuildVersion;                               //@synthesize appStoreToolsBuildVersion=_appStoreToolsBuildVersion - In the implementation block
+(id)applicationProxyForCompanionIdentifier:(id)arg1 ;
+(id)applicationProxyForBundleURL:(id)arg1 ;
+(id)applicationProxyForSystemPlaceholder:(id)arg1 ;
+(id)applicationProxyForIdentifier:(id)arg1 placeholder:(BOOL)arg2 ;
+(id)applicationProxyWithBundleUnitID:(unsigned)arg1 withContext:(LSContext*)arg2 ;
+(id)applicationProxyForIdentifier:(id)arg1 withContext:(LSContext*)arg2 ;

-(BOOL)isMISAuthorized;

@end

@protocol OS_dispatch_queue;
@class FBSSystemService, UNSLocationMonitor, NSMutableDictionary, NSObject;

@interface UNSApplicationLauncher : NSObject {
    
    FBSSystemService* _systemService;
    UNSLocationMonitor* _locationMonitor;
    NSMutableDictionary* _bundleIdentifierToAssertions;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(id)initWithSystemService:(id)arg1 locationMonitor:(id)arg2 ;
-(void)willPresentNotification:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)foregroundLaunchApplication:(id)arg1 withResponse:(id)arg2 launchImageName:(id)arg3 origin:(id)arg4 completionHandler:(/*^block*/id)arg5 ;
-(void)backgroundLaunchApplication:(id)arg1 withResponse:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(void)_queue_willPresentNotification:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)_removeAllProcessAssertionsAndInvalidate:(BOOL)arg1 ;
-(void)_queue_foregroundLaunchApplication:(id)arg1 withResponse:(id)arg2 launchImageName:(id)arg3 origin:(id)arg4 completionHandler:(/*^block*/id)arg5 ;
-(id)_queue_actionForNotificationResponse:(id)arg1 bundleIdentifier:(id)arg2 withHandler:(/*^block*/id)arg3 ;
-(void)_queue_backgroundLaunchApplication:(id)arg1 withResponse:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(void)_queue_removeProcessAssertion:(id)arg1 forBundleID:(id)arg2 invalidate:(BOOL)arg3 ;
-(id)_queue_newProcessAssertionForBundleID:(id)arg1 flags:(unsigned)arg2 reason:(unsigned)arg3 name:(id)arg4 watchdogInterval:(double)arg5 acquisitionHandler:(/*^block*/id)arg6 invalidationHandler:(/*^block*/id)arg7 ;
-(void)_queue_removeProcessAssertionsHavingReason:(unsigned)arg1 forBundleID:(id)arg2 invalidate:(BOOL)arg3 ;
-(void)_queue_addProcessAssertion:(id)arg1 forBundleID:(id)arg2 ;
-(void)_queue_removeAllProcessAssertionsAndInvalidate:(BOOL)arg1 ;
-(void)dealloc;
@end


@protocol OS_dispatch_queue;
@class NSObject, NSMutableDictionary, NSString;

@interface UNSDaemonLauncher : NSObject /*<UNUserNotificationCenterDelegateServiceProtocol>*/ {
    
    //NSObject*<OS_dispatch_queue> _queue;
    //NSObject*<OS_dispatch_queue> _callOutQueue;
    NSMutableDictionary* _connectionByBundleIdentifier;
    
}

@property (readonly) unsigned long long hash;
@property (readonly) Class superclass;
@property (copy,readonly) NSString * description;
@property (copy,readonly) NSString * debugDescription;
-(id)_queue_ensureConnectionForBundleIdentifier:(id)arg1 ;
-(void)didReceiveNotificationResponse:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)_queue_interruptedConnectionForBundleIdentifier:(id)arg1 ;
-(void)_queue_invalidatedConnectionForBundleIdentifier:(id)arg1 ;
-(id)init;
@end

@interface UNUserNotificationCenter (Undocumented)
-(id)initWithBundleIdentifier:(id)arg1 ;
-(id)initWithBundleProxy:(id)arg1 ;
@end

// Firmware < 9.0
@interface SBSLocalNotificationClient : NSObject
+ (void)scheduleLocalNotification:(id)notification bundleIdentifier:(id)bundleIdentifier;
@end

// Firmware >= 9.0 < 10.0
@interface UNSNotificationScheduler
- (id)initWithBundleIdentifier:(NSString *)bundleIdentifier;
- (void)addScheduledLocalNotifications:(NSArray *)notifications waitUntilDone:(BOOL)waitUntilDone;
@end




//protocol OS_dispatch_queue;
@class NSMutableDictionary, NSMutableSet, NSMutableArray, UNSApplicationLauncher, UNSDaemonLauncher, UNSNotificationCategoryRepository, UNSNotificationRepository, UNSNotificationTopicRepository, UNSAttachmentsService, BBDataProviderConnection, BBSettingsGateway, BBObserver, NSObject, NSString;

@interface UNSDefaultDataProviderFactory : NSObject  {
    
    NSMutableDictionary* _dataProvidersByBundleIdentifier;
    NSMutableDictionary* _descriptionsByBundleIdentifier;
    NSMutableSet* _authorizedBundleIdentifiers;
    NSMutableArray* _observers;
    UNSApplicationLauncher* _appLauncher;
    UNSDaemonLauncher* _daemonLauncher;
    UNSNotificationCategoryRepository* _categoryRepository;
    UNSNotificationRepository* _notificationRepository;
    UNSNotificationTopicRepository* _topicRepository;
    UNSAttachmentsService* _attachmentsService;
    BBDataProviderConnection* _dataProviderConnection;
    BBSettingsGateway* _settingsGateway;
    BBObserver* _settingsObserver;
    //NSObject*<OS_dispatch_queue> _queue;
    
}

@property (readonly) unsigned long long hash;
@property (readonly) Class superclass;
@property (copy,readonly) NSString * description;
@property (copy,readonly) NSString * debugDescription;
-(void)observer:(id)arg1 updateSectionInfo:(id)arg2 ;
-(void)_queue_notificationSourcesDidUninstall:(id)arg1 ;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(id)notificationSettingsForBundleIdentifier:(id)arg1 ;
-(void)notificationSourcesDidInstall:(id)arg1 ;
-(void)_queue_notificationSourcesDidInstall:(id)arg1 ;
-(id)initWithApplicationLauncher:(id)arg1 daemonLauncher:(id)arg2 categoryRepository:(id)arg3 notificationRepository:(id)arg4 attachmentsService:(id)arg5 topicRepository:(id)arg6 ; //iOS12+
-(id)initWithApplicationLauncher:(id)arg1 categoryRepository:(id)arg2 notificationRepository:(id)arg3 attachmentsService:(id)arg4 ; // <= iOS11.99

-(id)authorizedBundleIdentifiersForBundleIdentifiers:(id)arg1 ;
-(void)updateAuthorizationWithOptions:(unsigned long long)arg1 topics:(id)arg2 forBundleIdentifier:(id)arg3 completionHandler:(/*^block*/id)arg4 ;
-(void)requestAuthorizationStatus:(long long)arg1 withOptions:(unsigned long long)arg2 topics:(id)arg3 forBundleIdentifier:(id)arg4 completionHandler:(/*^block*/id)arg5 ;
-(void)setCriticalAlertAuthorization:(BOOL)arg1 forBundleIdentifier:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(id)_queue_notificationSettingsForBundleIdentifier:(id)arg1 ;
-(void)_queue_updateSettingsWithAuthorizationStatus:(long long)arg1 options:(unsigned long long)arg2 topics:(id)arg3 forBundleIdentifier:(id)arg4 completionHandler:(/*^block*/id)arg5 ;
-(void)_queue_setCriticalAlertAuthorization:(BOOL)arg1 forBundleIdentifier:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(id)_queue_authorizedBundleIdentifiersForBundleIdentifiers:(id)arg1 ;
-(void)_queue_addObserver:(id)arg1 ;
-(void)_queue_removeObserver:(id)arg1 ;
-(void)_queue_applicationDidEnableNotificationSettings:(id)arg1 ;
-(void)_queue_applicationDidDisableNotificationSettings:(id)arg1 ;
-(id)_queue_dataProviderForBundleIdentifier:(id)arg1 ;
-(id)_queue_sectionInfoForBundleIdentifier:(id)arg1 ;
-(void)_queue_setNotificationTopics:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_setSectionInfo:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_createDataProviderWithBundleIdentifier:(id)arg1 withCompletion:(/*^block*/id)arg2 ;
-(void)_queue_createDataProviderWithBundleIdentifier:(id)arg1 ;
-(void)_queue_notificationSourceDidUninstall:(id)arg1 ;
-(void)_queue_notificationSourceDidInstall:(id)arg1 ;
-(void)_queue_createNewDefaultDataProviders;
-(void)_queue_removeDataProviderWithBundleIdentifier:(id)arg1 ;
-(void)_queue_sectionInfoDidChange:(id)arg1 ;
-(void)dealloc;
-(void)removeObserver:(id)arg1 ;
-(void)addObserver:(id)arg1 ;
@end

@protocol OS_dispatch_queue;
@class NSObject, NSMutableSet, NSMutableDictionary;

@interface UNSAuthorizationAlertController : NSObject {
    
    //NSObject*<OS_dispatch_queue> _queue;
    NSMutableSet* _bundleIdentifersForActiveAlerts;
    NSMutableDictionary* _bundleIdentifiersToResultBlocks;
    
}
-(void)_queue_addResultBlock:(/*^block*/id)arg1 forBundleIdentifier:(id)arg2 ;
-(BOOL)_queue_isAlertActiveForBundleIdentifier:(id)arg1 ;
-(void)_queue_addAlertActiveForBundleIdentifier:(id)arg1 ;
-(void)_presentAuthorizationAlertForBundleIdentifier:(id)arg1 displayName:(id)arg2 withResult:(/*^block*/id)arg3 ;
-(void)_queue_removeAlertActiveForBundleIdentifier:(id)arg1 ;
-(void)_queue_sendResponse:(long long)arg1 forBundleIdentifier:(id)arg2 ;
-(void)presentAuthorizationAlertForBundleIdentifier:(id)arg1 displayName:(id)arg2 withResult:(/*^block*/id)arg3 ;
-(void)requestAuthorizationForBundleIdentifier:(id)arg1 displayName:(id)arg2 withResult:(/*^block*/id)arg3 ;
-(id)initWithQueue:(id)arg1 ;
@end


@interface UNSCriticalAlertAuthorizationAlertController : UNSAuthorizationAlertController
-(void)presentAuthorizationAlertForBundleIdentifier:(id)arg1 displayName:(id)arg2 withResult:(/*^block*/id)arg3 ;
@end


@protocol OS_dispatch_queue;
@class UNSKeyedDictionaryRepository, NSObject;

@interface UNSPushRegistrationRepository : NSObject {
    
    UNSKeyedDictionaryRepository* _repository;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(void)performMigration;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(void)_queue_performMigration;
-(void)setRegistration:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)allBundleIdentifiers;
-(id)registrationForBundleIdentifier:(id)arg1 ;
-(void)removeRegistrationForBundleIdentifier:(id)arg1 ;
-(void)_queue_performMigrationForBundleIdentifier:(id)arg1 ;
-(id)_queue_registrationForBundleIdentifier:(id)arg1 ;
-(void)_queue_setRegistration:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_removeRegistrationForBundleIdentifier:(id)arg1 ;
-(id)initWithDirectory:(id)arg1 ;
@end


@class CLLocationManager, UNSKeyedObservable;
@interface UNSLocationMonitor : NSObject /*<CLLocationManagerDelegate>*/ {
    
    CLLocationManager* _locationManager;
    UNSKeyedObservable* _observable;
    //NSObject*<OS_dispatch_queue> _queue;
    
}

@property (readonly) unsigned long long hash;
@property (readonly) Class superclass;
@property (copy,readonly) NSString * description;
@property (copy,readonly) NSString * debugDescription;
-(void)locationManager:(id)arg1 didEnterRegion:(id)arg2 ;
-(void)locationManager:(id)arg1 didExitRegion:(id)arg2 ;
-(void)locationManager:(id)arg1 didFailWithError:(id)arg2 ;
-(void)locationManager:(id)arg1 didStartMonitoringForRegion:(id)arg2 ;
-(void)markAsHavingReceivedLocation;
-(void)addObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)removeObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(BOOL)isBundleIdentifierAuthorizedForRegionMonitoring:(id)arg1 ;
-(void)setMonitoredRegions:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(id)initWithQueue:(id)arg1 locationManager:(id)arg2 ;
-(id)initWithQueue:(id)arg1 locationManager:(id)arg2 observable:(id)arg3 ;
-(void)_triggerDidFireForRegion:(id)arg1 ;
-(id)init;
@end


@class FBSSystemAppProxy;

@interface FBSSystemService : NSObject {
    
    FBSSystemAppProxy* _systemAppProxy;
    
}
+(id)clientCallbackQueue;
+(id)sharedService;
-(void)openApplication:(id)arg1 options:(id)arg2 clientPort:(unsigned)arg3 withResult:(/*^block*/id)arg4 ;
-(void)terminateApplicationGroup:(long long)arg1 forReason:(long long)arg2 andReport:(BOOL)arg3 withDescription:(id)arg4 completion:(/*^block*/id)arg5 ;
-(void)_openApplication:(id)arg1 withOptions:(id)arg2 clientHandle:(id)arg3 completion:(/*^block*/id)arg4 ;
-(id)processHandleForApplication:(id)arg1 ;
-(void)dataResetWithRequest:(id)arg1 completion:(/*^block*/id)arg2 ;
-(void)setKeyboardFocusApplicationWithBundleID:(id)arg1 pid:(int)arg2 completion:(/*^block*/id)arg3 ;
-(void)terminateApplication:(id)arg1 forReason:(long long)arg2 andReport:(BOOL)arg3 withDescription:(id)arg4 ;
-(void)terminateApplicationGroup:(long long)arg1 forReason:(long long)arg2 andReport:(BOOL)arg3 withDescription:(id)arg4 ;
-(void)cleanupClientPort:(unsigned)arg1 ;
-(void)reboot;
-(id)systemApplicationBundleIdentifier;
-(int)pidForApplication:(id)arg1 ;
-(void)sendActions:(id)arg1 withResult:(/*^block*/id)arg2 ;
-(void)shutdown;
-(void)shutdownWithOptions:(id)arg1 ;
-(void)terminateApplication:(id)arg1 forReason:(long long)arg2 andReport:(BOOL)arg3 withDescription:(id)arg4 completion:(/*^block*/id)arg5 ;
-(void)setBadgeValue:(id)arg1 forBundleID:(id)arg2 ;
-(BOOL)canOpenApplication:(id)arg1 reason:(long long*)arg2 ;
-(void)deleteAllSnapshotsForApplication:(id)arg1 ;
-(id)badgeValueForBundleID:(id)arg1 ;
-(unsigned)createClientPort;
-(void)openURL:(id)arg1 application:(id)arg2 options:(id)arg3 clientPort:(unsigned)arg4 withResult:(/*^block*/id)arg5 ;
-(id)init;
-(void)openApplication:(id)arg1 options:(id)arg2 withResult:(/*^block*/id)arg3 ;
-(BOOL)isPasscodeLockedOrBlocked;
@end

@protocol OS_dispatch_queue;
@class UNSKeyedDataStoreRepository, UNSKeyedObservable, NSObject;

@interface UNSNotificationCategoryRepository : NSObject {
    
    UNSKeyedDataStoreRepository* _repository;
    UNSKeyedObservable* _observable;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(void)performMigration;
-(void)_queue_notificationSourcesDidUninstall:(id)arg1 ;
-(void)addObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(void)_queue_performMigration;
-(id)allBundleIdentifiers;
-(long long)_maxObjectsPerKey;
-(id)initWithDataStoreRepository:(id)arg1 observable:(id)arg2 ;
-(void)_queue_performMigrationForBundleIdentifier:(id)arg1 ;
-(void)removeObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)categoriesForBundleIdentifier:(id)arg1 ;
-(id)_queue_categoriesForBundleIdentifier:(id)arg1 ;
-(void)_queue_setCategories:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)setCategories:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)initWithDirectory:(id)arg1 ;
-(id)init;
@end

@protocol OS_dispatch_queue, UNSNotificationRepositoryDelegate;
@class FBSSystemService, UNSKeyedDataStoreRepository, UNSKeyedObservable, NSObject;

@interface UNSNotificationRepository : NSObject {
    
    FBSSystemService* _systemService;
    UNSKeyedDataStoreRepository* _repository;
    UNSKeyedObservable* _observable;
    //NSObject*<OS_dispatch_queue> _queue;
    id<UNSNotificationRepositoryDelegate> _delegate;
    
}

@property (assign,nonatomic) id<UNSNotificationRepositoryDelegate> delegate;              //@synthesize delegate=_delegate - In the implementation block
-(void)performMigration;
-(void)performValidation;
-(void)addObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)notificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)_queue_performMigration;
-(void)saveNotificationRecord:(id)arg1 shouldRepost:(BOOL)arg2 forBundleIdentifier:(id)arg3 withCompletionHandler:(/*^block*/id)arg4 ;
-(id)allBundleIdentifiers;
-(id)initWithDirectory:(id)arg1 systemService:(id)arg2 ;
-(long long)_maxObjectsPerKey;
-(id)initWithDataStoreRepository:(id)arg1 observable:(id)arg2 ;
-(void)_queue_performMigrationForBundleIdentifier:(id)arg1 ;
-(void)removeObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)removeStoreForBundleIdentifier:(id)arg1 ;
-(void)removeAllNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)removeNotificationRecordsPassingTest:(/*^block*/id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)badgeNumberForBundleIdentifier:(id)arg1 ;
-(void)setBadgeNumber:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)setBadgeString:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(id)initWithDataStoreRepository:(id)arg1 observable:(id)arg2 systemService:(id)arg3 ;
-(id)_queue_notificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)_queue_saveNotificationRecord:(id)arg1 shouldRepost:(BOOL)arg2 withOptions:(unsigned long long)arg3 forBundleIdentifier:(id)arg4 ;
-(void)_queue_removeAllNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)_queue_removeNotificationRecordsPassingTest:(/*^block*/id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_performValidation;
-(id)_notificationsForObjects:(id)arg1 ;
-(void)_logNotification:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_setBadgeNumber:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)_queue_notifyObserversNotificationsDidAddNotifications:(id)arg1 replaceNotifications:(id)arg2 replacementNotifications:(id)arg3 removedNotifications:(id)arg4 shouldRepost:(BOOL)arg5 forBundleIdentifier:(id)arg6 ;
-(id)_queue_badgeNumberForBundleIdentifier:(id)arg1 ;
-(void)_queue_setBadgeString:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)_queue_setBadgeValue:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)_queue_performMigrationForUserNotificationsStore;
-(void)_queue_performMigrationForPushStore;
-(void)_queue_performMigrationForPushStoreAtPath:(id)arg1 ;
-(void)removeNotificationRepository;
-(id)initWithDirectory:(id)arg1 ; //iOS12+
-(id)initWithSystemService:(id)arg1 ; //<= iOS11
-(void)setDelegate:(id<UNSNotificationRepositoryDelegate>)arg1 ;
-(id<UNSNotificationRepositoryDelegate>)delegate;
@end

@protocol OS_dispatch_queue;
@class NSObject, UNSAttachmentsRepository, UNSNotificationRepository, UNSNotificationSchedulingService, UNSPendingNotificationRepository, NSString;

@interface UNSAttachmentsService : NSObject /*<UNSNotificationRepositoryObserver, UNSPendingNotificationRepositoryObserver*>*/ {
    
    //NSObject*<OS_dispatch_queue> _queue;
    UNSAttachmentsRepository* _attachmentsRepository;
    UNSNotificationRepository* _notificationRepository;
    UNSNotificationSchedulingService* _notificationSchedulingService;
    UNSPendingNotificationRepository* _pendingNotificationRepository;
    
}

@property (readonly) unsigned long long hash;
@property (readonly) Class superclass;
@property (copy,readonly) NSString * description;
@property (copy,readonly) NSString * debugDescription;
+(id)_stagingDirectory;
+(id)_attachmentURLsRemovedByReplaceUpdate:(id)arg1 ;
+(id)_notificationIdentifiersForNotificationRecords:(id)arg1 ;
-(void)_beginObservingNotificationChanges;
-(void)_queue_ensureIntegrityWithCompletionHandler:(/*^block*/id)arg1 ;
-(void)_notificationIdentifiersForBundleIdentifier:(id)arg1 replyOnQueue:(id)arg2 completionHandler:(/*^block*/id)arg3 ;
-(id)_queue_resolveAttachmentsForRequest:(id)arg1 bundleIdentifier:(id)arg2 bundleProxy:(id)arg3 error:(id*)arg4 ;
-(id)_queue_resolvedURLForNotificationAttachment:(id)arg1 request:(id)arg2 bundleIdentifier:(id)arg3 bundleProxy:(id)arg4 error:(id*)arg5 ;
-(id)_queue_validatedRepositoryURLForNotificationAttachment:(id)arg1 request:(id)arg2 bundleIdentifier:(id)arg3 bundleProxy:(id)arg4 error:(id*)arg5 ;
-(id)_queue_resolvedFileURLForNotificationAttachment:(id)arg1 request:(id)arg2 bundleIdentifier:(id)arg3 bundleProxy:(id)arg4 error:(id*)arg5 ;
-(id)_temporaryAttachmentFileURL;
-(void)_queue_deleteAttachmentDataForNotificationRecord:(id)arg1 bundleIdentifier:(id)arg2 ;
-(id)_queue_getAttachmentDataForAttachment:(id)arg1 bundleIdentifier:(id)arg2 error:(id*)arg3 ;
-(void)_queue_notificationSourcesDidUninstall:(id)arg1 ;
-(void)_queue_applicationDidUninstall:(id)arg1 ;
-(void)_repositoryDidPerformUpdates:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)notificationRepository:(id)arg1 didPerformUpdates:(id)arg2 forBundleIdentifier:(id)arg3 ;
-(void)pendingNotificationRepository:(id)arg1 didPerformUpdates:(id)arg2 forBundleIdentifier:(id)arg3 ;
-(id)initWithAttachmentsRepository:(id)arg1 notificationRepository:(id)arg2 notificationSchedulingService:(id)arg3 pendingNotificationRepository:(id)arg4 ; //iOS12+
-(id)initWithNotificationRepository:(id)arg1 notificationSchedulingService:(id)arg2 pendingNotificationRepository:(id)arg3 ; //< iOS11
-(void)ensureIntegrityWithCompletionHandler:(/*^block*/id)arg1 ;
-(id)resolveAttachmentsForRequest:(id)arg1 bundleIdentifier:(id)arg2 bundleProxy:(id)arg3 error:(id*)arg4 ;
-(id)resolveAttachmentsSkippingErrorsForRequest:(id)arg1 bundleIdentifier:(id)arg2 bundleProxy:(id)arg3 ;
-(void)_queue_deleteAttachmentDataForNotificationRecords:(id)arg1 bundleIdentifier:(id)arg2 ;
-(id)attachmentDataForAttachment:(id)arg1 bundleIdentifier:(id)arg2 error:(id*)arg3 ;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
@end

@class UNSKeyedDictionaryRepository, NSURL;

@interface UNSAttachmentsRepository : NSObject {
    
    UNSKeyedDictionaryRepository* _referencesRepository;
    NSURL* _directoryURL;
    
}
+(id)_sha1HashOfFileAtURL:(id)arg1 ;
-(void)performMigration;
-(id)bundleIdentifiersClaimingAttachments;
-(void)ensureIntegrityUsingNotificationIdentifiersForBundleIdentifiers:(id)arg1 ;
-(BOOL)isRepositoryURL:(id)arg1 ;
-(void)removeReferenceToRepositoryURL:(id)arg1 forNotificationIdentifier:(id)arg2 bundleIdentifier:(id)arg3 ;
-(BOOL)isValidRepositoryURL:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)moveFileIntoRepositoryFromFileURL:(id)arg1 forNotificationIdentifier:(id)arg2 bundleIdentifier:(id)arg3 ;
-(void)deleteAllFilesForBundleIdentifier:(id)arg1 ;
-(id)allBundleIdentifiers;
-(id)_attachmentDirectoryForBundleIdentifier:(id)arg1 ;
-(id)_fileURLForDigestString:(id)arg1 extension:(id)arg2 bundleIdentifier:(id)arg3 ;
-(unsigned long long)_addReferencesToRepositoryURL:(id)arg1 forNotificationIdentifier:(id)arg2 bundleIdentifier:(id)arg3 ;
-(unsigned long long)_removeReferencesToRepositoryURL:(id)arg1 forNotificationIdentifier:(id)arg2 bundleIdentifier:(id)arg3 ;
-(void)_removeRepositoryURL:(id)arg1 ;
-(void)_removeAllReferencesForBundleIdentifier:(id)arg1 ;
-(unsigned long long)_transformNotificationIdentifiersForRepositoryURL:(id)arg1 bundleIdentifier:(id)arg2 usingTransformBlock:(/*^block*/id)arg3 ;
-(void)_transformAttachmentsForBundleIdentifier:(id)arg1 usingTransformBlock:(/*^block*/id)arg2 ;
-(void)_performAttachmentReferencesMigration;
-(void)_performAttachmentFilesMigration;
-(void)_performAttachmentReferencesMigrationForBundleIdentifier:(id)arg1 ;
-(id)_claimedRepositoryURLsForBundleIdentifier:(id)arg1 ;
-(id)referencesForBundleIdentifier:(id)arg1 ;
-(id)initWithDirectory:(id)arg1 ; //iOS12
-(id)initWithDirectoryURL:(id)arg1 ; //<= iOS11
@end

@protocol OS_dispatch_queue;
@class UNSNotificationRepository, UNSPendingNotificationRepository, UNSNotificationScheduleRepository, UNSLocationMonitor, NSMutableDictionary, NSObject;

@interface UNSNotificationSchedulingService : NSObject {
    
    UNSNotificationRepository* _notificationRepository;
    UNSPendingNotificationRepository* _pendingNotificationRepository;
    UNSNotificationScheduleRepository* _notificationScheduleRepository;
    UNSLocationMonitor* _locationMonitor;
    NSMutableDictionary* _clients;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(void)localeDidChange;
-(void)_queue_notificationSourcesDidUninstall:(id)arg1 ;
-(id)undeliveredNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(void)_queue_applicationsDidAuthorizeNotificationSettings:(id)arg1 ;
-(void)_queue_applicationsDidDenyNotificationSettings:(id)arg1 ;
-(void)_queue_removeClientForBundleIdentifier:(id)arg1 ;
-(void)applicationsDidAuthorizeNotificationSettings:(id)arg1 ;
-(void)applicationsDidDenyNotificationSettings:(id)arg1 ;
-(void)notificationSourcesDidInstall:(id)arg1 ;
-(void)_queue_addPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_setPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_removePendingNotificationRecordsWithIdentifiers:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_removeSimilarPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_removeAllPendingNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(id)_queue_pendingNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(id)_queue_undeliveredNotificationRequestsForBundleIdentifier:(id)arg1 ;
-(void)_queue_notificationSourcesDidInstall:(id)arg1 ;
-(void)_queue_applicationStateDidRestore;
-(void)_queue_localeDidChange;
-(void)_queue_timeDidChangeSignificantly;
-(id)_queue_clientForBundleIdentifier:(id)arg1 ;
-(id)_queue_addClientForNotificationSourceDescription:(id)arg1 ;

-(id)initWithNotificationRepository:(id)arg1 pendingNotificationRepository:(id)arg2 notificationScheduleRepository:(id)arg3 locationMonitor:(id)arg4 ; //iOS12+
-(id)initWithNotificationRepository:(id)arg1 pendingNotificationRepository:(id)arg2 locationMonitor:(id)arg3 ; //<=iOS11

-(void)addPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)setPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)removePendingNotificationRecordsWithIdentifiers:(id)arg1 forBundleIdentifier:(id)arg2 withCompletionHandler:(/*^block*/id)arg3 ;
-(void)removeSimilarPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)removeAllPendingNotificationRecordsForBundleIdentifier:(id)arg1 withCompletionHandler:(/*^block*/id)arg2 ;
-(id)pendingNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)applicationStateDidRestore;
-(void)timeDidChangeSignificantly;
@end

@protocol OS_dispatch_queue;
@class UNSKeyedDataStoreRepository, UNSKeyedObservable, NSObject;

@interface UNSPendingNotificationRepository : NSObject {
    
    UNSKeyedDataStoreRepository* _repository;
    UNSKeyedObservable* _observable;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(void)performMigration;
-(void)_queue_notificationSourcesDidUninstall:(id)arg1 ;
-(void)addObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(void)_queue_performMigration;
-(id)allBundleIdentifiers;
-(void)_queue_setPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)_queue_pendingNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)setPendingNotificationRecords:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)pendingNotificationRecordsForBundleIdentifier:(id)arg1 ;
-(void)applicationStateDidRestore;
-(long long)_maxObjectsPerKey;
-(id)initWithDataStoreRepository:(id)arg1 observable:(id)arg2 ;
-(id)_queue_pendingNotificationDictionariesForBundleIdentifier:(id)arg1 ;
-(void)_queue_setPendingNotificationDictionaries:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_notifyObserversOfChangesFrom:(id)arg1 to:(id)arg2 forBundleIdentifier:(id)arg3 ;
-(void)_queue_performMigrationForBundleIdentifier:(id)arg1 ;
-(void)removeObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)initWithDirectory:(id)arg1 ;
@end

@protocol OS_dispatch_queue;
@class UNSKeyedDictionaryRepository, NSObject;

@interface UNSNotificationScheduleRepository : NSObject {
    
    UNSKeyedDictionaryRepository* _repository;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(void)performMigration;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(void)_queue_performMigration;
-(id)allBundleIdentifiers;
-(void)_queue_performMigrationForBundleIdentifier:(id)arg1 ;
-(id)scheduleForBundleIdentifier:(id)arg1 ;
-(void)setSchedule:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)_queue_scheduleForBundleIdentifier:(id)arg1 ;
-(void)_queue_setSchedule:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)_queue_removeScheduleForBundleIdentifier:(id)arg1 ;
-(void)removeScheduleForBundleIdentifier:(id)arg1 ;
-(id)initWithDirectory:(id)arg1 ;
-(id)_dateFormatter;
@end

@protocol OS_dispatch_queue;
@class UNSKeyedDataStoreRepository, UNSKeyedObservable, NSObject;

@interface UNSNotificationTopicRepository : NSObject {
    
    UNSKeyedDataStoreRepository* _repository;
    UNSKeyedObservable* _observable;
    //NSObject*<OS_dispatch_queue> _queue;
    
}
-(void)_queue_notificationSourcesDidUninstall:(id)arg1 ;
-(void)addObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(void)notificationSourcesDidUninstall:(id)arg1 ;
-(id)allBundleIdentifiers;
-(long long)_maxObjectsPerKey;
-(id)initWithDataStoreRepository:(id)arg1 observable:(id)arg2 ;
-(void)removeObserver:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)topicsForBundleIdentifier:(id)arg1 ;
-(void)setTopics:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)_queue_topicsForBundleIdentifier:(id)arg1 ;
-(void)_queue_setTopics:(id)arg1 forBundleIdentifier:(id)arg2 ;
-(id)initWithDirectory:(id)arg1 ;
@end

@class NSString, NSURL, NSArray, UNSNotificationSourceSettingsDescription;

@interface UNSNotificationSourceDescription : NSObject {
    
    BOOL _allowCriticalAlerts;
    BOOL _allowPrivateProperties;
    BOOL _allowUnlimitedPendingNotifications;
    BOOL _allowUnlimitedContentBody;
    BOOL _hideSettings;
    BOOL _automaticallyShowSettings;
    BOOL _suppressDismissalSync;
    BOOL _suppressUserAuthorizationPrompt;
    BOOL _useDefaultDataProvider;
    BOOL _usesCloudKit;
    BOOL _supportsContentAvailableRemoteNotifications;
    BOOL _restricted;
    BOOL _daemonShouldReceiveBackgroundResponses;
    NSString* _bundleIdentifier;
    NSString* _universalApplicationIdentifier;
    NSString* _displayName;
    NSString* _pushEnvironment;
    NSString* _defaultIconFile;
    NSString* _settingsIconFile;
    NSString* _settingsSheetIconFile;
    NSString* _carPlayIconFile;
    NSString* _watchQuickLookSmallIconFile;
    NSString* _watchQuickLookLargeIconFile;
    NSString* _watchListSmallIconFile;
    NSString* _watchListLargeIconFile;
    NSString* _watchQuickLook394hIconFile;
    NSString* _watchQuickLook448hIconFile;
    NSString* _watchList394hIconFile;
    NSString* _watchList448hIconFile;
    NSURL* _bundleURL;
    NSURL* _dataContainerURL;
    NSArray* _defaultCategories;
    UNSNotificationSourceSettingsDescription* _defaultSettings;
    NSArray* _defaultTopics;
    
}

@property (nonatomic,copy) NSString * bundleIdentifier;                                               //@synthesize bundleIdentifier=_bundleIdentifier - In the implementation block
@property (nonatomic,copy) NSString * displayName;                                                    //@synthesize displayName=_displayName - In the implementation block
@property (nonatomic,copy) NSString * universalApplicationIdentifier;                                 //@synthesize universalApplicationIdentifier=_universalApplicationIdentifier - In the implementation block
@property (nonatomic,copy) NSString * pushEnvironment;                                                //@synthesize pushEnvironment=_pushEnvironment - In the implementation block
@property (nonatomic,copy) NSString * defaultIconFile;                                                //@synthesize defaultIconFile=_defaultIconFile - In the implementation block
@property (nonatomic,copy) NSString * settingsIconFile;                                               //@synthesize settingsIconFile=_settingsIconFile - In the implementation block
@property (nonatomic,copy) NSString * settingsSheetIconFile;                                          //@synthesize settingsSheetIconFile=_settingsSheetIconFile - In the implementation block
@property (nonatomic,copy) NSString * carPlayIconFile;                                                //@synthesize carPlayIconFile=_carPlayIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchQuickLookSmallIconFile;                                    //@synthesize watchQuickLookSmallIconFile=_watchQuickLookSmallIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchQuickLookLargeIconFile;                                    //@synthesize watchQuickLookLargeIconFile=_watchQuickLookLargeIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchListSmallIconFile;                                         //@synthesize watchListSmallIconFile=_watchListSmallIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchListLargeIconFile;                                         //@synthesize watchListLargeIconFile=_watchListLargeIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchQuickLook394hIconFile;                                     //@synthesize watchQuickLook394hIconFile=_watchQuickLook394hIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchQuickLook448hIconFile;                                     //@synthesize watchQuickLook448hIconFile=_watchQuickLook448hIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchList394hIconFile;                                          //@synthesize watchList394hIconFile=_watchList394hIconFile - In the implementation block
@property (nonatomic,copy) NSString * watchList448hIconFile;                                          //@synthesize watchList448hIconFile=_watchList448hIconFile - In the implementation block
@property (nonatomic,copy) NSURL * bundleURL;                                                         //@synthesize bundleURL=_bundleURL - In the implementation block
@property (nonatomic,copy) NSURL * dataContainerURL;                                                  //@synthesize dataContainerURL=_dataContainerURL - In the implementation block
@property (nonatomic,retain) NSArray * defaultCategories;                                             //@synthesize defaultCategories=_defaultCategories - In the implementation block
@property (nonatomic,retain) UNSNotificationSourceSettingsDescription * defaultSettings;              //@synthesize defaultSettings=_defaultSettings - In the implementation block
@property (nonatomic,retain) NSArray * defaultTopics;                                                 //@synthesize defaultTopics=_defaultTopics - In the implementation block
@property (assign,nonatomic) BOOL automaticallyShowSettings;                                          //@synthesize automaticallyShowSettings=_automaticallyShowSettings - In the implementation block
@property (assign,nonatomic) BOOL hideSettings;                                                       //@synthesize hideSettings=_hideSettings - In the implementation block
@property (assign,nonatomic) BOOL useDefaultDataProvider;                                             //@synthesize useDefaultDataProvider=_useDefaultDataProvider - In the implementation block
@property (assign,nonatomic) BOOL suppressDismissalSync;                                              //@synthesize suppressDismissalSync=_suppressDismissalSync - In the implementation block
@property (assign,nonatomic) BOOL suppressUserAuthorizationPrompt;                                    //@synthesize suppressUserAuthorizationPrompt=_suppressUserAuthorizationPrompt - In the implementation block
@property (assign,nonatomic) BOOL allowCriticalAlerts;                                                //@synthesize allowCriticalAlerts=_allowCriticalAlerts - In the implementation block
@property (assign,nonatomic) BOOL allowPrivateProperties;                                             //@synthesize allowPrivateProperties=_allowPrivateProperties - In the implementation block
@property (assign,nonatomic) BOOL allowUnlimitedPendingNotifications;                                 //@synthesize allowUnlimitedPendingNotifications=_allowUnlimitedPendingNotifications - In the implementation block
@property (assign,nonatomic) BOOL allowUnlimitedContentBody;                                          //@synthesize allowUnlimitedContentBody=_allowUnlimitedContentBody - In the implementation block
@property (assign,nonatomic) BOOL usesCloudKit;                                                       //@synthesize usesCloudKit=_usesCloudKit - In the implementation block
@property (assign,nonatomic) BOOL supportsContentAvailableRemoteNotifications;                        //@synthesize supportsContentAvailableRemoteNotifications=_supportsContentAvailableRemoteNotifications - In the implementation block
@property (assign,getter=isRestricted,nonatomic) BOOL restricted;                                     //@synthesize restricted=_restricted - In the implementation block
@property (assign,nonatomic) BOOL daemonShouldReceiveBackgroundResponses;                             //@synthesize daemonShouldReceiveBackgroundResponses=_daemonShouldReceiveBackgroundResponses - In the implementation block
+(id)systemSourceDescriptionWithBundleURL:(id)arg1 ;
+(id)applicationSourceDescriptionWithApplication:(id)arg1 ;
+(id)_validEnvironmentFromEnvironment:(id)arg1 ;
+(id)descriptionWithBundleIdentifier:(id)arg1 path:(id)arg2 ;
-(void)setDisplayName:(NSString *)arg1 ;
-(NSArray *)defaultCategories;
-(void)setBundleURL:(NSURL *)arg1 ;
-(UNSNotificationSourceSettingsDescription *)defaultSettings;
-(void)setRestricted:(BOOL)arg1 ;
-(NSString *)pushEnvironment;
-(void)setPushEnvironment:(NSString *)arg1 ;
-(BOOL)supportsContentAvailableRemoteNotifications;
-(BOOL)usesCloudKit;
-(BOOL)allowUnlimitedPendingNotifications;
-(BOOL)useDefaultDataProvider;
-(BOOL)suppressUserAuthorizationPrompt;
-(BOOL)allowCriticalAlerts;
-(void)setDataContainerURL:(NSURL *)arg1 ;
-(void)setUsesCloudKit:(BOOL)arg1 ;
-(void)setAllowCriticalAlerts:(BOOL)arg1 ;
-(void)setSupportsContentAvailableRemoteNotifications:(BOOL)arg1 ;
-(void)setSystemPropertiesFromDictionary:(id)arg1 bundle:(id)arg2 ;
-(void)setSuppressUserAuthorizationPrompt:(BOOL)arg1 ;
-(void)setAllowUnlimitedPendingNotifications:(BOOL)arg1 ;
-(void)setAllowPrivateProperties:(BOOL)arg1 ;
-(void)setUseDefaultDataProvider:(BOOL)arg1 ;
-(NSString *)defaultIconFile;
-(NSString *)settingsIconFile;
-(NSString *)settingsSheetIconFile;
-(NSString *)carPlayIconFile;
-(NSString *)watchQuickLookSmallIconFile;
-(NSString *)watchQuickLookLargeIconFile;
-(NSString *)watchListSmallIconFile;
-(NSString *)watchListLargeIconFile;
-(NSString *)watchQuickLook394hIconFile;
-(NSString *)watchQuickLook448hIconFile;
-(NSString *)watchList394hIconFile;
-(NSString *)watchList448hIconFile;
-(NSString *)universalApplicationIdentifier;
-(NSArray *)defaultTopics;
-(BOOL)automaticallyShowSettings;
-(BOOL)hideSettings;
-(BOOL)suppressDismissalSync;
-(BOOL)allowUnlimitedContentBody;
-(BOOL)allowPrivateProperties;
-(void)setDefaultCategoriesFromArray:(id)arg1 bundle:(id)arg2 ;
-(void)setDefaultSettings:(UNSNotificationSourceSettingsDescription *)arg1 ;
-(void)setDefaultTopicsFromArray:(id)arg1 bundle:(id)arg2 ;
-(void)setIconFilesFromDictionary:(id)arg1 ;
-(void)setAutomaticallyShowSettings:(BOOL)arg1 ;
-(void)setHideSettings:(BOOL)arg1 ;
-(void)setUniversalApplicationIdentifier:(NSString *)arg1 ;
-(void)setSuppressDismissalSync:(BOOL)arg1 ;
-(void)setAllowUnlimitedContentBody:(BOOL)arg1 ;
-(void)setDaemonShouldReceiveBackgroundResponses:(BOOL)arg1 ;
-(void)setDefaultIconFile:(NSString *)arg1 ;
-(void)setSettingsIconFile:(NSString *)arg1 ;
-(void)setSettingsSheetIconFile:(NSString *)arg1 ;
-(void)setCarPlayIconFile:(NSString *)arg1 ;
-(void)setWatchQuickLookSmallIconFile:(NSString *)arg1 ;
-(void)setWatchQuickLookLargeIconFile:(NSString *)arg1 ;
-(void)setWatchListSmallIconFile:(NSString *)arg1 ;
-(void)setWatchListLargeIconFile:(NSString *)arg1 ;
-(void)setWatchQuickLook394hIconFile:(NSString *)arg1 ;
-(void)setWatchQuickLook448hIconFile:(NSString *)arg1 ;
-(void)setWatchList394hIconFile:(NSString *)arg1 ;
-(void)setWatchList448hIconFile:(NSString *)arg1 ;
-(void)setDefaultCategories:(NSArray *)arg1 ;
-(void)setDefaultTopics:(NSArray *)arg1 ;
-(BOOL)daemonShouldReceiveBackgroundResponses;
-(BOOL)isEqual:(id)arg1 ;
-(NSString *)bundleIdentifier;
-(unsigned long long)hash;
-(id)description;
-(NSString *)displayName;
-(BOOL)isRestricted;
-(NSURL *)bundleURL;
-(NSURL *)dataContainerURL;
-(void)setBundleIdentifier:(NSString *)arg1 ;
@end
