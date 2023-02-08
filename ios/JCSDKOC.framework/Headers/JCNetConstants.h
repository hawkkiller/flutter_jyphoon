//
//  JCNetConstants.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/24.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @addtogroup 网络模块
 * @{
 */

/**
 *  网络类型
 */
typedef NS_ENUM(NSInteger, JCNetType) {
    /// 无网
    JCNetTypeUnavailable,
    /// Wifi
    JCNetTypeWifi,
    /// 数据网
    JCNetTypeMobile,
    /// 未知类型
    JCNetTypeUnknown,
};

/**
 * @}
 */
