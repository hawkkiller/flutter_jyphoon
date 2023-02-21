//
//  JCCallConstants.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 错误码
/// @{

/**
 *  通话结束错误原因
 */
typedef NS_ENUM(NSInteger, JCCallReason) {
    /// 无异常
    JCCallReasonNone,
    /// 未登录
    JCCallReasonNotLogin,
    /// 函数调用失败
    JCCallReasonCallFunctionError,
    /// 超时
    JCCallReasonTimeOut,
    /// 网络异常
    JCCallReasonNetWork,
    /// 超过通话数限制
    JCCallReasonCallOverLimit,
    /// 自己挂断
    JCCallReasonTermBySelf,
    /// 应答失败
    JCCallReasonAnswerFail,
    /// 忙
    JCCallReasonBusy,
    /// 拒接
    JCCallReasonDecline,
    /// 用户不在线
    JCCallReasonUserOffline,
    /// 无此用户
    JCCallReasonNotFound,
    /// 已有通话拒绝视频来电
    JCCallReasonRejectVideoWhenHasCall,
    /// 已有视频通话拒绝来电
    JCCallReasonRejectCallWhenHasVideoCall,
    /// 通话因某端心跳超时挂断
    JCCallReasonSessionTimeout,
    /// 其他错误
    JCCallReasonOther = 100,
};
/// @}

/// @addtogroup 一对一通话模块
/// @{

/**
 *  通话方向
 */
typedef NS_ENUM(NSInteger, JCCallDirection) {
    /// 呼入
    JCCallDirectionIn,
    /// 呼出
    JCCallDirectionOut,
};

/**
 *  通话状态
 */
typedef NS_ENUM(NSInteger, JCCallState) {
    /// 初始
    JCCallStateInit,
    /// 振铃
    JCCallStatePending,
    /// 连接中
    JCCallStateConnecting,
    /// 通话中
    JCCallStateTalking,
    /// 通话正常结束
    JCCallStateOk,
    /// 未接通挂断
    JCCallStateCancel,
    /// 未接通被挂断
    JCCallStateCanceled,
    /// 未接
    JCCallStateMissed,
    /// 异常
    JCCallStateError,
};

/**
 *  通话网络状态
 */
typedef NS_ENUM(NSInteger, JCCallNetWork) {
    /// 未知状态
    JCCallNetWorkNA = -100,
    /// 无网络
    JCCallNetWorkDisconnected = -3,
    /// 很差
    JCCallNetWorkVeryBad,
    /// 差
    JCCallNetWorkBad,
    /// 一般
    JCCallNetWorkNormal,
    /// 好
    JCCallNetWorkGood,
    /// 很好
    JCCallNetWorkVeryGood,
};

/**
 *  DTMF值
 */
typedef NS_ENUM(NSInteger, JCCallDtmf) {
    /// Dtmf0
    JCCallDtmf0,
    /// Dtmf1
    JCCallDtmf1,
    /// Dtmf2
    JCCallDtmf2,
    /// Dtmf3
    JCCallDtmf3,
    /// Dtmf4
    JCCallDtmf4,
    /// Dtmf5
    JCCallDtmf5,
    /// Dtmf6
    JCCallDtmf6,
    /// Dtmf7
    JCCallDtmf7,
    /// Dtmf8
    JCCallDtmf8,
    /// Dtmf9
    JCCallDtmf9,
    /// DtmfStar
    JCCallDtmfStar,
    /// DtmfPound
    JCCallDtmfPound,
    /// DtmfA
    JCCallDtmfA,
    /// DtmfB
    JCCallDtmfB,
    /// DtmfC
    JCCallDtmfC,
    /// DtmfD
    JCCallDtmfD,
};

/**
 * 回声消除模式
 */
typedef NS_ENUM(NSInteger, JCCallAecMode) {
    /// 声学回声消除。支持在免提状态下的通话，对于iOS和Windows等性能较好的机型有效。
    JCCallAecModeAEC = 0, // MtcCallDb.EN_MTC_EC_AEC;
    /// 使用操作系统提供的声学回声消除功能，支持在免提状态下的通话。对于多数iOS和Android等品牌手机有效，但部分机型可能无效。
    JCCallAecModeOS = 1, // MtcCallDb.EN_MTC_EC_OS;
    /// 声学回声抑制，通过半双工方式实现回声抑制，通常不建议使用。
    JCCallAecModeAES = 2, // MtcCallDb.EN_MTC_EC_AES;
    /// 软件自适应声学回声消除，对于大多数所有机型有效。但计算量比AEC稍大一些。SDE追踪延迟精度高，FDE能适应更大的延迟。
    JCCallAecModeFDE = 3, // MtcCallDb.EN_MTC_EC_AEC_FDE;
    /// 软件自适应声学回声消除，对于大多数所有机型有效。但计算量比AEC稍大一些。SDE追踪延迟精度高，FDE能适应更大的延迟。
    JCCallAecModeSDE = 4, // MtcCallDb.EN_MTC_EC_AEC_SDE;
};

/**
 * 通话媒体配置模式
 */
typedef NS_ENUM(NSInteger, JCCallMediaConfigMode) {
    /// 360P
    JCCallMediaConfigMode360P,
    /// 720P
    JCCallMediaConfigMode720P,
    /// 智能硬件场景，比如会和手表通话等
    JCCallMediaConfigModeIntelligentHardware,
    /// 与asr，展讯等小系统互通
    JCCallMediaConfigModeIOT,
    /// 对接落地业务，此模式会关闭 srtp 加密以及部分落地业务不支持的协商配置
    JCCallMediaConfigModeSip,
};
///@}
