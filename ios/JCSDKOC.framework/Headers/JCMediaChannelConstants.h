//
//  JCMediaChannelConstants.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 错误码
/// @{

/**
 *  频道加入失败和离开的原因
 */
typedef NS_ENUM(NSInteger, JCMediaChannelReason) {
    /// 正常
    JCMediaChannelReasonNone = 0,
    /// 未登录
    JCMediaChannelReasonNotLogin,
    /// 超时
    JCMediaChannelReasonTimeOut,
    /// 网络异常
    JCMediaChannelReasonNetWork,
    /// 函数调用失败
    JCMediaChannelReasonCallFunctionError,
    /// 已加入
    JCMediaChannelReasonAlreadyJoined,
    /// 被踢
    JCMediaChannelReasonKicked,
    /// 掉线
    JCMediaChannelReasonOffline,
    /// 主动离开
    JCMediaChannelReasonQuit,
    /// 频道关闭
    JCMediaChannelReasonOver,
    /// 成员满
    JCMediaChannelReasonFull,
    /// 密码无效
    JCMediaChannelReasonInvalidPassword,
    /// 会议异常
    JCMediaChannelReasonInternalError,
    /// 调用服务器接口异常
    JCMediaChannelReasonServerError,
    /// 参数异常
    JCMediaChannelReasonInvalidParam,
    /// 其他错误
    JCMediaChannelReasonOther = 100,
};
/// @}

/// @addtogroup 多方通话模块
/// @{

#define MASK_CUSTOM_ROLE (JCMediaChannelCustomRole0 | JCMediaChannelCustomRole1 | JCMediaChannelCustomRole2 | JCMediaChannelCustomRole3);

#define MASK_CUSTOM_STATE (JCMediaChannelCustomState0 | JCMediaChannelCustomState1 | JCMediaChannelCustomState2 | JCMediaChannelCustomState3);

/**
 *  图像尺寸等级
 */
typedef NS_ENUM(NSInteger, JCMediaChannelPictureSize) {
    /// 不渲染
    JCMediaChannelPictureSizeNone,
    /// 最小尺寸
    JCMediaChannelPictureSizeMin,
    /// 小尺寸
    JCMediaChannelPictureSizeSmall,
    /// 大尺寸
    JCMediaChannelPictureSizeLarge,
    /// 最大尺寸
    JCMediaChannelPictureSizeMax,
};

/**
 *  媒体视频最大分辨率
 */
typedef NS_ENUM(NSInteger, JCMediaChannelMaxResolution) {
    /// 最大分辨率360P
    JCMediaChannelMaxResolution360,
    /// 最大分辨率720P
    JCMediaChannelMaxResolution720,
    /// 最大分辨率1080P
    JCMediaChannelMaxResolution1080,
};

/**
 *  自身在频道中状态
 */
typedef NS_ENUM(NSInteger, JCMediaChannelState) {
    /// 空闲状态
    JCMediaChannelStateIdle,
    /// 加入中
    JCMediaChannelStateJoining,
    /// 已加入
    JCMediaChannelStateJoined,
    /// 离开中
    JCMediaChannelStateLeaving,
};

/**
 *  成员类型
 */
typedef NS_ENUM(NSInteger, JCMediaChannelParticipantType) {
    /// 普通成员
    JCMediaChannelParticipantTypeNormal,
    /// Pstn成员
    JCMediaChannelParticipantTypePstn,
    /// Webrtc成员
    JCMediaChannelParticipantTypeWebrtc,
    /// IRC 成员
    JCMediaChannelParticipantTypeIrc,
};

/**
 *  音量状态
 */
typedef NS_ENUM(NSInteger, JCMediaChannelVolumeStatus) {
    /// 静音
    JCMediaChannelVolumeStatusNone,
    /// 无声音  1
    JCMediaChannelVolumeStatusZero,
    /// 低  1 - 30
    JCMediaChannelVolumeStatusLow,
    /// 中  31 - 60
    JCMediaChannelVolumeStatusMid,
    /// 高  61 -100
    JCMediaChannelVolumeStatusHigh,
};

/**
 *  网络状态
 */
typedef NS_ENUM(NSInteger, JCMediaChannelNetStatus) {
    /// 未连接
    JCMediaChannelNetStatusDisconnected,
    /// 非常差
    JCMediaChannelNetStatusVeryBad,
    /// 差
    JCMediaChannelNetStatusBad,
    /// 一般
    JCMediaChannelNetStatusNormal,
    /// 好
    JCMediaChannelNetStatusGood,
    /// 非常好
    JCMediaChannelNetStatusVeryGood,
};

/**
 *  视频录制状态
 */
typedef NS_ENUM(NSInteger, JCMediaChannelRecordState) {
    /// 无法进行视频录制
    JCMediaChannelRecordStateNone,
    /// 可以开启视频录制
    JCMediaChannelRecordStateReady,
    /// 视频录制中
    JCMediaChannelRecordStateRunning,
};

/**
 *  CDN状态
 */
typedef NS_ENUM(NSInteger, JCMediaChannelCdnState) {
    /// 无法进行Cdn推流
    JCMediaChannelCdnStateNone,
    /// 可以开启Cdn推流
    JCMediaChannelCdnStateReady,
    /// Cdn推流中
    JCMediaChannelCdnStateRunning,
};

/**
 *  自定义角色
 */
typedef NS_ENUM(NSInteger, JCMediaChannelCustomRole) {
    /// 无自定义状态
    JCMediaChannelCustomRoleNone = 0,
    /// 自定义角色0
    JCMediaChannelCustomRole0 = 1<<12,
    /// 自定义角色1
    JCMediaChannelCustomRole1 = 1<<13,
    /// 自定义角色2
    JCMediaChannelCustomRole2 = 1<<14,
    /// 自定义角色3
    JCMediaChannelCustomRole3 = 1<<15,
};

/**
 *  自定义状态
 */
typedef NS_ENUM(NSInteger, JCMediaChannelCustomState) {
    /// 无自定义状态
    JCMediaChannelCustomStateNone = 0,
    /// 自定义状态0
    JCMediaChannelCustomState0 = 1<<12,
    /// 自定义状态1
    JCMediaChannelCustomState1 = 1<<13,
    /// 自定义状态2
    JCMediaChannelCustomState2 = 1<<14,
    /// 自定义状态3
    JCMediaChannelCustomState3 = 1<<15,
};

/**
 * 视频等级
 */
typedef NS_ENUM(NSInteger, JCMediaChannelVideoLevel) {
    /// 最小尺寸
    JCMediaChannelVideoLevelMin = 256,
    /// 小尺寸
    JCMediaChannelVideoLevelSmall = 512,
    /// 大尺寸
    JCMediaChannelVideoLevelLarge = 768,
    /// 最大尺寸
    JCMediaChannelVideoLevelMax = 1024
};

/**
 * 录制混屏模式
 */
typedef NS_ENUM(NSInteger, JCMediaChannelMergeMode) {
    /// 平铺模式
    JCMediaChannelMergeModeScreen = 1,
    /// 讲台模式
    JCMediaChannelMergeModePlatform = 2,
    /// 演讲者模式
    JCMediaChannelMergeModeSpeaker = 3,
    /// 自定义布局模式
    JCMediaChannelMergeModeLayout = 4,
    /// 智能模式
    JCMediaChannelMergeModeIntellegence = 5,
    /// 屏幕分享模式
    JCMediaChannelMergeModeScreenSharing = 6
};

/**
 * 混屏的详细模式
 */
typedef NS_ENUM(NSInteger, JCMediaChannelMergeModeEx) {
    /// 自由布局
    JCMediaChannelMergeModeExFreelayoutI = 1,
    /// 矩形布局
    JCMediaChannelMergeModeExRectLayoutI = 2,
    /// 大小屏放大2倍
    JCMediaChannelMergeModeExBigSmallX2I = 3,
    /// 大小屏放大3倍
    JCMediaChannelMergeModeExBigSmallX3I = 4,
    /// 大小屏放大4倍
    JCMediaChannelMergeModeExBigSmallX4I = 5,
    /// 大小屏放大5倍
    JCMediaChannelMergeModeExBigSmallX5I = 6,
    /// 大小屏放大6倍
    JCMediaChannelMergeModeExBigSmallX6I = 7,
    /// 大小屏放大7倍
    JCMediaChannelMergeModeExBigSmallX7I = 8,
    /// 大小屏放大8倍
    JCMediaChannelMergeModeExBigSmallX8I = 9,
    /// 大小屏放大9倍
    JCMediaChannelMergeModeExBigSmallX9I = 10,
    /// 大小屏放大10倍
    JCMediaChannelMergeModeExBigSmallX10I = 11,
    /// 大小屏放大到顶部
    JCMediaChannelMergeModeExBigSmallTopI = 12,
    /// 大小屏放大到底部
    JCMediaChannelMergeModeExBigSmallBottomI = 13,
    /// 等分模式
    JCMediaChannelMergeModeExDivideLayoutI = 14,
    /// 等分模式忽略图像角度
    JCMediaChannelMergeModeExDivideLayoutNoangleI = 15
};
/// @}
