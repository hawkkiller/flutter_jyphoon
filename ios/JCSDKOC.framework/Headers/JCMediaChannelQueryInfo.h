//
//  JCMediaChannelQueryInfo.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/25.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @addtogroup 多方通话模块
 * @{
 */

/**
 *  多方通话查询信息结果
 */
@interface JCMediaChannelQueryInfo : NSObject

/**
 * 频道标识
 */
@property (nonatomic, readonly, copy) NSString* channelId;

/**
 * 频道号
 */
@property (nonatomic, readonly) int number;

/**
 * 开始时间
 */
@property (nonatomic, readonly) double startTime;

/**
 * 成员数
 */
@property (nonatomic, readonly) int clientCount;

/**
 * 获取成员列表
 */
@property (nonatomic, readonly, strong) NSMutableArray *members;

@end

/**
 * @}
 */
