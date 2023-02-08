//
//  JCLog.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/22.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JCLog : NSObject

/**
 * @brief 上传日志
 * @param reason 原因描述
 * @return
 */
+(bool)uploadLog:(NSString*)reason;

/**
 *  打印 error 类型日志
 */
+(void)debug:(NSString*)type format:(NSString*)format, ...;

/**
 *  打印 info 类型日志
 */
+(void)info:(NSString*)type format:(NSString*)format, ...;

/**
 *  打印 error 类型日志
 */
+(void)error:(NSString*)type format:(NSString*)format, ...;

@end
