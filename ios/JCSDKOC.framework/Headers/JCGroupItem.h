//
//  JCGroupItem.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/15.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCGroupConstants.h"

/**
 * @addtogroup 群组模块
 * @{
 */

/**
 * 群组对象类
 */
@interface JCGroupItem : NSObject

/**
 * 群组标识
 */
@property (nonatomic, copy, readonly) NSString* groupId;

/**
 * 群备注名称
 *
 * @note 仅自己可见
 */
@property (nonatomic, copy, readonly) NSString* nickName;

/**
 * 扩展信息
 *
 * @note 仅自己可见
 */
@property (nonatomic, copy, readonly) NSString* tag;

/**
 * 群名称
 */
@property (nonatomic, copy, readonly) NSString* name;

/**
 * 是否是免打扰状态
 * - true: 是免打扰状态
 * - false: 不是免打扰状态
 */
@property (nonatomic, readonly) bool dnd;

/**
 * 群组类型
 * - @ref JCGroupTypeDiscussion :  讨论组
 * - @ref JCGroupTypeNormal : 普通群
 */
@property (nonatomic, readonly) JCGroupType type;

/**
 * 自定义属性
 */
@property (nonatomic, readonly) NSDictionary<NSString*, NSObject*>* customProperties;

/**
 * 群组改变状态
 * - @ref JCGroupChangeStateNone : 无
 * - @ref JCGroupChangeStateAdd : 新增
 * - @ref JCGroupChangeStateUpdate : 更新
 * - @ref JCGroupChangeStateRemove : 删除
 * - @ref JCGroupChangeStateProperties : 群属性
 */
@property (nonatomic, readonly) JCGroupChangeState changeState;

/**
 * 最新一次更新时间
 */
//@property (nonatomic, readonly) long long updateTime;

/**
 * 构造 JCGroupItem
 * @param groupId     群组唯一标识
 * @param nickName   群备注名
 * @param tag              标签
 * @param dnd              是否免打扰
 * - true: 设置免打扰
 * - false: 不设置免打扰
 * @param changeState  群组变化状态
 * - @ref JCGroupChangeStateNone : 无
 * - @ref JCGroupChangeStateAdd : 新增
 * - @ref JCGroupChangeStateUpdate : 更新
 * - @ref JCGroupChangeStateRemove : 删除
 * - @ref JCGroupChangeStateProperties : 群属性
 * @return 返回 JCGroupItem 对象
 */
-(instancetype)init:(NSString*)groupId nickName:(NSString*)nickName tag:(NSString*)tag dnd:(bool)dnd changeState:(JCGroupChangeState)changeState;

/**
 * 构造 JCGroupItem
 * @param groupId      群组唯一标识
 * @param name             群名称
 * @param type             群组类型：
 * - @ref JCGroupTypeDiscussion : 讨论组
 * - @ref JCGroupTypeNormal : 普通群
 * @param customProperties 自定义属性
 * @return 返回 JCGroupItem 对象
 */
-(instancetype)init:(NSString*)groupId name:(NSString*)name type:(JCGroupType)type customProperties:(NSDictionary<NSString*, NSObject*>*)customProperties;

/**
 * 构造 JCGroupItem
 * @param groupId     群组唯一标识
 * @param changeState 群组变化状态：
 * - @ref JCGroupChangeStateNone : 无
 * - @ref JCGroupChangeStateAdd : 新增
 * - @ref JCGroupChangeStateUpdate : 更新
 * - @ref JCGroupChangeStateRemove : 删除
 * - @ref JCGroupChangeStateProperties : 群属性
 * @return 返回 JCGroupItem 对象
 */
-(instancetype)init:(NSString*)groupId changeState:(JCGroupChangeState)changeState;

@end

/**
 * @}
 */
