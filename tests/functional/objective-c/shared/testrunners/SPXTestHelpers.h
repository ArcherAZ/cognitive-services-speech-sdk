//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//

#ifndef SPXTestHelpers_h
#define SPXTestHelpers_h

@interface SPXTestHelpers : NSObject
+ (NSString *) normalizeText:(NSString *) input;
+ (double) levenshteinSimilarityRatio:(NSString *)stringA withString:(NSString *)stringB;
+ (NSUInteger) levenshteinDistance:(NSString *)stringA to:(NSString *)stringB;

@end
#endif /* SPXTestHelpers_h */