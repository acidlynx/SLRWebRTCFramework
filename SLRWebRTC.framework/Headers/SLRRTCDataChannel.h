/*
 *  Copyright 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#import <AvailabilityMacros.h>
#import <Foundation/Foundation.h>

#import "SLRRTCMacros.h"

NS_ASSUME_NONNULL_BEGIN

RTC_OBJC_EXPORT
@interface SLRRTCDataBuffer : NSObject

/** NSData representation of the underlying buffer. */
@property(nonatomic, readonly) NSData *data;

/** Indicates whether |data| contains UTF-8 or binary data. */
@property(nonatomic, readonly) BOOL isBinary;

- (instancetype)init NS_UNAVAILABLE;

/**
 * Initialize an SLRRTCDataBuffer from NSData. |isBinary| indicates whether |data|
 * contains UTF-8 or binary data.
 */
- (instancetype)initWithData:(NSData *)data isBinary:(BOOL)isBinary;

@end

@class SLRRTCDataChannel;
RTC_OBJC_EXPORT
@protocol SLRRTCDataChannelDelegate <NSObject>

/** The data channel state changed. */
- (void)dataChannelDidChangeState:(SLRRTCDataChannel *)dataChannel;

/** The data channel successfully received a data buffer. */
- (void)dataChannel:(SLRRTCDataChannel *)dataChannel
    didReceiveMessageWithBuffer:(SLRRTCDataBuffer *)buffer;

@optional
/** The data channel's |bufferedAmount| changed. */
- (void)dataChannel:(SLRRTCDataChannel *)dataChannel didChangeBufferedAmount:(uint64_t)amount;

@end

/** Represents the state of the data channel. */
typedef NS_ENUM(NSInteger, SLRRTCDataChannelState) {
  SLRRTCDataChannelStateConnecting,
  SLRRTCDataChannelStateOpen,
  SLRRTCDataChannelStateClosing,
  SLRRTCDataChannelStateClosed,
};

RTC_OBJC_EXPORT
@interface SLRRTCDataChannel : NSObject

/**
 * A label that can be used to distinguish this data channel from other data
 * channel objects.
 */
@property(nonatomic, readonly) NSString *label;

/** Whether the data channel can send messages in unreliable mode. */
@property(nonatomic, readonly) BOOL isReliable DEPRECATED_ATTRIBUTE;

/** Returns whether this data channel is ordered or not. */
@property(nonatomic, readonly) BOOL isOrdered;

/** Deprecated. Use maxPacketLifeTime. */
@property(nonatomic, readonly) NSUInteger maxRetransmitTime DEPRECATED_ATTRIBUTE;

/**
 * The length of the time window (in milliseconds) during which transmissions
 * and retransmissions may occur in unreliable mode.
 */
@property(nonatomic, readonly) uint16_t maxPacketLifeTime;

/**
 * The maximum number of retransmissions that are attempted in unreliable mode.
 */
@property(nonatomic, readonly) uint16_t maxRetransmits;

/**
 * The name of the sub-protocol used with this data channel, if any. Otherwise
 * this returns an empty string.
 */
@property(nonatomic, readonly) NSString *protocol;

/**
 * Returns whether this data channel was negotiated by the application or not.
 */
@property(nonatomic, readonly) BOOL isNegotiated;

/** Deprecated. Use channelId. */
@property(nonatomic, readonly) NSInteger streamId DEPRECATED_ATTRIBUTE;

/** The identifier for this data channel. */
@property(nonatomic, readonly) int channelId;

/** The state of the data channel. */
@property(nonatomic, readonly) SLRRTCDataChannelState readyState;

/**
 * The number of bytes of application data that have been queued using
 * |sendData:| but that have not yet been transmitted to the network.
 */
@property(nonatomic, readonly) uint64_t bufferedAmount;

/** The delegate for this data channel. */
@property(nonatomic, weak) id<SLRRTCDataChannelDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

/** Closes the data channel. */
- (void)close;

/** Attempt to send |data| on this data channel's underlying data transport. */
- (BOOL)sendData:(SLRRTCDataBuffer *)data;

@end

NS_ASSUME_NONNULL_END
