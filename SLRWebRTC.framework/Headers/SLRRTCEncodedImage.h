/*
 *  Copyright 2017 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#import <Foundation/Foundation.h>

#import "SLRRTCMacros.h"
#import "SLRRTCVideoFrame.h"

NS_ASSUME_NONNULL_BEGIN

/** Represents an encoded frame's type. */
typedef NS_ENUM(NSUInteger, SLRRTCFrameType) {
  SLRRTCFrameTypeEmptyFrame = 0,
  SLRRTCFrameTypeAudioFrameSpeech = 1,
  SLRRTCFrameTypeAudioFrameCN = 2,
  SLRRTCFrameTypeVideoFrameKey = 3,
  SLRRTCFrameTypeVideoFrameDelta = 4,
};

typedef NS_ENUM(NSUInteger, SLRRTCVideoContentType) {
  SLRRTCVideoContentTypeUnspecified,
  SLRRTCVideoContentTypeScreenshare,
};

/** Represents an encoded frame. Corresponds to webrtc::EncodedImage. */
RTC_OBJC_EXPORT
@interface SLRRTCEncodedImage : NSObject

@property(nonatomic, strong) NSData *buffer;
@property(nonatomic, assign) int32_t encodedWidth;
@property(nonatomic, assign) int32_t encodedHeight;
@property(nonatomic, assign) uint32_t timeStamp;
@property(nonatomic, assign) int64_t captureTimeMs;
@property(nonatomic, assign) int64_t ntpTimeMs;
@property(nonatomic, assign) uint8_t flags;
@property(nonatomic, assign) int64_t encodeStartMs;
@property(nonatomic, assign) int64_t encodeFinishMs;
@property(nonatomic, assign) SLRRTCFrameType frameType;
@property(nonatomic, assign) SLRRTCVideoRotation rotation;
@property(nonatomic, assign) BOOL completeFrame;
@property(nonatomic, strong) NSNumber *qp;
@property(nonatomic, assign) SLRRTCVideoContentType contentType;

@end

NS_ASSUME_NONNULL_END
