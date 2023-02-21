//
//  JCMessageChannelConversation.h
//  JCSDKOCShare
//
//  Created by maikireton on 2019/11/19.
//  Copyright © 2019 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @addtogroup 消息通道模块
 * @{
 */

NS_ASSUME_NONNULL_BEGIN

/**
 * 消息概况实体类
 */
@interface JCMessageChannelConversation : NSObject
/**
 * 服务器会话id
 */
@property (nonatomic, copy) NSString* serverUid;
/**
 * 最新一条消息id
 */
@property (nonatomic) long lastMessageId;
/**
 * 对端已读的消息id(一对一)
 */
@property (nonatomic) long lastOtherReadMessageId;
/**
 * 对端已收的消息id(一对一)
 */
@property (nonatomic) long lastOtherRecvMessageId;
/**
 * 自己读到的消息id
 */
@property (nonatomic) long lastSelfReadMessageId;
/**
 * 最后一次会话更新时间
 */
@property (nonatomic) long updateTime;
/**
 * 最后一条消息时间
 */
@property (nonatomic) long lastMessageTime;
/**
 * 最后一套消息内容
 */
@property (nonatomic) NSString* lastMessageBrief;

@end

NS_ASSUME_NONNULL_END

/**
 * @}
 */
