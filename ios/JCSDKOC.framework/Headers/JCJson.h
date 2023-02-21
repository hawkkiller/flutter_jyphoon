//
//  JCJson.h
//  JCSDKOC
//
//  Created by maikireton on 2017/9/8.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JCJson : NSObject

/**
 *  @brief 将 json 字符串转换为 NSMutableArray，NSMutableDictionary
 */
+(id)jsonToObj:(NSString*)json;

/**
 *  @brief 将 json 字符串转换为 NSMutableArray，NSMutableDictionary
 */
+(id)jsonCharToObj:(const char*)json;

/**
 *  @brief 将 NSArray，NSDictionary 对象转化为 json 字符串
 */
+(NSString*)objToJson:(id)obj;

@end
