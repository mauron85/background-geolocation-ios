//
//  MAURRawLocationProvider.m
//  BackgroundGeolocation
//
//  Created by Marian Hello on 06/11/2017.
//  Copyright © 2017 mauron85. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MAURRawLocationProvider.h"
#import "MAURLocationController.h"
#import "MAURLogging.h"

static NSString * const TAG = @"RawLocationProvider";
static NSString * const Domain = @"com.marianhello";

@implementation MAURRawLocationProvider {

    BOOL isStarted;
    MAURLocationController *locationController;
}

- (instancetype) init
{
    self = [super init];

    if (self) {
        isStarted = NO;
    }

    return self;
}

- (void) onCreate {
    locationController = [MAURLocationController sharedInstance];
    locationController.delegate = self;
}

- (BOOL) onConfigure:(MAURConfig*)config error:(NSError * __autoreleasing *)outError
{
    DDLogVerbose(@"%@ configure", TAG);

    locationController.pausesLocationUpdatesAutomatically = [config pauseLocationUpdates];
    locationController.activityType = [config decodeActivityType];
    locationController.distanceFilter = config.distanceFilter.integerValue; // meters
    locationController.desiredAccuracy = [config decodeDesiredAccuracy];

    return YES;
}

- (BOOL) onStart:(NSError * __autoreleasing *)outError
{
    DDLogInfo(@"%@ will start", TAG);

    if (!isStarted) {
        [locationController stopMonitoringSignificantLocationChanges];
        isStarted = [locationController start:outError];
    }

    return isStarted;
}

- (BOOL) onStop:(NSError * __autoreleasing *)outError
{
    DDLogInfo(@"%@ will stop", TAG);

    if (!isStarted) {
        return YES;
    }

    [locationController stopMonitoringSignificantLocationChanges];
    if ([locationController stop:outError]) {
        isStarted = NO;
        return YES;
    }

    return NO;
}

- (void) onTerminate
{
    if (isStarted) {
        [locationController startMonitoringSignificantLocationChanges];
    }
}

- (void) onAuthorizationChanged:(BGAuthorizationStatus)authStatus
{
    [self.delegate onAuthorizationChanged:authStatus];
}

- (void) onLocationsChanged:(NSArray*)locations
{
    for (CLLocation *location in locations) {
        MAURLocation *bgloc = [MAURLocation fromCLLocation:location];
        [self.delegate onLocationChanged:bgloc];
    }
}

- (void) onError:(NSError*)error
{
    [self.delegate onError:error];
}

- (void) onPause:(CLLocationManager*)manager
{
    [self.delegate onLocationPause];
}

- (void) onResume:(CLLocationManager*)manager
{
    [self.delegate onLocationResume];
}

- (void) onDestroy {
    DDLogInfo(@"Destroying %@ ", TAG);
    [self onStop:nil];
}

- (void) dealloc
{
    //    locationController.delegate = nil;
}

@end

