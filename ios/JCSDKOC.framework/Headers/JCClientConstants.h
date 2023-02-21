//
//  JCClientConstants.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 错误码
/// @{
/// 错误代码

/**
 *  登录错误原因枚举
 */
typedef NS_ENUM(NSInteger, JCClientReason) {
    /// 正常
    JCClientReasonNone,
    /// sdk 未初始化
    JCClientReasonSDKNotInit,
    /// 无效的参数
    JCClientReasonInvalidParam,
    /// 函数调用失败
    JCClientReasonCallFunctionError,
    /// 当前状态无法再次登录
    JCClientReasonStateCannotLogin,
    /// 登录超时
    JCClientReasonTimeOut,
    /// 网络异常
    JCClientReasonNetWork,
    /// appkey 错误
    JCClientReasonAppKey,
    /// 账号密码错误
    JCClientReasonAuth,
    /// 无该用户
    JCClientReasonNoUser,
    /// 被强制登出
    JCClientReasonServerLogout,
    /// 登录其他设备
    JCClientReasonAnotherDeviceLogined,
    /// 本地请求失败
    JCClientReasonLocalRequest,
    /// 发消息失败
    JCClientReasonSendMessage,
    /// 服务器忙
    JCClientReasonServerBusy,
    /// 服务器不可达
    JCClientReasonServerNotReach,
    /// 服务器拒绝(无权限访问)
    JCClientReasonServerForbidden,
    /// 服务器不可用
    JCClientReasonServerUnavaliable,
    /// DNS 查询错误
    JCClientReasonDnsQuery,
    /// 服务器内部错误
    JCClientReasonInternal,
    /// 无资源
    JCClientReasonNoResource,
    /// 没有回应验证码
    JCClientReasonNoNonce,
    /// 无效验证码
    JCClientReasonInvalidAuthCode,
    /// Token不匹配
    JCClientReasonTokenMismatch,
    /// Token 长度无效
    JCClientReasonTokenSizeInvalid,
    /// Token 未携带 AppSecret
    JCClientReasonTokenSecretNotFound,
    /// Token 解析错误
    JCClientReasonTokenAnalysisError,
    /// Token 携带的 Appkey 校验错误
    JCClientReasonTokenVersignAppkeyError,
    /// Token 与账号不匹配
    JCClientReasonTokenAccountIdMismatch,
    /// Token 已过期
    JCClientReasonTokenExpired,
    /// 其他错误
    JCClientReasonOther = 100,
};
/// @}

/// @addtogroup 登录模块
/// @{

/**
 * 登录状态
 */
typedef NS_ENUM(NSInteger, JCClientState) {
    /// 未初始化
    JCClientStateNotInit,
    /// 未登录
    JCClientStateIdle,
    /// 登录中
    JCClientStateLogining,
    /// 登录成功
    JCClientStateLogined,
    /// 登出中
    JCClientStateLogouting,
};

/**
 * 日志等级
 */
typedef NS_ENUM(NSInteger, JCLogLevel) {
    /// 不打印日志
    JCLogLevelDisable,
    /// 只打印 error 等级的日志
    JCLogLevelError,
    /// 只打印 info 和 error 等级的日志
    JCLogLevelInfo,
    /// 打印所有等级的日志
    JCLogLevelDebug
};
/// @}
