//
//  LogReader.h
//  BackgroundGeolocation
//
//  Created by Marian Hello on 02/07/16.
//  Copyright © 2016 mauron85. All rights reserved.
//

#ifndef LogReader_h
#define LogReader_h

#import "Logging.h"

@interface LogReader : NSObject {
@private
    NSString *logDirectory;
}

- (id)initWithLogDirectory:(NSString *)aLogDirectory;
- (NSString*) prepareSQL:(NSInteger)limit fromLogEntryId:(NSInteger)entryId minLogLevel:(NSInteger)minLogLevel;
- (NSArray*) getEntries:(NSInteger)limit fromLogEntryId:(NSInteger)entryId minLogLevel:(DDLogFlag)minLogLevel;
- (NSArray*) getLogEntries:(NSInteger)limit fromLogEntryId:(NSInteger)offset minLogLevelAsString:(NSString *)minLogLevel;

@end

#endif /* LogReader_h */
