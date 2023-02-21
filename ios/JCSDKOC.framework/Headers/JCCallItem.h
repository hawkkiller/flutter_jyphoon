//
//  JCCallItem.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCCallConstants.h"

/**
 * @addtogroup 一对一通话模块
 * @{
 */

/**
 * 上次更新到这次更新间的状态变化集合
 */
@interface JCCallChangeParam : NSObject

/**
 * 状态是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool state;

/**
 * 挂起是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool hold;

/**
 * 被挂起是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool held;

/**
 * 静音是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool mute;

/**
 * 音频录制是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool audioRecord;

/**
 * 本地视频录制是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool localVideoRecord;

/**
 * 远端视频录制是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool remoteVideoRecord;

/**
 * 音频输出是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool audioOutputType;

/**
 * 活跃是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool active;

/**
 * 本端上传视频是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool uploadVideoStreamSelf;

/**
 * 对端上传视频是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool uploadVideoStreamOther;

/**
 * 网络状态是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool netStatus;

/**
 * 对端声音中断是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool otherAudioInterrupt;

@end


/**
 * 通话对象，此类主要记录通话的一些状态，UI可以根据其中的状态进行更新
 */
@interface JCCallItem : NSObject

/**
 * 用户标识
 */
@property (nonatomic, readonly, copy) NSString* __nonnull userId;

/**
 * 用户昵称
 *
 * @note
 * - 用户昵称为空时返回用户标识
 * - 被叫能够直接获取主叫的昵称，主叫不能直接获取被叫的昵称。被叫可以在收到 {@link JCCallCallback#onCallItemAdd: onCallItemAdd} 回调时可以通过 {@link JCMessageChannel#sendMessage:keyId:messageType:text:extraParams:cookie:atAll:atServerUidList: sendMessage} 方法向主叫发送自己的昵称
 */
@property (nonatomic , copy) NSString* __nullable displayName;

/**
 * 渲染标识
 *
 * 此属性原本用于 {@link JCMediaDevice#startVideo:renderType: startVideo} 渲染其他端视频使用，现在可以直接调用 {@link startOtherVideo: startOtherVideo} 方法来渲染其他端视频
 */
@property (nonatomic, readonly, copy) NSString* __nonnull renderId;

/**
 * 通话方向（呼入或呼出）
 *
 * - @ref JCCallDirectionIn : 呼入
 * - @ref JCCallDirectionOut : 呼出
 */
@property (nonatomic, readonly) JCCallDirection direction;

/**
 * 是否为视频通话
 *
 * - true: 视频通话
 * - false: 音频通话
 */
@property (nonatomic, readonly) bool video;

/**
 * 通话建立时间戳，单位秒
 */
@property (nonatomic, readonly) long beginTime;

/**
 * 通话开始时间戳，单位秒
 */
@property (nonatomic, readonly) long talkingBeginTime;

/**
 * 获取通话状态
 *
 * 通话状态，参见：
 * - @ref JCCallStateInit : 初始
 * - @ref JCCallStatePending : 振铃
 * - @ref JCCallStateConnecting : 连接中
 * - @ref JCCallStateTalking : 通话中
 * - @ref JCCallStateOk : 通话正常结束
 * - @ref JCCallStateCancel : 未接通挂断
 * - @ref JCCallStateCanceled : 未接通被挂断
 * - @ref JCCallStateMissed : 未接
 * - @ref JCCallStateError : 异常
 */
@property (nonatomic, readonly) JCCallState state;

/**
 * 此路通话是否为挂起状态
 *
 * - true: 挂起状态
 * - false: 非挂起状态
 */
@property (nonatomic, readonly) bool hold;

/**
 * 此路通话是否为被挂起状态
 *
 * - true: 被挂起状态
 * - false: 非被挂起状态
 */
@property (nonatomic, readonly) bool held;

/**
 * 此路通话是否为静音状态
 *
 * @deprecated 从 v2.7.1 废弃。Juphoon 不建议你使用。建议使用 {@ref JCCall.muteMicrophone:mute: muteMicrophone} 方法开启/取消音频输入静音，
 * 并使用 @ref microphoneMute 属性获取此路通话是否为音频输入静音状态。

 * - true: 静音状态
 * - false: 不是静音状态
 */
@property (nonatomic, readonly) bool mute;

/**
 * 此路通话是否为音频输入静音状态
 *
 * - true: 静音状态
 * - false: 不是静音状态
 */
@property (nonatomic, readonly) bool microphoneMute;

/**
 * 此路通话是否为音频输出静音状态
 *
 * - true: 静音状态
 * - false: 不是静音状态
 */
@property (nonatomic, readonly) bool speakerMute;

/**
 * 此路通话是否为录音状态
 *
 * - true: 录音状态
 * - false: 非录音状态
 */
@property (nonatomic, readonly) bool audioRecord;

/**
 * 录音文件的保存路径
 */
@property (copy, nonatomic, readonly) NSString* __nullable audioRecordFilePath;

/**
 * 是否在录制本端视频
 *
 * - true: 正在录制本端视频
 * - false: 没有在录制本端视频
 */
@property (nonatomic, readonly) bool localVideoRecord;

/**
 * 本端视频录制文件的保存路径
 */
@property (copy, nonatomic, readonly) NSString* __nullable localVideoRecordFilePath;

/**
 * 是否在录制远端视频
 *
 * - true: 正在录制远端视频
 * - false: 没有在录制远端视频
 */
@property (nonatomic, readonly) bool remoteVideoRecord;

/**
 * 获取远端视频录制文件的保存路径
 */
@property (copy, nonatomic, readonly) NSString* __nullable remoteVideoRecordFilePath;

/**
 * 音频输出类型，根据类型判断是听筒，耳机，麦克风等
 */
@property (nonatomic, readonly, copy) NSString* __nullable audioOutputType;

/**
 * 是否激活状态，会议通话时忽略此参数
 *
 * - true: 激活状态
 * - false: 不是激活状态
 */
@property (nonatomic, readonly) bool active;

/**
 * 获取本端是否在上传视频流
 *
 * @note 针对视频通话有效
 *
 * 本端是否在上传视频流
 * - true: 本端在上传视频流
 * - false: 本端没有在上传视频流
 */
@property (nonatomic, readonly) bool uploadVideoStreamSelf;

/**
 * 获取对端是否在上传视频流
 *
 * @note 针对视频通话有效
 *
 * 对端是否在上传视频流
 * - true: 对端在上传视频流
 * - false: 对端没有在上传视频流
 */
@property (nonatomic, readonly) bool uploadVideoStreamOther;

/**
 * 获取通话结束原因
 *
 * 通话结束原因，参见 @ref JCCallReason "JCCall 结束原因"
 */
@property (nonatomic, readonly) JCCallReason reason;

/**
 * 音频发送网络状态
 *
 * - @ref JCCallNetWorkNA  : 未知状态
 * - @ref JCCallNetWorkDisconnected : 无网络
 * - @ref JCCallNetWorkVeryBad : 很差
 * - @ref JCCallNetWorkBad : 差
 * - @ref JCCallNetWorkNormal : 一般
 * - @ref JCCallNetWorkGood : 好
 * - @ref JCCallNetWorkVeryGood : 很好
 */
@property (nonatomic, readonly) JCCallNetWork audioNetSendStatus;

/**
 * 音频接收网络状态
 *
 * - @ref JCCallNetWorkNA  : 未知状态
 * - @ref JCCallNetWorkDisconnected : 无网络
 * - @ref JCCallNetWorkVeryBad : 很差
 * - @ref JCCallNetWorkBad : 差
 * - @ref JCCallNetWorkNormal : 一般
 * - @ref JCCallNetWorkGood : 好
 * - @ref JCCallNetWorkVeryGood : 很好
 */
@property (nonatomic, readonly) JCCallNetWork audioNetReceiveStatus;

/**
 * 视频发送网络状态
 *
 * - @ref JCCallNetWorkNA  : 未知状态
 * - @ref JCCallNetWorkDisconnected : 无网络
 * - @ref JCCallNetWorkVeryBad : 很差
 * - @ref JCCallNetWorkBad : 差
 * - @ref JCCallNetWorkNormal : 一般
 * - @ref JCCallNetWorkGood : 好
 * - @ref JCCallNetWorkVeryGood : 很好
 */
@property (nonatomic, readonly) JCCallNetWork videoNetSendStatus;

/**
 * 视频接收网络状态
 *
 * - @ref JCCallNetWorkNA  : 未知状态
 * - @ref JCCallNetWorkDisconnected : 无网络
 * - @ref JCCallNetWorkVeryBad : 很差
 * - @ref JCCallNetWorkBad : 差
 * - @ref JCCallNetWorkNormal : 一般
 * - @ref JCCallNetWorkGood : 好
 * - @ref JCCallNetWorkVeryGood : 很好
 */
@property (nonatomic, readonly) JCCallNetWork videoNetReceiveStatus;

/**
 * 获取自定义参数
 *
 * 即调用 {@link JCCall#call:video:callParam: call} 接口时，@ref JCCall#callParam "callParam" 入参对象的 @ref JCCallParam#extraParam "extraParam" 值
 *
 * @return 自定义参数
 */
@property (nonatomic, readonly, copy) NSString* __nullable extraParam;

/**
 * 获取服务端唯一通话CallId
 *
 * 可以用来通话去重，如果为空字符串则不能通过此字段来去重，说明此通话还未到服务器
 */
@property (nonatomic, readonly, copy) NSString* __nullable serverCallId;

/**
 * 对端声音是否中断
 * - true: 对端声音中断
 * - false: 对端声音没有中断
 */
@property (nonatomic, readonly) bool otherAudioInterrupt;

/**
 * 小系统通话中，标识通话唯一性
 *
 * 即调用 {@link JCCall#call:video:callParam: call} 接口时，@ref JCCallParam "callParam" 入参对象的 @ref JCCallParam.ticket "ticket" 值
 */
@property (nonatomic, readonly) NSString *__nullable ticket;


/**
 * 自动开启音频
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool autoStartAudio;

/**
 * 字符串信息
 * @return 返回 JCCallItem 实例信息
 */
-(NSString* __nonnull)toString;

/**
 * 启动自身视频渲染
 *
 * @param type 渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @return 渲染对象
 */
-(JCMediaDeviceVideoCanvas* __nullable)startSelfVideo:(JCMediaDeviceRender)type;

 /**
  * 停止自身视频渲染
  */
-(void)stopSelfVideo;

/**
 * 启动对端视频渲染
 *
 * @param type 渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @return 渲染对象
 */
-(JCMediaDeviceVideoCanvas* __nullable)startOtherVideo:(JCMediaDeviceRender)type;

/**
 * 停止对端视频渲染
 */
-(void)stopOtherVideo;

@end

/**
 * @}
 */
