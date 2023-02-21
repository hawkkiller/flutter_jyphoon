//
//  JCMessageChannelCallback.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMessageChannelItem.h"
#import "JCMessageChannelConversation.h"

/**
 * @addtogroup 消息通道模块
 * @{
 */

/**
 * JCMessageChannel 回调
 */
@protocol JCMessageChannelCallback <NSObject>

/**
 * 消息发送状态更新回调
 *
 * @param message IM消息对象，通过该对象可以获得消息的属性及状态
 */
-(void)onMessageSendUpdate:(JCMessageChannelItem*)message;

/**
 * 收到消息回调
 *
 * 非自动接收模式下会上报自己的消息，上层需要自己处理
 *
 * @param message IM消息对象，通过该对象可以获得消息的属性及状态
 */
-(void)onMessageRecv:(JCMessageChannelItem*)message;

/**
 * 刷新消息结果回调
 *
 * @param result                           刷新消息是否成功
 * @param operationId                      操作ID, 由revMessage返回
 * @param jcMessageChannelConversationList 刷新消息结果返回, 会话列表
 * @param reason                           @ref JCMessageChannelReason "失败原因描述"
 * @param updateTime                       服务器最后更新时间，当 result 为 false 时该值有效
 * @param refreshServerUid                 调用 refreshConversation 传入的 serverUid
 */
-(void)onRefreshConversation:(int)operationId result:(bool)result conversations:(NSArray<JCMessageChannelConversation*>*)conversations reason:(JCMessageChannelReason)reason updateTime:(long)updateTime refreshServerUid:(NSString*)refreshServerUid;

/**
 * 拉取消息结果回调
 *
 * @param result      收取消息是否成功
 * @param operationId 操作ID, 由revMessage返回
 * @param reason      @ref JCMessageChannelReason "失败原因描述"
 */
-(void)onFetchMessageResult:(int)operationId result:(bool)result reason:(JCMessageChannelReason)reason;

/**
 * 标志消息已读结果回调
 *
 * @param result      标志消息已读是否成功
 * @param operationId 操作ID, 由setMessageRead返回
 * @param reason      @ref JCMessageChannelReason "失败原因描述"
 */
-(void)onMarkReadResult:(int)operationId result:(bool)result reason:(JCMessageChannelReason)reason;

/**
 * 标志消息已收结果回调
 *
 * @param result      标志消息已收是否成功
 * @param operationId 操作ID, 由setMessageRead返回
 * @param reason      @ref JCMessageChannelReason "失败原因描述"
 */
-(void)onMarkRecvResult:(int)operationId result:(bool)result reason:(JCMessageChannelReason)reason;

/**
 * 对方已收消息回执回调
 *
 * @param serverUid         用户ID
 * @param serverMessageId       服务器消息 id
 */
-(void)onReceiveMarkRecv:(NSString*)serverUid serverMessageId:(long)serverMessageId;

/**
 * 对方已读消息回执回调
 *
 * @param serverUid             用户ID
 * @param serverMessageId 服务器消息 id
 */
-(void)onReceiveMarkRead:(NSString*)serverUid serverMessageId:(long)serverMessageId;

/**
 * 拉取历史消息回调
 *
 * 主要针对拉取历史消息
 *
 * @param messageList IM消息对象列表，通过该对象可以获得消息的属性及状态
 */
-(void)onMessageListRecv:(NSArray<JCMessageChannelItem*>*)messageList;

/**
 * 撤回消息结果回调
 *
 * @param result      标志消息已收是否成功
 * @param operationId 操作ID, 由setMessageRead返回
 * @param reason      @ref JCMessageChannelReason "失败原因描述"
 */
-(void)onWithdrawalMessageResult:(int)operationId result:(bool)result message:(JCMessageChannelItem*)message reason:(JCMessageChannelReason)reason;

@end

/**
 * @}
 */
