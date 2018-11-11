#import <Foundation/Foundation.h>
#if __has_include(<CocoaLumberjack/CocoaLumberjack.h>)
#import <CocoaLumberjack/CocoaLumberjack.h>
#else
#import "CocoaLumberjack.h"
#endif
#if __has_include(<CocoaLumberjack/DDAbstractDatabaseLogger.h>)
#import <CocoaLumberjack/DDAbstractDatabaseLogger.h>
#else
#import "DDAbstractDatabaseLogger.h"
#endif


@class FMDatabase;


@interface FMDBLogger : DDAbstractDatabaseLogger <DDLogger>
{
@private
    NSString *logDirectory;
    NSMutableArray *pendingLogEntries;
    
    FMDatabase *database;
}

/**
 * Initializes an instance set to save it's sqlite file to the given directory.
 * If the directory doesn't already exist, it is automatically created.
 **/
- (id)initWithLogDirectory:(NSString *)logDirectory;

//
// This class inherits from DDAbstractDatabaseLogger.
//
// So there are a bunch of options such as:
//
// @property (assign, readwrite) NSUInteger saveThreshold;
// @property (assign, readwrite) NSTimeInterval saveInterval;
//
// @property (assign, readwrite) NSTimeInterval maxAge;
// @property (assign, readwrite) NSTimeInterval deleteInterval;
// @property (assign, readwrite) BOOL deleteOnEverySave;
//
// And methods such as:
//
// - (void)savePendingLogEntries;
// - (void)deleteOldLogEntries;
//
// These options and methods are documented extensively in DDAbstractDatabaseLogger.h
//

@end
