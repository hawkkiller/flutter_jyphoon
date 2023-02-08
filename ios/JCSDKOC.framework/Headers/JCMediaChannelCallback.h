//
//  JCMediaChannelCallback.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMediaChannelParticipant.h"
#import "JCMediaChannelConstants.h"
#import "JCMediaChannelQueryInfo.h"
#import "JCMediaChannelParticipant.h"

/**
 * @addtogroup 多方通话模块
 * @{
 */

@class JCMediaChannelPropChangeParam;

/**
 * JCMediaChannel 回调
 */
@protocol JCMediaChannelCallback <NSObject>

/**
 * 自身在频道中的状态变化回调
 *
 * 状态：
 * - @ref JCMediaChannelStateIdle : 空闲状态
 * - @ref JCMediaChannelStateJoining : 加入中
 * - @ref JCMediaChannelStateJoined : 已加入
 * - @ref JCMediaChannelStateLeaving : 离开中
 *
 * @param state    当前状态
 * @param oldState 变化前状态
 */
-(void)onMediaChannelStateChange:(JCMediaChannelState)state oldState:(JCMediaChannelState)oldState;

/**
 * 属性变化回调
 *
 * @param changeParam JCMediaChannelPropChangeParam 变化标识集合
 */
-(void)onMediaChannelPropertyChange:(JCMediaChannelPropChangeParam *)changeParam;

/**
 * 加入频道结果回调
 *
 * @param result 加入频道是否成功
 * - true：成功
 * - false：失败
 * @param reason    加入失败原因，当 result 为 false 时该值有效。失败原因参见：@ref JCMediaChannelReason "错误码"
 * @param channelId 频道标识符
 */
-(void)onJoin:(bool)result reason:(JCMediaChannelReason)reason channelId:(NSString*)channelId;

/**
 * 离开频道结果回调
 *
 * @param reason    离开原因，参见：@ref JCMediaChannelReason "离开原因"
 * @param channelId 频道标识符
 */
-(void)onLeave:(JCMediaChannelReason)reason channelId:(NSString*)channelId;

/**
 * 解散频道结果回调
 *
 * @param result 解散频道是否成功
 * - true：成功
 * - false：失败
 * @param reason 解散失败原因，当 result 为 false 时该值有效。失败原因参见：@ref JCMediaChannelReason "JCMediaChannel 失败原因"
 */
-(void)onStop:(bool)result reason:(JCMediaChannelReason)reason;

/**
 * 查询频道信息结果回调
 *
 * @param operationId 操作id，由 {@link JCMediaChannel#query: query} 接口返回
 * @param result 查询频道信息是否成功
 * - true：查询成功
 * - false：查询失败
 * @param reason      查询失败原因，当 result 为 false 时该值有效。失败原因参见：@ref JCMediaChannelReason "JCMediaChannel 错误码"
 * @param queryInfo   JCMediaChannelQueryInfo 对象，查询到的频道信息，当失败时只需关注 @ref JCMediaChannelQueryInfo.channelId "channelId"
 */
-(void)onQuery:(int)operationId result:(bool)result reason:(JCMediaChannelReason)reason queryInfo:(JCMediaChannelQueryInfo*)queryInfo;

/**
 * 新成员加入回调
 *
 * @param participant JCMediaChannelParticipant 成员对象
 */
-(void)onParticipantJoin:(JCMediaChannelParticipant*)participant;

/**
 * 成员离开回调
 *
 * @param participant JCMediaChannelParticipant 成员对象
 */
-(void)onParticipantLeft:(JCMediaChannelParticipant*)participant;

/**
 * 成员更新回调
 *
 * @param participant JCMediaChannelParticipant 成员对象
 * @param changeParam JCMediaChannelParticipantChangeParam 更新标识类
 */
-(void)onParticipantUpdate:(JCMediaChannelParticipant*)participant participantChangeParam:(JCMediaChannelParticipantChangeParam *)participantChangeParam;

/**
 * 接收频道消息的回调
 *
 * @param type           消息类型   对应 {@link JCMediaChannel#sendMessage:content:toUserId: sendMessage} 方法中的 type 参数
 * @param content    消息内容   对应 {@link JCMediaChannel#sendMessage:content:toUserId: sendMessage} 方法中的 content 参数
 * @param fromUserId 消息发送成员的 userId
 */
-(void)onMessageReceive:(NSString *)type content:(NSString *)content fromUserId:(NSString *)fromUserId;

/**
 * 邀请Sip用户操作结果回调
 *
 * @param operationId 操作id
 * @param result 邀请用户是否成功
 * - true：成功，此时会触发 {@link JCMediaChannelCallback#onParticipantJoin: onParticipantJoin}  回调
 * - false：失败
 * @param reason  失败原因，当 result 为 false 时该值有效。参见：@ref JCMediaChannelReason "失败原因"
 */
-(void)onInviteSipUserResult:(int)operationId result:(bool)result reason:(int)reason;

/**
 * 成员声音变化
 *
 * @param participant JCMediaChannelParticipant 变化成员
 */
-(void)onParticipantVolumeChange:(JCMediaChannelParticipant*)participant;

@end

/**
 * @}
 */
