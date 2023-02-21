//
//  JCAccountCallback.h
//  JCSDKOC
//
//  Created by Ginger on 2018/6/8.
//  Copyright © 2018年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCAccountItem.h"
#import "JCAccountContact.h"

/**
 * @addtogroup 账号模块
 * @{
 */

/**
 * JCAccount 回调
 */
@protocol JCAccountCallback <NSObject>

/**
 * 查询账号状态结果回调
 *
 * @param operationId     操作ID, 由 {@link JCAccount#queryUserStatus: queryUserStatus} 接口返回
 * @param queryResult          查询是否成功
 * - true: 成功
 * - false: 失败
 * @param accountItemList 查询结果
 */
- (void)onQueryUserStatusResult:(int)operationId result:(BOOL)queryResult accountItemList:(NSArray<JCAccountItem*>*)accountItemList;

/**
 * 查询账号 ServerUid 结果回调
 *
 * @param operationId 操作ID, 由 {@link JCAccount#queryServerUid: queryServerUid} 接口返回
 * @param result      查询是否成功 成功但不一定所有查询 userId 都有 serverUid
 * - true: 成功
 * - false: 失败
 * @param resultMap   查询结果
 */
- (void)onQueryServerUidResult:(int)operationId result:(BOOL)queryResult serverUids:(NSDictionary<NSString*, NSString*>*)serverUids;

/**
 * 查询账号 UserId 结果回调
 *
 * @param operationId 操作ID, 由 {@link JCAccount#queryUserId: queryUserId} 接口返回
 * @param result      查询是否成功 成功但不一定所有查询 serverUid 都有 userId
 * - true: 成功
 * - false: 失败
 * @param resultMap   查询结果
 */
- (void)onQueryUserIdResult:(int)operationId result:(BOOL)queryResult userIds:(NSDictionary<NSString*, NSString*>*)userIds;

/**
 * 查询网络联系人列表结果回调
 *
 * @param operationId 操作ID, 由 {@link JCAccount#refreshContacts: refreshContacts} 接口返回
 * @param result      刷新是否成功
 * - true: 成功
 * - false: 失败
 * @param contacts    联系人队列
 * @param updateTime  服务器更新时间
 * @param fullUpdate  是否全更新
 * - true: 全更新
 * - false: 没有全更新
 */
- (void)onRefreshContacts:(int)operationId result:(BOOL)result contacts:(NSArray<JCAccountContact*>*)contacts updateTime:(long)updateTime fullUpdate:(bool)fullUpdate;

/**
 * 处理联系人结果回调
 *
 * @param operationId 操作ID，由 {@link JCAccount#dealContact:  dealContact} 接口返回
 * @param result            操作是否成功
 * - true: 成功
 * - false: 失败
 * @param reason            失败原因，当 result 为 false 时有效。参见：@ref JCAccountReason "错误码"
 */
- (void)onDealContact:(int)operationId result:(BOOL)result reason:(JCAccountReason)reason;

/**
 * 服务器联系人变化回调
 *
 * 调用 {@link JCAccount#refreshContacts: refreshContacts} 会触发此回调
 *
 * @param contactList 联系人列表
 */
- (void)onContactsChange:(NSArray<JCAccountContact*>*)contacts;

/**
 * 设置免打扰回调
 *
 * @param operationId   操作ID，由 {@link JCAccount#setDnd:dnd:  setDnd} 接口返回
 * @param result              操作是否成功
 * - true: 成功
 * - false: 失败
 * @param reason              失败原因，当 result 为 false 时有效，参见：@ref JCAccountReason "错误码"
 */
-(void)onSetContactDnd:(int)operationId result:(bool)result reason:(JCAccountReason)reason;

@end

/**
 * @}
 */
