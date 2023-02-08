//
//  JCMessageChannelConstants.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 错误码
/// @{

/**
 * 消息错误原因
 */
typedef NS_ENUM(NSInteger, JCMessageChannelReason) {
    /// 正常
    JCMessageChannelReasonNone,
    /// 未登录
    JCMessageChannelReasonNotLogin,
    /// 消息内容太长
    JCMessageChannelReasonNetwork,
    /// 消息内容太长
    JCMessageChannelReasonTooLong = 10,
    /// 其他错误
    JCMessageChannelReasonOther = 100,
};
/// @}

/// @addtogroup 消息通道模块
/// @{

/**
 * 消息归属类型
 */
typedef NS_ENUM(NSInteger, JCMessageChannelType) {
    /// 一对一消息
    JCMessageChannelType1To1,
    /// 群组消息
    JCMessageChannelTypeGroup,
};

/**
 * 消息状态
 */
typedef NS_ENUM(NSInteger, JCMessageChannelItemState) {
    /// 消息初始状态
    JCMessageChannelItemStateInit,
    /// 消息传输中状态
    JCMessageChannelItemStateTransfering,
    /// 消息成功状态
    JCMessageChannelItemStateOK,
    /// 消息失败状态
    JCMessageChannelItemStateFail,
    /// 已送达
    JCMessageChannelItemStateArrived = 5,
    /// 已读
    JCMessageChannelItemStateReaded,
    /// 撤回
    JCMessageChannelItemStateWithdrawal,
};

/**
 * 消息传输方向
 */
typedef NS_ENUM(NSInteger, JCMessageChannelItemDirection) {
    /// 发送
    JCMessageChannelItemDirectionSend,
    /// 接收
    JCMessageChannelItemDirectionReceive,
};

/**
 * 消息关键字
 */
extern NSString* const JCMessageChannelItemMessageId;
extern NSString* const JCMessageChannelItemFileUri;
extern NSString* const JCMessageChannelItemThumbUri;
extern NSString* const JCMessageChannelItemFileSize;
extern NSString* const JCMessageChannelItemDuration;
extern NSString* const JCMessageChannelItemExtraData;
/**
 * 缩略图限制大小，单位字节
 */
extern const int JCMessageChannelItemMaxThumbSize;

/// @}
