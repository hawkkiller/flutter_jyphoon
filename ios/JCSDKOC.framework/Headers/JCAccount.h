//
//  JCAccount.h
//  JCSDKOC
//
//  Created by Ginger on 2018/6/8.
//  Copyright © 2018年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCAccountCallback.h"
#import "JCAccountItem.h"

/**
 * @defgroup 账号模块
 * @{
 * 用于管理账号
 */

/**
 * 账号类
 */
@interface JCAccount : NSObject

/**
 * 创建 JCAccount 对象
 *
 * JCAccount 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @param callback    JCAccountCallback 回调接口，用于回调相关通知
 * @return JCAccount  对象
 * @exception "JCCallCallback 传空会出现调用失败"
 */
+ (JCAccount* __nullable)create:(id<JCAccountCallback> __nonnull)callback;

/**
 * 销毁 JCAccount 对象
 *
 * 该方法为同步调用，需要等待 JCAccount 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCAccount 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCAccount 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCAccount 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+ (void)destroy;

/**
 * 查询账号状态
 *
 * @param userIdArray  查询的账号列表
 * @return
 * - >0：操作id，结果通过 {@link JCAccountCallback#onQueryUserStatusResult:result:accountItemList: onQueryUserStatusResult} 通知
 * - -1：调用失败，不会收到回调
 */
- (int)queryUserStatus:(NSArray<NSString*>* __nonnull)userIdArray;

/**
 * 查询账号在服务器上的 uid
 *
 * @param userIdArray    查询的账号列表
 * @return
 * - >0：操作id，结果通过 {@link JCAccountCallback#onQueryServerUidResult:result:serverUids: onQueryServerUidResult} 通知
 * - -1：调用失败，不会收到回调
 */
- (int)queryServerUid:(NSArray<NSString*>* __nonnull)userIdArray;

/**
 * 查询账号 userId
 *
 * @param serverUidArray    查询的账号列表
 * @return
 * - >0：操作id，结果通过 {@link JCAccountCallback#onQueryUserIdResult:result:userIds: onQueryUserIdResult} 通知
 * - -1：调用失败，不会收到回调
 */
- (int)queryUserId:(NSArray<NSString*>* __nonnull)serverUidArray;

/**
 * 查询所有的联系人（支持增量）
 *
 * @param lastQueryTime 上次更新时间戳
 * @return
 * - >0：操作id，结果通过 {@link JCAccountCallback#onRefreshContacts:result:contacts:updateTime:fullUpdate: onRefreshContacts} 通知
 * - -1：调用失败，不会收到回调
 */
- (int)refreshContacts:(long)lastQueryTime;

/**
 * 操作联系人
 *
 * @param contact 联系人对象
 * @return
 * - >0：操作id，结果通过 {@link JCAccountCallback#onDealContact:result:reason: onDealContact} 通知
 * - -1：调用失败，当方法入参 JCAccountContact 传空时出现调用失败，不会收到回调
 */
- (int)dealContact:(JCAccountContact* __nonnull)contact;

/**
 * 设置免打扰
 *
 * @param serverUid     服务器自己的 uid
 * @param dnd                  是否免打扰
 * - true：设置免打扰，
 * - false：取消免打扰
 * @return
 * - >0：操作id，结果通过 {@link JCAccountCallback#onSetContactDnd:result:reason: onSetContactDnd} 通知
 * - -1：调用失败，不会收到回调
 */
- (int)setDnd:(NSString* __nonnull)serverUid dnd:(bool)dnd;

/// @cond Doxygen_All
/**
 * 设置自己自定义状态
 *
 * @param customStatus 自定义状态类型, @ref JCAccountCustomStatusType "自定义状态"
 * @param value       自定义状态值
 * @return 操作是否成功
 */
- (bool)setCustomStatus:(JCAccountCustomStatusType)customStatus value:(NSString *_Nonnull)value;
/// @endcond

/**
 * 添加回调
 *
 * @param callback JCAccountCallback 接口对象
 */
- (void)addCallback:(id<JCAccountCallback> __nonnull)callback;

/**
 * 删除回调
 *
 * @param callback JCAccountCallback 接口对象
 */
- (void)removeCallback:(id<JCAccountCallback> __nonnull)callback;


@end

/**
 * @}
 */
