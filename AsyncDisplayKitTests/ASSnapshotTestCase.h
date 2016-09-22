//
//  ASSnapshotTestCase.h
//  AsyncDisplayKit
//
//  Copyright (c) 2014-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//

#import <FBSnapshotTestCase/FBSnapshotTestCase.h>

#if __LP64__
#define AS_64 1
#else
#define AS_64 0
#endif

/**
 Maps platform to reference image directory suffix
 */
#define ASSnapshotReferenceDirectorySuffix() \
({ \
NSString *suffix = \
AS_AT_LEAST_IOS10 ? @"_IOS10" : \
AS_AT_LEAST_IOS9 ? @"_IOS9" : \
AS_AT_LEAST_IOS8 ? @"_IOS8" : \
@""; \
AS_64 ? [suffix stringByAppendingString:@"_64"] : suffix; \
})

@class ASDisplayNode;

#define ASSnapshotVerifyNode(node__, identifier__) \
{ \
  [ASSnapshotTestCase hackilySynchronouslyRecursivelyRenderNode:node__]; \
  FBSnapshotVerifyLayer(node__.layer, identifier__); \
  [node__ setShouldRasterizeDescendants:YES]; \
  [ASSnapshotTestCase hackilySynchronouslyRecursivelyRenderNode:node__]; \
  FBSnapshotVerifyLayer(node__.layer, identifier__); \
  [node__ setShouldRasterizeDescendants:NO]; \
  [ASSnapshotTestCase hackilySynchronouslyRecursivelyRenderNode:node__]; \
  FBSnapshotVerifyLayer(node__.layer, identifier__); \
}

#define ASSnapshotVerifyLayerWithOptions(layer__, identifier__, suffixes__, tolerance__) \
  ASSnapshotVerifyViewOrLayerWithOptions(Layer, layer__, identifier__, suffixes__, tolerance__)

#define ASSnapshotVerifyLayer(layer__, identifier__) \
  ASSnapshotVerifyLayerWithOptions(layer__, identifier__, FBSnapshotTestCaseDefaultSuffixes(), 0)

#define ASSnapshotVerifyViewOrLayerWithOptions(what__, viewOrLayer__, identifier__, suffixes__, tolerance__) \
{ \
  NSString *referenceImagesDirectory = [NSString stringWithFormat:@"%@%@", [self getReferenceImageDirectoryWithDefault:(@ FB_REFERENCE_IMAGE_DIR)], ASSnapshotReferenceDirectorySuffix()]; \
  \
  XCTAssertTrue((suffixes__.count > 0), @"Suffixes set cannot be empty %@", suffixes__); \
  \
  BOOL testSuccess__ = NO; \
  NSError *error__ = nil; \
  NSMutableArray *errors__ = [NSMutableArray array]; \
  \
  if (self.recordMode) { \
    \
    NSString *referenceImagesDirectory__ = [NSString stringWithFormat:@"%@%@", referenceImagesDirectory, suffixes__.firstObject]; \
    BOOL referenceImageSaved__ = [self compareSnapshotOf ## what__ :(viewOrLayer__) referenceImagesDirectory:referenceImagesDirectory__ identifier:(identifier__) tolerance:(tolerance__) error:&error__]; \
    if (!referenceImageSaved__) { \
      [errors__ addObject:error__]; \
    } \
  } else { \
    \
    for (NSString *suffix__ in suffixes__) { \
      NSString *referenceImagesDirectory__ = [NSString stringWithFormat:@"%@%@", referenceImagesDirectory, suffix__]; \
      BOOL referenceImageAvailable = [self referenceImageRecordedInDirectory:referenceImagesDirectory__ identifier:(identifier__) error:&error__]; \
      \
      if (referenceImageAvailable) { \
        BOOL comparisonSuccess__ = [self compareSnapshotOf ## what__ :(viewOrLayer__) referenceImagesDirectory:referenceImagesDirectory__ identifier:(identifier__) tolerance:(tolerance__) error:&error__]; \
        [errors__ removeAllObjects]; \
        if (comparisonSuccess__) { \
          testSuccess__ = YES; \
          break; \
        } else { \
          [errors__ addObject:error__]; \
        } \
      } else { \
        [errors__ addObject:error__]; \
      } \
    } \
  } \
  XCTAssertTrue(testSuccess__, @"Snapshot comparison failed: %@", errors__.firstObject); \
  XCTAssertFalse(self.recordMode, @"Test ran in record mode. Reference image is now saved. Disable record mode to perform an actual snapshot comparison!"); \
}


@interface ASSnapshotTestCase : FBSnapshotTestCase

/**
 * Hack for testing.  ASDisplayNode lacks an explicit -render method, so we manually hit its layout & display codepaths.
 */
+ (void)hackilySynchronouslyRecursivelyRenderNode:(ASDisplayNode *)node;

/**
 Returns a default set of strings that is used to append a suffix based on the architectures and OS.
 
 @returns An @c NSOrderedSet object containing strings that are appended to the reference images directory.
 */
NSOrderedSet *ASSnapshotTestCaseDefaultSuffixes(void);

@end
