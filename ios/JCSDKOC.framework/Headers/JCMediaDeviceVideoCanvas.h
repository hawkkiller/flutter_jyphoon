//
//  JCMediaDeviceVideoCanvas.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMediaDeviceConstants.h"
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
#define JCView UIView
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
#define JCView NSView
#endif

/**
 * @addtogroup 设备模块
 * @{
 */

/**
 *  视频对象
 */
@interface JCMediaDeviceVideoCanvas : NSObject

/**
 * 渲染标识
 */
@property (nonatomic, readonly) NSString* videoSource;

/**
 * 获取视频渲染视图
 */
@property (nonatomic, readonly, strong) JCView* videoView;

/**
 * 渲染模式
 */
@property (nonatomic, readonly) JCMediaDeviceRender renderType;

/**
 * 自定义数据
 */
@property (nonatomic) id customData;

/**
 * 更新视频渲染标识
 * @param videoSource 视频源
 * @return 成功返回 true，失败返回 false
 */
-(bool)replace:(NSString*)videoSource;

/**
 * 暂停视频渲染
 */
-(void)pause;

/**
 * 恢复视频渲染
 */
-(void)resume;

/**
 * 旋转角度，必须是90的倍数，该角度表示与屏幕正方向旋转后的夹角
 * @param angle 角度值
 * @return 是否成功
 * - true: 成功
 * - false: 失败
 */
-(bool)rotate:(int)angle;

/**
 * 视频通话截图
 *
 * 调用此方法时需要保证该视频对象正在渲染，否则将调用失败
 *
 * @param width     截屏宽度像素，-1为视频源像素
 * @param height    截屏高度像素，-1为视频源像素
 * @param filePath  **文件路径，需精确到文件名及格式，例如：/Documents/JuphoonCloud/picture.png。请确保目录存在且可写。**
 * @return 是否成功
 * - true: 成功
 * - false: 失败
 */
-(bool)snapshot:(int)width heigh:(int)height filePath:(NSString*)filePath;

/**
 * 镜像
 *
 * 调用此方法时需要保证该视频对象正在渲染，否则将调用失败
 *
 * @param mirrorType     镜像类型
 * @see JCMediaDeviceMirror
 * @return 是否成功
 * - true: 成功
 * - false: 失败
 */

-(bool)videoMirror:(JCMediaDeviceMirror)mirrorType;

/**
 * 对焦
 *
 * 调用此方法时需要保证该视频对象正在渲染，否则将调用失败
 *
 * @note
 * 前置摄像头可能会调用失败
 *
 * @param xPercent    焦点所在渲染视图 x 轴的比例,取值范围 0-1
 * @param yPercent    焦点所在渲染视图 y 轴的比例,取值范围 0-1
 * @return 是否成功
 * - true: 成功
 * - false: 失败
 */
-(bool)focus:(float)xPercent yPercent:(float)yPercent;

@end
