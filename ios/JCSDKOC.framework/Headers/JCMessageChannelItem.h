//
//  JCMessageChannelItem.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMessageChannelConstants.h"

/**
 * @addtogroup 消息通道模块
 * @{
 */

/**
 *  IM消息对象类
 */
@interface JCMessageChannelItem : NSObject

/**
 * 消息唯一标识
 */
@property (nonatomic, readonly, copy) NSString* messageId;

/**
 * 消息内容类型
 */
@property (nonatomic, readonly, copy) NSString* messageType;

/**
 * 消息内容
 *
 * 包括文本和自定义消息体内容
 */
@property (nonatomic, readonly, copy) NSString* text;

/**
 * 文件链接
 *
 * 可以通过 JCStorage 将文件上传至 Juphoon Cloud 平台来获取该地址，也可以从其他文件消息获取改地址
 */
@property (nonatomic, readonly, copy) NSString* fileUri;

/**
 * 缩略图链接
 *
 * 可以通过 JCStorage 将文件上传至 Juphoon Cloud 平台来获取该地址，也可以从其他文件消息获取改地址
 */
@property (nonatomic, readonly, copy) NSString* thumbUri;

/**
 * 文件大小
 */
@property (nonatomic, readonly) int fileSize;

/**
 * 文件时长
 * @note 语音，视频消息有效
 */
@property (nonatomic, readonly) int duration;

/**
 * 自定义参数集
 */
@property (nonatomic, readonly, strong) NSDictionary* extraParams;

/**
 * 消息对端用户标识
 */
@property (nonatomic, readonly, copy) NSString* userId;

/**
 * 消息对端昵称
 */
@property (nonatomic, readonly, copy) NSString* displayName;

/**
 * 群组标识，type 为 @ref JCMessageChannelTypeGroup 时有效
 */
@property (nonatomic, readonly, copy) NSString* groupId;

/**
 * 发送或者接收时间，单位毫秒
 */
@property (nonatomic, readonly) long time;

/**
 * 发送成功时间，单位毫秒，如果是收到消息则是服务器记录的该消息发送时间
 */
@property (nonatomic, readonly) long sentTime;

/**
 * 消息传输方向，参见：
 * - @ref JCMessageChannelItemDirectionSend : 发送
 * - @ref JCMessageChannelItemDirectionReceive : 接收
 */
@property (nonatomic, readonly) JCMessageChannelItemDirection direction;

/**
 * 返回是一对一消息还是群组消息
 *
 * - @ref JCMessageChannelType1To1 : 一对一消息
 * - @ref JCMessageChannelTypeGroup : 群组消息
 */
@property (nonatomic, readonly) JCMessageChannelType type;

/**
 * 消息状态：
 * - @ref JCMessageChannelItemStateInit : 消息初始状态
 * - @ref JCMessageChannelItemStateTransfering : 消息传输中状态
 * - @ref JCMessageChannelItemStateOK : 消息成功状态
 * - @ref JCMessageChannelItemStateFail : 消息失败状态
 * - @ref JCMessageChannelItemStateArrived : 已送达
 * - @ref JCMessageChannelItemStateReaded : 已读
 * - @ref JCMessageChannelItemStateWithdrawal : 撤回
 */
@property (nonatomic, readonly) JCMessageChannelItemState state;

/**
 * @ref JCMessageChannelReason "消息错误码"
 *
 * 当消息状态为 @ref JCMessageChannelItemStateFail 时有效
 */
@property (nonatomic, readonly) JCMessageChannelReason error;

/**
 * 消息的服务器id
 */
@property (nonatomic, readonly) long serverMessageId;

/**
 * cookie
 */
@property (nonatomic, strong) id cookie;

/**
 * 会话 serverUid
 */
@property (nonatomic, strong) NSString* serverUid;

/**
 * 消息发送者 uid
 */
@property (nonatomic, strong) NSString* senderUid;

/**
 * 是否@我的，针对群聊
 * - true: @我
 * - false: 未@我
 */
@property (nonatomic) bool atMe;
/**
 * 是否@所有人，针对群聊
 * - true: @所有人
 * - false: 未@所有人
 */
@property (nonatomic) bool atAll;
/**
 * @的uid列表
 */
@property (nonatomic, strong) NSArray<NSString*>* atServerUidList;
/**
 * 是否是撤回消息
 * - true: 是撤回消息
 * - false: 不是撤回消息
 */
@property (nonatomic) bool isWithdrawal;
/**
 * 撤回的消息id
 */
@property (nonatomic) long withdrawalMessageId;;

@end

/**
 * @}
 */
