//
//  JCNet.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/24.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCNetConstants.h"
#import "JCNetCallback.h"

/**
 * @defgroup 网络模块
 * @{
 * 用于获取当前网络信息
 */

/**
 * 网络类
 */
@interface JCNet : NSObject

/**
 * 单例获得 JCNet 实例
 */
+ (JCNet*)shared;

/**
 * 网络类型
 *
 *  - @ref JCNetTypeUnavailable : 无网
 *  - @ref JCNetTypeWifi : Wifi
 *  - @ref JCNetTypeMobile : 数据网
 *  - @ref JCNetTypeUnknown : 未知类型
 */
@property (nonatomic, readonly) JCNetType netType;

/**
 * 是否有网
 *
 * @ref JCNetTypeUnknown 认为无网
 *
 * @return
 * - true 表示有网
 * - false 表示无网
 */
@property (nonatomic, readonly) BOOL hasNet;

/**
 * 设置回调
 * @param callback 回调对象
 */
-(void)addCallback:(id<JCNetCallback>)callback;

/**
 * 删除回调
 * @param callback 回调对象
 */
-(void)removeCallback:(id<JCNetCallback>)callback;

@end

/**
 * @}
 */
