//
//  JCGroupCallback.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/15.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCGroupItem.h"
#import "JCGroupMember.h"
#import "JCGroupConstants.h"

/**
 * @addtogroup 群组模块
 * @{
 */

/**
 *  JCGroup 回调
 */
@protocol JCGroupCallback <NSObject>

/**
 * 拉取群列表结果回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#fetchGroups: fetchGroups} 接口返回
 * @param result      拉取群列表是否成功
 * true: 成功
 * false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groups      群列表
 * @param updateTime  服务器更新时间
 * @param baseTime    服务器上个版本更新时间
 * @param fullUpdated 是否全更新
 * - true: 全量更新
 * - false: 非全量更新
 */
-(void)onFetchGroups:(int)operationId result:(bool)result reason:(JCGroupReason)reason groups:(NSArray<JCGroupItem*>*)groups updateTime:(long)updateTime baseTime:(long)baseTime fullUpdate:(bool)fullUpdate;

/**
 * 拉取群详情结果回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#fetchGroupInfo: fetchGroupInfo} 接口返回
 * @param result      拉取群详情是否成功
 * true: 成功
 * false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupItem   JCGroupItem 对象
 * @param members     成员列表
 * @param updateTime  服务器更新时间
 * @param baseTime    服务器上个版本更新时间
 * @param fullUpdated 是否全更新
 * - true: 全量更新
 * - false: 非全量更新
 */
-(void)onFetchGroupInfo:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupItem:(JCGroupItem*)groupItem members:(NSArray<JCGroupMember*>*)members updateTime:(long)updateTime baseTime:(long)baseTime fullUpdate:(bool)fullUpdate;

/**
 * 群列表更新回调
 *
 * 调用 {@link JCGroup#fetchGroups: fetchGroups} 获取更新列表
 *
 * @param groupList  变化的 group
 * @param updateTime 服务器更新时间
 * @param baseTime   服务器上个版本更新时间
 */
-(void)onGroupListChange:(NSArray<JCGroupItem*>*)groups updateTime:(long)updateTime baseTime:(long)baseTime;

/**
 * 群信息更新回调
 *
 * 调用 {@link JCGroup#fetchGroupInfo:updateTime: fetchGroupInfo} 获取更新信息
 *
 * @param groupId    群标识
 * @param memberList 成员列表
 * @param updateTime 服务器更新时间
 * @param baseTime   服务器上个版本更新时间
 */
-(void)onGroupInfoChange:(NSString*)groupId members:(NSArray<JCGroupMember*>*)members updateTime:(long)updateTime baseTime:(long)baseTime;

/**
 * 创建群回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#createGroup:groupName:type:customProperties: createGroup} 接口返回
 * @param result      创建群是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupItem   JCGroupItem 对象
 * @param updateTime  服务器更新时间
 * @param baseTime    服务器上个版本更新时间
 */
-(void)onCreateGroup:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupItem:(JCGroupItem*)groupItem updateTime:(long)updateTime baseTime:(long)baseTime;;

/**
 * 更新群信息回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#updateGroup: updateGroup} 接口返回
 * @param result      更新群信息是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupId     群标识
 */
-(void)onUpdateGroup:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupId:(NSString*)groupId;

/**
 * 解散群组回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#dissolve: dissolve} 接口返回
 * @param result      解散群是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupId     群标识
 */
-(void)onDissolve:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupId:(NSString*)groupId;

/**
 * 离开群组回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#leave: leave} 接口返回
 * @param result      离开群组是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupId     群标识
 * @param updateTime  服务器更新时间
 * @param baseTime    服务器上个版本更新时间
 */
-(void)onLeave:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupId:(NSString*)groupId;

/**
 * 操作成员结果回调
 *
 * @param operationId   操作标识，由 {@link JCGroup#dealMembers:members: dealMembers} 接口返回
 * @param result      操作成员是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupId     群标识
 */
-(void)onDealMembers:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupId:(NSString*)groupId;

/**
 * 更新备注信息结果回调
 *
 * 调用 {@link JCGroup#updateGroupComment:nickName:tag: updateGroupComment} 接口 更新备注信息结果
 *
 * @param operationId   操作标识
 * @param result      更新备注信息是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupId     群标识
 */
-(void)onUpdateGroupComment:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupId:(NSString*)groupId;

/**
 * 设置免打扰回调
 *
 * 调用 {@link JCGroup#setDnd:dnd: setDnd} 接口 设置免打扰
 *
 * @param operationId   操作标识
 * @param result      设置免打扰是否成功
 * - true: 成功
 * - false: 失败
 * @param reason      失败原因，当 result 为 false 时该值有效，参见：@ref JCGroupReason "JCGroup 错误码"
 * @param groupId     群标识
 */
-(void)onSetGroupDnd:(int)operationId result:(bool)result reason:(JCGroupReason)reason groupId:(NSString*)groupId;


@end

/**
 * @}
 */
