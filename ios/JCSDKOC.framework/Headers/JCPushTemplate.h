//
//  JCPushInfo.h
//  JCSDKOC
//
//  Created by maikireton on 2017/9/15.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @addtogroup 推送模块
 * @{
 */

/**
 * 推送模板类
 */
@interface JCPushTemplate : NSObject

/**
 * 设置苹果服务器获取的token
 * @param deviceToken token 值
 * @param voip 是否是 voip token
 * @param debug 是否是 debug 模式
 */
-(id)initWithToken:(NSData*)deviceToken voip:(bool)voip debug:(bool)debug;

/**
 * 设置通话推送信息
 * @param sound 声音资源，例如 ring.m4r，为 nil 时则用默认声音
 * @param seconds 消息过期时间
 */
-(id)initWithCall:(NSString*)sound expiration:(int)seconds;

/**
 * 设置消息推送信息
 * @param infoType 消息类型
 * @param tip 提示内容，不包含发送者，例如 “xx:发送了条消息”，其中"发送了条消息"为tip值，如果要提示发送内容，则填 nil
 * @param sound 声音资源，例如 ring.m4r
 * @param seconds 消息过期时间
 */
-(id)initWithText:(NSString*)infoType tip:(NSString*)tip sound:(NSString*)sound expiration:(int)seconds;

/**
 * 推送数据字符串
 */
-(NSString*)getData;

@end

/**
 * @}
 */
