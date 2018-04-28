//
//  MAURBackgroundSync.h
//
//  Created by Marian Hello on 07/07/16.
//  Copyright © 2016 mauron85. All rights reserved.
//

#ifndef MAURBackgroundSync_h
#define MAURBackgroundSync_h

#import <Foundation/Foundation.h>

@interface MAURBackgroundSync : NSObject

- (instancetype) init;
- (NSString*) status;
- (void) sync:(NSString*)url onLocationThreshold:(NSInteger)threshold withTemplate:(id)locationTemplate withHttpHeaders:(NSMutableDictionary*)httpHeaders;
- (void) cancel;

@end

#endif /* MAURBackgroundSync_h */
