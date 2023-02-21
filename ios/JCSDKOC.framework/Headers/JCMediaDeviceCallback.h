//
//  JCMediaDeviceCallback.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMediaDeviceConstants.h"

/**
 * @addtogroup 设备模块
 * @{
 */

/**
 * JCMediaDeviceCallback 回调
 */
@protocol JCMediaDeviceCallback <NSObject>

/**
 * 摄像头变化回调
 *
 * 开启、关闭、切换摄像头时会收到此回调
 */
-(void)onCameraUpdate;

/**
 * 音频输出类型变化回调
 *
 * 音频输出类型发生变化时会收到此回调，例如从扬声器状态变为耳机状态
 *
 * @param audioRouteType 音频输出类型
 */
-(void)onAudioOutputTypeChange:(NSString*)audioOutputType;

/**
 * 收到第一帧数据回调
 *
 * 一对一通话或多方通话通话时，收到第一帧数据时会收到此回调，在 {@link onRenderStart: onRenderStart} 之前收到
 *
 * @param canvas JCMediaDeviceVideoCanvas 渲染对象
 */
-(void)onRenderReceived:(JCMediaDeviceVideoCanvas*)canvas;

/**
 * 画面开始渲染回调
 *
 * 一对一通话或多方通话通话时，JCMediaDeviceVideoCanvas 渲染对象开始渲染画面，会收到此回调
 *
 * @param canvas JCMediaDeviceVideoCanvas 渲染对象
 */
-(void)onRenderStart:(JCMediaDeviceVideoCanvas*)canvas;

/**
 * 声音中断恢复回调
 *
 * 音频中断或恢复时会收到此回调
 *
 * @param interrupt 中断或恢复
 * - true 表示中断
 * - false 表示恢复
 */
-(void)onAudioInerruptAndResume:(BOOL)interrupt;

@end

/**
 * @}
 */
