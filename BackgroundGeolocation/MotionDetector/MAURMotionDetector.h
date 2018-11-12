//
//  MAURMotionDetector.h
//  MotionDetection
//
// The MIT License (MIT)
//
// Created by : arturdev
// Copyright (c) 2014 SocialObjects Software. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

#import <Foundation/Foundation.h>
#import <SOMotionDetector/SOLocationManager.h>
#import "MAURMotionActivity.h"
#import <CoreMotion/CoreMotion.h>

@class MAURMotionDetector;

@protocol MAURMotionDetectorDelegate <NSObject>

@optional
- (void)motionDetector:(MAURMotionDetector *)motionDetector activityTypeChanged:(MAURMotionActivity *)motionActivity;
- (void)motionDetector:(MAURMotionDetector *)motionDetector locationChanged:(CLLocation *)location;
- (void)motionDetector:(MAURMotionDetector *)motionDetector accelerationChanged:(CMAcceleration)acceleration;
- (void)motionDetector:(MAURMotionDetector *)motionDetector locationWasPaused:(BOOL)changed;

@end

@interface MAURMotionDetector : NSObject

#pragma mark - Singleton
+ (MAURMotionDetector *)sharedInstance;

#pragma mark - Properties
@property (weak, nonatomic) id<MAURMotionDetectorDelegate> delegate;

@property (copy) void (^activityTypeChangedBlock) (MAURMotionActivity *motionActivity);
@property (copy) void (^locationChangedBlock) (CLLocation *location);
@property (copy) void (^accelerationChangedBlock) (CMAcceleration acceleration);
@property (copy) void (^locationWasPausedBlock) (BOOL changed);

@property (nonatomic, readonly) MAURMotionActivity *motionActivity;
@property (nonatomic, readonly) double currentSpeed;
@property (nonatomic, readonly) CMAcceleration acceleration;
@property (nonatomic, readonly) BOOL isShaking;


#pragma mark - Methods
- (void)startDetection;
- (void)stopDetection;

#pragma mark - Customization Methods

/**
 * Set this parameter to YES if you want to use M7 chip to detect more exact motion type. By default is No.
 * Set this parameter before calling startDetection method.
 * Available only on devices that have M7 chip. At this time only the iPhone 5S, iPhone6/6plus, the iPad Air and iPad mini with retina display have the M7 coprocessor.
 */
@property (nonatomic) BOOL useM7IfAvailable NS_AVAILABLE_IOS(7_0);

@property (nonatomic) double activityDetectionInterval;

/**
 *@param speed  The minimum speed value less than which will be considered as not moving state
 */
- (void)setMinimumSpeed:(CGFloat)speed;

/**
 *@param speed  The maximum speed value more than which will be considered as running state
 */
- (void)setMaximumWalkingSpeed:(CGFloat)speed;

/**
 *@param speed  The maximum speed value more than which will be considered as automotive state
 */
- (void)setMaximumRunningSpeed:(CGFloat)speed;

/**
 *@param acceleration  The minimum acceleration value less than which will be considered as non shaking state
 */
- (void)setMinimumRunningAcceleration:(CGFloat)acceleration;


@end
