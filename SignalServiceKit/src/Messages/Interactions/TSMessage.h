//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "TSInteraction.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Abstract message class.
 */

@class MessageSticker;
@class OWSContact;
@class OWSLinkPreview;
@class SDSAnyReadTransaction;
@class SDSAnyWriteTransaction;
@class TSAttachment;
@class TSAttachmentStream;
@class TSQuotedMessage;

@interface TSMessage : TSInteraction <OWSPreviewText>

// NOTE: These correspond to just the "body" attachments.
@property (nonatomic, readonly) NSMutableArray<NSString *> *attachmentIds;
@property (nonatomic, readonly, nullable) NSString *body;

// Per-conversation expiration.
@property (nonatomic, readonly) uint32_t expiresInSeconds;
@property (nonatomic, readonly) uint64_t expireStartedAt;
@property (nonatomic, readonly) uint64_t expiresAt;
// See: hasPerMessageExpiration.
@property (nonatomic, readonly) BOOL hasPerConversationExpiration;

@property (nonatomic, readonly, nullable) TSQuotedMessage *quotedMessage;
@property (nonatomic, readonly, nullable) OWSContact *contactShare;
@property (nonatomic, readonly, nullable) OWSLinkPreview *linkPreview;
@property (nonatomic, readonly, nullable) MessageSticker *messageSticker;

// Per-message expiration.
@property (nonatomic, readonly) uint32_t perMessageExpirationDurationSeconds;
@property (nonatomic, readonly) uint64_t perMessageExpireStartedAt;
@property (nonatomic, readonly) uint64_t perMessageExpiresAt;
@property (nonatomic, readonly) BOOL perMessageExpirationHasExpired;
// See: hasPerConversationExpiration.
@property (nonatomic, readonly) BOOL hasPerMessageExpiration;
@property (nonatomic, readonly) BOOL hasPerMessageExpirationStarted;

- (instancetype)initInteractionWithTimestamp:(uint64_t)timestamp inThread:(TSThread *)thread NS_UNAVAILABLE;

- (instancetype)initMessageWithTimestamp:(uint64_t)timestamp
                                inThread:(TSThread *)thread
                             messageBody:(nullable NSString *)body
                           attachmentIds:(NSArray<NSString *> *)attachmentIds
                        expiresInSeconds:(uint32_t)expiresInSeconds
                         expireStartedAt:(uint64_t)expireStartedAt
                           quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                            contactShare:(nullable OWSContact *)contactShare
                             linkPreview:(nullable OWSLinkPreview *)linkPreview
                          messageSticker:(nullable MessageSticker *)messageSticker
     perMessageExpirationDurationSeconds:(uint32_t)perMessageExpirationDurationSeconds NS_DESIGNATED_INITIALIZER;

// --- CODE GENERATION MARKER

// This snippet is generated by /Scripts/sds_codegen/sds_generate.py. Do not manually edit it, instead run `sds_codegen.sh`.

// clang-format off

- (instancetype)initWithUniqueId:(NSString *)uniqueId
             receivedAtTimestamp:(uint64_t)receivedAtTimestamp
                          sortId:(uint64_t)sortId
                       timestamp:(uint64_t)timestamp
                  uniqueThreadId:(NSString *)uniqueThreadId
                   attachmentIds:(NSArray<NSString *> *)attachmentIds
                            body:(nullable NSString *)body
                    contactShare:(nullable OWSContact *)contactShare
                 expireStartedAt:(uint64_t)expireStartedAt
                       expiresAt:(uint64_t)expiresAt
                expiresInSeconds:(unsigned int)expiresInSeconds
                     linkPreview:(nullable OWSLinkPreview *)linkPreview
                  messageSticker:(nullable MessageSticker *)messageSticker
perMessageExpirationDurationSeconds:(unsigned int)perMessageExpirationDurationSeconds
  perMessageExpirationHasExpired:(BOOL)perMessageExpirationHasExpired
       perMessageExpireStartedAt:(uint64_t)perMessageExpireStartedAt
                   quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                   schemaVersion:(NSUInteger)schemaVersion
NS_SWIFT_NAME(init(uniqueId:receivedAtTimestamp:sortId:timestamp:uniqueThreadId:attachmentIds:body:contactShare:expireStartedAt:expiresAt:expiresInSeconds:linkPreview:messageSticker:perMessageExpirationDurationSeconds:perMessageExpirationHasExpired:perMessageExpireStartedAt:quotedMessage:schemaVersion:));

// clang-format on

// --- CODE GENERATION MARKER

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (BOOL)hasAttachments;
- (NSArray<TSAttachment *> *)bodyAttachmentsWithTransaction:(SDSAnyReadTransaction *)transaction;
- (NSArray<TSAttachment *> *)mediaAttachmentsWithTransaction:(SDSAnyReadTransaction *)transaction;
- (nullable TSAttachment *)oversizeTextAttachmentWithTransaction:(SDSAnyReadTransaction *)transaction;
- (NSArray<TSAttachment *> *)allAttachmentsWithTransaction:(SDSAnyReadTransaction *)transaction;

- (void)removeAttachment:(TSAttachment *)attachment
             transaction:(SDSAnyWriteTransaction *)transaction NS_SWIFT_NAME(removeAttachment(_:transaction:));

// Returns ids for all attachments, including message ("body") attachments,
// quoted reply thumbnails, contact share avatars, link preview images, etc.
- (NSArray<NSString *> *)allAttachmentIds;

- (void)setQuotedMessageThumbnailAttachmentStream:(TSAttachmentStream *)attachmentStream;

- (nullable NSString *)oversizeTextWithTransaction:(SDSAnyReadTransaction *)transaction;
- (nullable NSString *)bodyTextWithTransaction:(SDSAnyReadTransaction *)transaction;

- (BOOL)shouldStartExpireTimerWithTransaction:(SDSAnyReadTransaction *)transaction;

- (BOOL)hasRenderableContent;

#pragma mark - Update With... Methods

- (void)updateWithExpireStartedAt:(uint64_t)expireStartedAt transaction:(SDSAnyWriteTransaction *)transaction;

- (void)updateWithLinkPreview:(OWSLinkPreview *)linkPreview transaction:(SDSAnyWriteTransaction *)transaction;

- (void)updateWithMessageSticker:(MessageSticker *)messageSticker transaction:(SDSAnyWriteTransaction *)transaction;

#pragma mark - Per-message expiration

// This method is used when we start expiration of per-message expiration.
//
// NOTE: To start "count down", use PerMessageExpiration.  Don't call this method directly.
- (void)updateWithPerMessageExpireStartedAt:(uint64_t)perMessageExpireStartedAt
                                transaction:(SDSAnyWriteTransaction *)transaction;

- (void)updateWithHasPerMessageExpiredAndRemoveRenderableContentWithTransaction:(SDSAnyWriteTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END
