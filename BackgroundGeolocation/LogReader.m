//
//  LogReader.m
//  BackgroundGeolocation
//
//  Created by Marian Hello on 02/07/16.
//  Copyright © 2016 mauron85. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sqlite3.h>
#import "CocoaLumberjack.h"
#import "FMDB.h"
#import "LogReader.h"

// Convert DDLogFlag to string
static NSString* logFlag_toString(DDLogFlag logFlag)
{
    switch (logFlag) {
        case DDLogFlagVerbose:
            return @"TRACE";
        case DDLogFlagDebug:
            return @"DEBUG";
        case DDLogFlagInfo:
            return @"INFO";
        case DDLogFlagWarning:
            return @"WARN";
        case DDLogFlagError:
            return @"ERROR";
    }
    return @"N/A";
}

static DDLogFlag string_toLogFlag(NSString *logFlag)
{
    if ([@"TRACE" isEqualToString:logFlag]) {
        return DDLogFlagVerbose;
    }
    if ([@"DEBUG" isEqualToString:logFlag]) {
        return DDLogFlagDebug;
    }
    if ([@"INFO" isEqualToString:logFlag]) {
        return DDLogFlagInfo;
    }
    if ([@"WARN" isEqualToString:logFlag]) {
        return DDLogFlagWarning;
    }
    if ([@"ERROR" isEqualToString:logFlag]) {
        return DDLogFlagError;
    }

    return DDLogFlagVerbose; // maybe we should throw exception instead
}

@implementation LogReader : NSObject

- (id)initWithLogDirectory:(NSString *)aLogDirectory
{
    if ((self = [super init]))
    {
        logDirectory = [aLogDirectory copy];
    }
    
    return self;
}

- (NSArray*) getLogEntries:(NSInteger)limit startAtOffset:(NSInteger)offset minLogLevelAsString:(NSString *)minLogLevel;
{
    return [self getEntries:limit startAtOffset:offset minLogLevel:string_toLogFlag(minLogLevel)];
}

- (NSArray*) getEntries:(NSInteger)limit startAtOffset:(NSInteger)offset minLogLevel:(DDLogFlag)minLogLevel;
{
    NSMutableArray *logs = [[NSMutableArray alloc] init];
    NSString *dbPath = [logDirectory stringByAppendingPathComponent:@"log.sqlite"];
    FMDatabase *database = [[FMDatabase alloc] initWithPath:dbPath];
    if (![database openWithFlags:SQLITE_OPEN_READONLY]) {
        NSLog(@"%@: Failed opening database!", [self class]);
        database = nil;
        return nil;
    }

    NSString *sql = [NSString stringWithFormat:@"SELECT ROWID, context, level, message, timestamp FROM logs WHERE level <= %d ORDER BY timestamp %@ LIMIT %ld OFFSET %ld", (int)minLogLevel, limit >= 0 ? @"DESC" : @"ASC", (long)ABS(limit), (long)offset];
    FMResultSet *rs = [database executeQuery:sql];
    while([rs next]) {
        NSMutableDictionary *entry = [NSMutableDictionary dictionaryWithCapacity:4];
        [entry setObject:[NSNumber numberWithInt:[rs intForColumnIndex:0]] forKey:@"rowid"];
        [entry setObject:[NSNumber numberWithInt:[rs intForColumnIndex:1]] forKey:@"context"];
        [entry setObject:logFlag_toString([rs intForColumnIndex:2]) forKey:@"level"];
        [entry setObject:[rs stringForColumnIndex:3] forKey:@"message"];
        [entry setObject:[NSNumber numberWithDouble:[rs doubleForColumnIndex:4] * 1000] forKey:@"timestamp"];
        [logs addObject:entry];
    }
    [rs close];
    [database close];
    
    return logs;
}

@end
