//
//  JCGroupMember.h
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
 *  群组成员类
 */
@interface JCGroupMember : NSObject

/**
 * 群组标识
 */
@property (nonatomic, copy) NSString* groupId;

/**
 * 用户标识
 */
@property (nonatomic, copy) NSString* userId;

/**
 * 服务器端用户标识
 * 当通知成员变化时，changeState 为 @ref JCGroupChangeStateRemove 时只能通过此参数来判断，不能通过 userId
 */
@property (nonatomic, copy) NSString* uid;

/**
 * 用户昵称
 */
@property (nonatomic, copy) NSString* displayName;

/**
 * 角色类型：
 * - @ref JCGroupMemberTypeOwner : 拥有者
 * - @ref JCGroupMemberTypeManager : 管理员
 * - @ref JCGroupMemberTypeMember: 群成员
 */
@property (nonatomic) JCGroupMemberType memberType;

/**
 * 成员改变状态：
 * - @ref JCGroupChangeStateNone : 无
 * - @ref JCGroupChangeStateAdd : 新增
 * - @ref JCGroupChangeStateUpdate : 更新
 * - @ref JCGroupChangeStateRemove : 删除
 * - @ref JCGroupChangeStateProperties : 群属性
 */
@property (nonatomic) JCGroupChangeState changeState;

/**
 *  构造 JCGroupMember
 *  @param groupId 群组唯一标识
 *  @param userId 用户标识
 *  @param uid 服务器端用户标识
 *  @param displayName 昵称
 *  @param memberType 成员类型
 * - @ref JCGroupMemberTypeOwner : 拥有者
 * - @ref JCGroupMemberTypeManager : 管理员
 * - @ref JCGroupMemberTypeMember : 群成员
 *  @param changeState 成员变化状态：
 * - @ref JCGroupChangeStateNone : 无
 * - @ref JCGroupChangeStateAdd : 新增
 * - @ref JCGroupChangeStateUpdate : 更新
 * - @ref JCGroupChangeStateRemove : 删除
 * - @ref JCGroupChangeStateProperties : 群属性
 * @return JCGroupMember 对象
 */
-(instancetype)init:(NSString*)groupId userId:(NSString*)userId uid:(NSString*)uid displayName:(NSString*)displayName memberType:(JCGroupMemberType)memberType changeState:(JCGroupChangeState)changeState;

@end

/**
 * @}
 */
