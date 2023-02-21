//
//  JCMediaDeviceConstants.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 设备模块
/// @{

/**
 *  窗口与屏幕角度
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceRotateAngle) {
    /// 窗口与屏幕角度 0°
    JCMediaDeviceRotateAngle0 = 0,
    /// 窗口与屏幕角度 90°
    JCMediaDeviceRotateAngle90 = 90,
    /// 窗口与屏幕角度 180°
    JCMediaDeviceRotateAngle180 = 180,
    /// 窗口与屏幕角度 270°
    JCMediaDeviceRotateAngle270 = 270,
};

/**
 *  渲染模式
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceRender) {
    /// 铺满窗口，会有裁剪
    JCMediaDeviceRenderFullScreen = 0,
    /// 全图像显示，会有黑边
    JCMediaDeviceRenderFullContent,
    /// 自适应
    JCMediaDeviceRenderFullAuto,
};

/**
 *  视频像素格式
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceVideoPixelFormat) {
    /// I420
    JCMediaDeviceVideoPixelFormatI420 = 1,
    /// IYUV
    JCMediaDeviceVideoPixelFormatIYUV = 2,
    /// RGB24
    JCMediaDeviceVideoPixelFormatRGB24 = 3,
    /// ABGR
    JCMediaDeviceVideoPixelFormatABGR = 4,
    /// ARGB
    JCMediaDeviceVideoPixelFormatARGB = 5,
    /// ARGB444
    JCMediaDeviceVideoPixelFormatARGB444 = 6,
    /// RGB565
    JCMediaDeviceVideoPixelFormatRGB565 = 7,
    /// ARGB1555
    JCMediaDeviceVideoPixelFormatARGB1555 = 8,
    /// YUY2
    JCMediaDeviceVideoPixelFormatYUY2 = 9,
    /// YV12
    JCMediaDeviceVideoPixelFormatYV12 = 10,
    /// UYVY
    JCMediaDeviceVideoPixelFormatUYVY = 11,
    /// MJPG
    JCMediaDeviceVideoPixelFormatMJPG = 12,
    /// NV21
    JCMediaDeviceVideoPixelFormatNV21 = 13,
    /// NV12
    JCMediaDeviceVideoPixelFormatNV12 = 14,
    /// BGRA
    JCMediaDeviceVideoPixelFormatBGRA = 15,
};

/**
 * 视频旋转角度
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceVideoAngel) {
    /// 自动
    JCMediaDeviceVideoAngelAuto = -1,
    /// 0°
    JCMediaDeviceVideoAngel0 = 0,
    /// 90°
    JCMediaDeviceVideoAngel90 = 90,
    /// 180°
    JCMediaDeviceVideoAngel180 = 180,
    /// 270°
    JCMediaDeviceVideoAngel270 = 270
};

/**
 * 摄像头类型
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceCameraType) {
    /// 未获取到摄像头
    JCMediaDeviceCameraTypeNone = 0,
    /// 前置摄像头
    JCMediaDeviceCameraTypeFront = 1,
    /// 后置摄像头
    JCMediaDeviceCameraTypeBack = 2,
    /// 未知摄像头
    JCMediaDeviceCameraTypeUnknown = 3
};

/**
 * 视频源类型
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceVideoSource) {
    /// 用户
    JCMediaDeviceVideoSourcePeer = 0,
    /// 采集设备
    JCMediaDeviceVideoSourceCapture = 1,
    /// 文件
    JCMediaDeviceVideoSourceFile = 2,
};

/**
 * 镜像类型
 */
typedef NS_ENUM(NSInteger, JCMediaDeviceMirror) {
    /// 不镜像
    JCMediaDeviceMirrorNone = 0,
    /// 水平方向镜像
    JCMediaDeviceMirrorHorizontal = 1,
    /// 竖直方向镜像
    JCMediaDeviceMirrorVertical = 2,
    /// 自动选择
    JCMediaDeviceMirrorAuto = 3,
    /// 转场动画，从左侧翻转
    JCMediaDeviceMirrorFromLeft = 4,
    /// 转场动画，从上侧翻转
    JCMediaDeviceMirrorFromTop = 8,
};

typedef NS_ENUM(NSInteger, JCMediaDeviceAudioAECType) {
    /// 开启硬件AEC
    JCMediaDeviceAudioAECTypeOn,
    /// 关闭硬件AEC
    JCMediaDeviceAudioAECTypeOff,
    /// 硬件AEC 自动
    JCMediaDeviceAudioAECTypeAuto
};

/// @}
