//
//  JCMediaChannelParticipant.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMediaChannelConstants.h"

/**
 * @addtogroup 多方通话模块
 * @{
 */

/**
 * 上次更新到这次更新间的状态变化集合
 */
@interface JCMediaChannelParticipantChangeParam : NSObject

/**
 * 上传音频是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean audio;

/**
 * 上传视频是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean video;

/**
 * 图像请求大小是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean pictureSize;

/**
 * 成员类型是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean type;

/**
 * 成员网络状态是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean netStatus;

/**
 * 自定义状态变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean customState;

/**
 * 自定义角色变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) Boolean customRole;

/**
 * 音频订阅状态变化
 * - true：变化
 * - false：没变化
 */
@property (nonatomic) Boolean audioSubscribe;

@end

/**
 *  多方通话成员
 */
@interface JCMediaChannelParticipant : NSObject

/**
 * 用户标识
 */
@property (nonatomic, readonly, copy) NSString* userId;

/**
 * 渲染标识
 *
 * 用于 JCMediaDevice 中 {@link startVideo:pictureSize:  startVideo} 渲染视频使用
 */
@property (nonatomic, readonly, copy) NSString* renderId;

/**
 * 昵称
 */
@property (nonatomic, readonly, copy) NSString* displayName;

/**
 * 音量状态
 * - @ref JCMediaChannelVolumeStatusNone : 静音
 * - @ref JCMediaChannelVolumeStatusZero : 无声音  1
 * - @ref JCMediaChannelVolumeStatusLow : 低  1 - 30
 * - @ref JCMediaChannelVolumeStatusMid : 中  31 - 60
 * - @ref JCMediaChannelVolumeStatusHigh : 高  61 -100
 */
@property (nonatomic, readonly) JCMediaChannelVolumeStatus volumeStatus;

/**
 * 网络状态
 * - @ref JCMediaChannelNetStatusDisconnected : 无
 * - @ref JCMediaChannelNetStatusVeryBad : 非常差
 * - @ref JCMediaChannelNetStatusBad : 差
 * - @ref JCMediaChannelNetStatusNormal : 一般
 * - @ref JCMediaChannelNetStatusGood : 好
 * - @ref JCMediaChannelNetStatusVeryGood : 非常好
 */
@property (nonatomic, readonly) JCMediaChannelNetStatus netStatus;

/**
 * 是否开启了语音
 * - true: 已开启
 * - false: 未开启
 */
@property (nonatomic, readonly) bool audio;

/**
 * 是否开启了视频
 * - true: 已开启
 * - false: 未开启
 */
@property (nonatomic, readonly) bool video;

/**
 * 是否通过Sip接通
 * - true: 已接通
 * - false: 未接通
 */
@property (nonatomic, readonly) bool sipTalking;

/**
 * 获得成员类型
 * - @ref JCMediaChannelParticipantTypeNormal : 普通成员
 * - @ref JCMediaChannelParticipantTypePstn : Pstn成员
 * - @ref JCMediaChannelParticipantTypeWebrtc : Webrtc成员
 * - @ref JCMediaChannelParticipantTypeIrc : IRC成员
 */
@property (nonatomic, readonly) JCMediaChannelParticipantType type;

/**
 * 图像尺寸
 * - @ref JCMediaChannelPictureSizeNone : 不渲染
 * - @ref JCMediaChannelPictureSizeMin : 最小尺寸
 * - @ref JCMediaChannelPictureSizeSmall : 小尺寸
 * - @ref JCMediaChannelPictureSizeLarge : 大尺寸
 * - @ref JCMediaChannelPictureSizeMax : 最大尺寸
 */
@property (nonatomic, readonly) JCMediaChannelPictureSize pictureSize;

/**
 * 获得自定义角色值
 */
@property (nonatomic, readonly) JCMediaChannelCustomRole customRole;

/**
 * 获得自定义状态值
 */
@property (nonatomic, readonly) JCMediaChannelCustomState customState;

/**
 * 是否是创建者
 */
@property (nonatomic, readonly) bool isCreator;

/**
 * 是不是自己
 * - true: 是自己
 * - false: 不是自己
 */
@property (nonatomic, readonly) bool isSelf;

/**
 * 是否订阅了该成员的音频
 * - true：订阅
 * - false：未订阅
 */
@property (nonatomic, readonly) bool audioSubscribe;

/**
 * 字符串信息
 * @return 返回 JCMediaChannel 实例信息
 */
-(NSString*)toString;

/**
 * 开始渲染视频对象
 *
 * @param type  渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @param pictureSize 视频请求级别：
 * - @ref JCMediaChannelPictureSizeNone : 不渲染
 * - @ref JCMediaChannelPictureSizeMin : 最小尺寸
 * - @ref JCMediaChannelPictureSizeSmall : 小尺寸
 * - @ref JCMediaChannelPictureSizeLarge : 大尺寸
 * - @ref JCMediaChannelPictureSizeMax : 最大尺寸
 * @return 视频对象
 */
-(JCMediaDeviceVideoCanvas*)startVideo:(JCMediaDeviceRender)type pictureSize:(JCMediaChannelPictureSize)pictureSize;

/**
 * 停止渲染视频对象
 */
-(void)stopVideo;

@end

/**
 * @}
 */
