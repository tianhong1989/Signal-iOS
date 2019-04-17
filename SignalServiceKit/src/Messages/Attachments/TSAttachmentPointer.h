//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "TSAttachment.h"

NS_ASSUME_NONNULL_BEGIN

@class OWSBackupFragment;
@class SSKProtoAttachmentPointer;
@class TSAttachmentStream;
@class TSMessage;

typedef NS_ENUM(NSUInteger, TSAttachmentPointerType) {
    TSAttachmentPointerTypeUnknown = 0,
    TSAttachmentPointerTypeIncoming = 1,
    TSAttachmentPointerTypeRestoring = 2,
};

typedef NS_ENUM(NSUInteger, TSAttachmentPointerState) {
    TSAttachmentPointerStateEnqueued = 0,
    TSAttachmentPointerStateDownloading = 1,
    TSAttachmentPointerStateFailed = 2,
};

/**
 * A TSAttachmentPointer is a yet-to-be-downloaded attachment.
 */
@interface TSAttachmentPointer : TSAttachment

@property (nonatomic) TSAttachmentPointerType pointerType;
@property (atomic) TSAttachmentPointerState state;
@property (nullable, atomic) NSString *mostRecentFailureLocalizedText;

// Though now required, `digest` may be null for pre-existing records or from
// messages received from other clients
@property (nullable, nonatomic, readonly) NSData *digest;

@property (nonatomic, readonly) CGSize mediaSize;

// Non-nil for attachments which need "lazy backup restore."
- (nullable OWSBackupFragment *)lazyRestoreFragment;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithServerId:(UInt64)serverId
                             key:(NSData *)key
                          digest:(nullable NSData *)digest
                       byteCount:(UInt32)byteCount
                     contentType:(NSString *)contentType
                  sourceFilename:(nullable NSString *)sourceFilename
                         caption:(nullable NSString *)caption
                  albumMessageId:(nullable NSString *)albumMessageId
                  attachmentType:(TSAttachmentType)attachmentType
                       mediaSize:(CGSize)mediaSize NS_DESIGNATED_INITIALIZER;

- (instancetype)initForRestoreWithAttachmentStream:(TSAttachmentStream *)attachmentStream NS_DESIGNATED_INITIALIZER;

// --- CODE GENERATION MARKER

// clang-format off

- (instancetype)initWithUniqueId:(NSString *)uniqueId
                  albumMessageId:(nullable NSString *)albumMessageId
         attachmentSchemaVersion:(NSUInteger)attachmentSchemaVersion
                  attachmentType:(TSAttachmentType)attachmentType
                       byteCount:(unsigned int)byteCount
                         caption:(nullable NSString *)caption
                     contentType:(NSString *)contentType
                   encryptionKey:(nullable NSData *)encryptionKey
                    isDownloaded:(BOOL)isDownloaded
                        serverId:(unsigned long long)serverId
                  sourceFilename:(nullable NSString *)sourceFilename
                          digest:(nullable NSData *)digest
           lazyRestoreFragmentId:(nullable NSString *)lazyRestoreFragmentId
                       mediaSize:(CGSize)mediaSize
  mostRecentFailureLocalizedText:(nullable NSString *)mostRecentFailureLocalizedText
                     pointerType:(TSAttachmentPointerType)pointerType
                           state:(TSAttachmentPointerState)state
NS_SWIFT_NAME(init(uniqueId:albumMessageId:attachmentSchemaVersion:attachmentType:byteCount:caption:contentType:encryptionKey:isDownloaded:serverId:sourceFilename:digest:lazyRestoreFragmentId:mediaSize:mostRecentFailureLocalizedText:pointerType:state:));

// clang-format on

// --- CODE GENERATION MARKER

+ (nullable TSAttachmentPointer *)attachmentPointerFromProto:(SSKProtoAttachmentPointer *)attachmentProto
                                                albumMessage:(nullable TSMessage *)message;

+ (NSArray<TSAttachmentPointer *> *)attachmentPointersFromProtos:
                                        (NSArray<SSKProtoAttachmentPointer *> *)attachmentProtos
                                                    albumMessage:(TSMessage *)message;

#pragma mark - Update With... Methods

// Marks attachment as needing "lazy backup restore."
- (void)markForLazyRestoreWithFragment:(OWSBackupFragment *)lazyRestoreFragment
                           transaction:(YapDatabaseReadWriteTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END
