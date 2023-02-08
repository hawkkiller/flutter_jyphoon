//
//  JCGroup.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/15.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCGroupCallback.h"
#import "JCGroupConstants.h"
#import "JCGroupItem.h"

/**
 * @defgroup 群组模块
 * @{
 * 用于管理群组
 */

/**
 *  群操作类
 */
@interface JCGroup : NSObject

/**
 * 创建 JCGroup 对象
 *
 * JCGroup 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 调用此方法创建 JCGroup 对象后，期间没有调用过 {@link destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCGroup 对象
 * - 调用此方法前确保 JCClient 已完成初始化，即 @ref JCClient.state "state" 状态值不等于 @ref JCClientStateNotInit
 *
 * @param client JCClient 对象
 * @param callback JCGroupCallback 回调接口，用于回调相关通知
 * @return 返回 JCGroup 对象
 * @exception "JCClient、JCGroupCallback 任意一个参数传空就会出现调用异常"
 */
+(JCGroup* __nullable)create:(JCClient* __nonnull)client callback:(id<JCGroupCallback> __nonnull)callback;

/**
 * 销毁 JCGroup 对象
 *
 * 该方法为同步调用，需要等待 JCGroup 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCGroup 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCGroup 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCGroup 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 获取当前用户加入的群列表
 *
 * @param updateTime 最新一次记录的群列表服务器更新时间
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onFetchGroups:result:reason:groups:updateTime:baseTime:fullUpdate: onFetchGroups} 回调
 * - -1：调用失败，不会收到回调
 */
-(int)fetchGroups:(long)updateTime;

/**
 * 刷新群组信息
 *
 * @param groupId    群标识
 * @param updateTime 最新一次记录的该群服务器更新时间
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onFetchGroupInfo:result:reason:groupItem:members:updateTime:baseTime:fullUpdate: onFetchGroupInfo} 回调
 * - -1：调用失败，不会收到回调
 */
-(int)fetchGroupInfo:(NSString* __nonnull)groupId updateTime:(long)updateTime;

/**
 * 创建群
 *
 * @param members            JCGroupMember 列表
 * @param groupName        群名称
 * @param type                   群类型：
 * - @ref JCGroupTypeDiscussion : 讨论组
 * - @ref JCGroupTypeNormal : 普通群
 * @param customProperties 自定义属性
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onCreateGroup:result:reason:groupItem:updateTime:baseTime: onCreateGroup}  回调
 * - -1：调用失败，不会收到回调
 */
-(int)createGroup:(NSArray<JCGroupMember*>* __nonnull)members groupName:(NSString* __nonnull)groupName type:(JCGroupType)type customProperties:(NSDictionary<NSString*, NSObject*>* __nullable)customProperties;

/**
 * 更新群
 *
 * @param groupItem JCGroupItem 对象，其中 JCGroupItem 中 @ref JCGroupItem.changeState "changeState" 值不影响具体操作
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onCreateGroup:result:reason:groupItem:updateTime:baseTime: onCreateGroup}  回调
 * - -1：调用失败，不会收到回调
 */
-(int)updateGroup:(JCGroupItem* __nonnull)groupItem;

/**
 * 解散群组
 *
 * @note 群拥有者才能解散群组
 *
 * @param groupId 群标识
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onDissolve:result:reason:groupId: onDissolve} 回调
 * - -1：调用异常，不会收到回调通知
 */
-(int)dissolve:(NSString* __nonnull)groupId;

/**
 * 离开群组
 *
 * @param groupId 群标识
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onLeave:result:reason:groupId: onLeave} 回调
 * - -1：调用异常，不会收到回调通知
 */
-(int)leave:(NSString* __nonnull)groupId;

/**
 * 操作成员
 *
 * @param groupId 群标识
 * @param members JCGroupMember 对象列表，通过 @ref JCGroupItem.changeState "changeState" 值来表明增加，更新，删除成员操作
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onDealMembers:result:reason:groupId: onDealMembers} 回调
 * - -1：调用异常，不会收到回调通知
 */
-(int)dealMembers:(NSString* __nonnull)groupId members:(NSArray<JCGroupMember*>* __nonnull)members;

/**
 * 更新群备注信息
 *
 * @note 仅自己可见
 *
 * @param groupId  群标识
 * @param nickName 备注名
 * @param tagMap   额外信息
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onUpdateGroupComment:result:reason:groupId: onUpdateGroupComment} 回调
 * - -1：调用异常，不会收到回调通知
 */
-(int)updateGroupComment:(NSString* __nonnull)groupId nickName:(NSString* __nonnull)nickName tag:(NSDictionary<NSString*, NSObject*>* __nullable)tag;

/**
 * 设置免打扰
 *
 *
 *
 * @param groupId 群标识
 * @param dnd     是否免打扰
 * - true: 免打扰，
 * - false: 取消免打扰
 * @return
 * - >0：操作id，结果通过 {@link JCGroupCallback#onSetGroupDnd:result:reason:groupId: onSetGroupDnd} 回调
 * - -1：调用异常，不会收到回调通知
 */
-(int)setDnd:(NSString* __nonnull)groupId dnd:(bool)dnd;

@end

/**
 * @}
 */
