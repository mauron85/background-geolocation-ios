//
//  MAURPostLocationTask.h
//  BackgroundGeolocation
//
//  Created by Marian Hello on 27/04/2018.
//  Copyright © 2018 mauron85. All rights reserved.
//

#ifndef MAURPostLocationTask_h
#define MAURPostLocationTask_h

#import "MAURConfig.h"
#import "MAURLocation.h"

@interface MAURPostLocationTask : NSObject

@property (nonatomic, weak) MAURConfig  *config;

- (void) add:(MAURLocation*)location;
- (void) start;
- (void) stop;

@end

#endif /* MAURPostLocationTask_h */
