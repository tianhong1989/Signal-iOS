//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "OWSReadTracking.h"
#import "TSMessage.h"

NS_ASSUME_NONNULL_BEGIN

@class TSContactThread;
@class TSGroupThread;

@interface TSIncomingMessage : TSMessage <OWSReadTracking>

@property (nonatomic, readonly, nullable) NSNumber *serverTimestamp;

@property (nonatomic, readonly) BOOL wasReceivedByUD;

- (instancetype)initMessageWithTimestamp:(uint64_t)timestamp
                                inThread:(nullable TSThread *)thread
                             messageBody:(nullable NSString *)body
                           attachmentIds:(NSArray<NSString *> *)attachmentIds
                        expiresInSeconds:(uint32_t)expiresInSeconds
                         expireStartedAt:(uint64_t)expireStartedAt
                           quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                            contactShare:(nullable OWSContact *)contactShare
                             linkPreview:(nullable OWSLinkPreview *)linkPreview NS_UNAVAILABLE;

/**
 *  Inits an incoming group message that expires.
 *
 *  @param timestamp
 *    When the message was created in milliseconds since epoch
 *  @param thread
 *    Thread to which the message belongs
 *  @param authorId
 *    Signal ID (i.e. e164) of the user who sent the message
 *  @param sourceDeviceId
 *    Numeric ID of the device used to send the message. Used to detect duplicate messages.
 *  @param body
 *    Body of the message
 *  @param attachmentIds
 *    The uniqueIds for the message's attachments, possibly an empty list.
 *  @param expiresInSeconds
 *    Seconds from when the message is read until it is deleted.
 *  @param quotedMessage
 *    If this message is a quoted reply to another message, contains data about that message.
 *
 *  @return initiated incoming group message
 */
- (instancetype)initIncomingMessageWithTimestamp:(uint64_t)timestamp
                                        inThread:(TSThread *)thread
                                        authorId:(NSString *)authorId
                                  sourceDeviceId:(uint32_t)sourceDeviceId
                                     messageBody:(nullable NSString *)body
                                   attachmentIds:(NSArray<NSString *> *)attachmentIds
                                expiresInSeconds:(uint32_t)expiresInSeconds
                                   quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                                    contactShare:(nullable OWSContact *)contactShare
                                     linkPreview:(nullable OWSLinkPreview *)linkPreview
                                 serverTimestamp:(nullable NSNumber *)serverTimestamp
                                 wasReceivedByUD:(BOOL)wasReceivedByUD NS_DESIGNATED_INITIALIZER;

// --- CODE GENERATION MARKER

// clang-format off

- (instancetype)initWithUniqueId:(NSString *)uniqueId
             receivedAtTimestamp:(unsigned long long)receivedAtTimestamp
                          sortId:(unsigned long long)sortId
                       timestamp:(unsigned long long)timestamp
                  uniqueThreadId:(NSString *)uniqueThreadId
                   attachmentIds:(NSArray<NSString *> *)attachmentIds
                            body:(nullable NSString *)body
                    contactShare:(nullable OWSContact *)contactShare
                 expireStartedAt:(unsigned long long)expireStartedAt
                       expiresAt:(unsigned long long)expiresAt
                expiresInSeconds:(unsigned int)expiresInSeconds
                     linkPreview:(nullable OWSLinkPreview *)linkPreview
                   quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                   schemaVersion:(NSUInteger)schemaVersion
                        authorId:(NSString *)authorId
                            read:(BOOL)read
                 serverTimestamp:(nullable NSNumber *)serverTimestamp
                  sourceDeviceId:(unsigned int)sourceDeviceId
                 wasReceivedByUD:(BOOL)wasReceivedByUD
NS_SWIFT_NAME(init(uniqueId:receivedAtTimestamp:sortId:timestamp:uniqueThreadId:attachmentIds:body:contactShare:expireStartedAt:expiresAt:expiresInSeconds:linkPreview:quotedMessage:schemaVersion:authorId:read:serverTimestamp:sourceDeviceId:wasReceivedByUD:));

// clang-format on

// --- CODE GENERATION MARKER

- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/*
 * Find a message matching the senderId and timestamp, if any.
 *
 * @param authorId
 *   Signal ID (i.e. e164) of the user who sent the message
 * @params timestamp
 *   When the message was created in milliseconds since epoch
 *
 */
+ (nullable instancetype)findMessageWithAuthorId:(NSString *)authorId
                                       timestamp:(uint64_t)timestamp
                                     transaction:(YapDatabaseReadWriteTransaction *)transaction;

// This will be 0 for messages created before we were tracking sourceDeviceId
@property (nonatomic, readonly) UInt32 sourceDeviceId;

@property (nonatomic, readonly) NSString *authorId;

// convenience method for expiring a message which was just read
- (void)markAsReadNowWithSendReadReceipt:(BOOL)sendReadReceipt
                             transaction:(YapDatabaseReadWriteTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END
