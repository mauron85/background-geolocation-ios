//
//  MAURMotionActivity.h
//  BackgroundGeolocation
//
//  Created by Marian Hello on 13/12/2017.
//  Copyright © 2017 mauron85. All rights reserved.
//

#ifndef MAURMotionActivity_h
#define MAURMotionActivity_h

#import <Foundation/Foundation.h>

typedef enum
{
    MotionTypeNotMoving = 1,
    MotionTypeWalking,
    MotionTypeRunning,
    MotionTypeAutomotive,
    MotionTypeUnknown
} MAURMotionType;

@interface MAURMotionActivity : NSObject <NSCopying>

@property int confidence;
@property MAURMotionType motionType;

@end

#endif /* MAURMotionActivity_h */
