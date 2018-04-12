//
//  LogReader.h
//  BackgroundGeolocation
//
//  Created by Marian Hello on 02/07/16.
//  Copyright © 2016 mauron85. All rights reserved.
//

#ifndef LogReader_h
#define LogReader_h

#define LOG_LEVEL_DEF ddLogLevel

@interface LogReader : NSObject {
@private
    NSString *logDirectory;
}

- (id)initWithLogDirectory:(NSString *)aLogDirectory;
- (NSArray*) getEntries:(NSInteger)limit startAtOffset:(NSInteger)offset minLogLevel:(DDLogFlag)minLogLevel;
- (NSArray*) getLogEntries:(NSInteger)limit startAtOffset:(NSInteger)offset minLogLevelAsString:(NSString *)minLogLevel;

@end

#endif /* LogReader_h */
