//
//  JCAccountItem.h
//  JCSDKOC
//
//  Created by Ginger on 2018/6/8.
//  Copyright © 2018年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCAccountConstants.h"

/**
 * @addtogroup 账号模块
 * @{
 */

/**
 *  查询账号结果对象
 */
@interface JCAccountItem : NSObject

/**
 * 查询的账号
 */
@property (nonatomic, copy) NSString* __nonnull userId;
/**
 * 查询账号状态结果，参见：
 * - @ref JCAccountUserStatusError : 查询异常
 * - @ref JCAccountUserStatusNotFound : 用户未注册
 * - @ref JCAccountUserStatusOffline : 用户离线
 * - @ref JCAccountUserStatusPush : 用户推送状态
 * - @ref JCAccountUserStatusOnline : 用户在线
 */
@property (nonatomic, assign) JCAccountUserStatus status;

/**
 * 自定义状态0
 */
@property (nonatomic, copy) NSString *customStatus0;
/**
 * 自定义状态1
 */
@property (nonatomic, copy) NSString *customStatus1;
/**
 * 自定义状态2
 */
@property (nonatomic, copy) NSString *customStatus2;
/**
 * 自定义状态3
 */
@property (nonatomic, copy) NSString *customStatus3;

@end

/**
 * @}
 */
