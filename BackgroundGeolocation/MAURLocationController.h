//
//  MAURLocationController.h
//
//  Created by Jinru on 12/19/09.
//  Copyright 2009 Arizona State University. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "MAURProviderDelegate.h"

// protocol for sending location updates to another view controller
@protocol LocationControllerDelegate
@required
- (void) onAuthorizationChanged:(BGAuthorizationStatus)authStatus;
- (void) onLocationsChanged:(NSArray*)locations;
- (void) onError:(NSError*)error;
- (void) onLocationPause:(CLLocationManager*)manager;
- (void) onLocationResume:(CLLocationManager*)manager;
@end

@interface MAURLocationController : NSObject <CLLocationManagerDelegate>  {
    
    CLLocationManager* locationManager;
    __weak id delegate;
}

@property (nonatomic, strong) CLLocationManager* locationManager;
@property (nonatomic, weak) id  delegate;

- (BOOL) start:(NSError * __autoreleasing *)outError;
- (BOOL) stop:(NSError * __autoreleasing *)outError;
- (BOOL) startMonitoringSignificantLocationChanges;
- (BOOL) stopMonitoringSignificantLocationChanges;
//- (void) startMonitoringForRegion:(CLRegion*)region;
//- (void) stopMonitoringForRegion:(CLRegion*)region;
- (void) setPausesLocationUpdatesAutomatically:(BOOL)newPausesLocationsUpdatesAutomatically;
- (BOOL) pausesLocationUpdatesAutomatically;
- (void) setDistanceFilter:(CLLocationDistance)newDistanceFiler;
- (CLLocationDistance) distanceFilter;
- (void) setActivityType:(CLActivityType)newActivityType;
- (CLActivityType) activityType;
- (void) setDesiredAccuracy:(CLLocationAccuracy)newDesiredAccuracy;
- (CLLocationAccuracy) desiredAccuracy;

+ (MAURLocationController*)sharedInstance; // Singleton method

@end
