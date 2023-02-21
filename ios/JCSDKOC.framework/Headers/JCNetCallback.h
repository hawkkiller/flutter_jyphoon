//
//  JCNetCallback.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/24.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCNetConstants.h"

/**
 * @addtogroup 网络模块
 * @{
 */

/**
 * JCNet 回调代理
 */
@protocol JCNetCallback <NSObject>

/**
 * 网络变化回调，网络类型参见：
 *  - @ref JCNetTypeUnavailable : 无网
 *  - @ref JCNetTypeWifi : Wifi
 *  - @ref JCNetTypeMobile : 数据网
 *  - @ref JCNetTypeUnknown : 未知类型
 *
 * @param newNetType 当前网络类型
 * @param oldNetType 之前网络类型
 */
-(void)onNetChange:(JCNetType)newNetType oldNetType:(JCNetType)oldNetType;

@end

/**
 * @}
 */
