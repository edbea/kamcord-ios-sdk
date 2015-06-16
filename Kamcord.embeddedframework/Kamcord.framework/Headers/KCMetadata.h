//
//  KCMetaData.h
//  Kamcord
//
//  Created by Sam Green on 4/15/15.
//  Copyright (c) 2015 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Kamcord-C-Interface.h"

/**
 *
 * This class represents one piece of video metadata.
 *
 * This class is immutable.
 *
 */
@interface KCMetadata : NSObject


/**
 *
 * The type of the metadata value
 *
 */
@property (nonatomic, readonly) KCMetadataValueType type;

/**
 *
 * The comparator used for searching the metadata
 *
 */
@property (nonatomic) KCMetadataCompareType compareType;

/**
 *
 * The key for this metadata's value
 *
 */
@property (nonatomic, readonly, copy) NSString *key;

/**
 *
 * The value of this metadata as a string
 *
 */
@property (nonatomic, readonly, copy) NSString *value;

/**
 *
 * The value of this metadata as an NSNumber
 *
 */
@property (nonatomic, readonly) NSNumber *numericValue;

/**
 *
 *  Convenience properties (these will transform the value prior to returning it)
 *
 */
@property (nonatomic, readonly) double doubleValue;
@property (nonatomic, readonly) NSInteger integerValue;
@property (nonatomic, readonly) NSString *stringValue;
@property (nonatomic, readonly) NSDictionary *dictionaryValue;

/**
 *
 * Whether this metadata value represents a tag or not
 *
 */
@property (nonatomic, readonly, getter=isTag) BOOL tag;

/**
 *
 * Whether this metadata value represents a keyword or not
 *
 */
@property (nonatomic, readonly, getter=isKeyword) BOOL keyword;


/**
 *
 * Initialize this metadata object.
 *
 * Contraints:
 *
 * The key and value must be non-nil. If they are nil, an assert will be 
 * triggered at runtime for debug builds.
 *
 * The key **cannot** be longer than 50 characters.
 *
 * The value **cannot** be longer than 150 characters.
 *
 * A video **cannot•• have more than 25 key-value pairs.
 *
 */
+ (instancetype)metadataWithKey:(NSString *)key andStringValue:(NSString *)value;
+ (instancetype)metadataWithKey:(NSString *)key andDoubleValue:(double)value;
+ (instancetype)metadataWithKey:(NSString *)key andIntegerValue:(NSInteger)value;

/**
 *
 * Tags for videos
 *
 */
+ (instancetype)metadataWithTag:(NSString *)tag;

/**
 *
 * Keywords for videos
 *
 */
+ (instancetype)metadataWithKeyword:(NSString *)keyword;

@end
