//
//  JCMessageChannel.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMessageChannelItem.h"
#import "JCMessageChannelCallback.h"

/**
 * @defgroup 消息通道模块
 * @{
 * 用于管理消息通道
 */

/**
 * 消息通道类，包括一对一消息和群组消息
 */
@interface JCMessageChannel : NSObject

/**
 * 缩率图保存路径
 *
 * 初始化会默认设置，同时用户可以自己设置
 */
@property (nonatomic, copy) NSString * __nonnull thumbDir;

/**
 * 创建 JCMessageChannel 对象
 *
 * JCMessageChannel 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 调用此方法创建 JCMessageChannel 对象后，期间没有调用过 {@link destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCMessageChannel 对象
 * - 调用此方法前确保 JCClient 已完成初始化，即 @ref JCClient.state "state" 状态值不等于 @ref JCClientStateNotInit
 *
 * @param client   JCClient 对象
 * @param callback JCMessageChannelCallback 回调接口，用于回调相关通知
 * @return 返回 JCMessageChannel 对象
 * @exception "JCClient、JCMessageChannelCallback 任意一个参数传空就会出现调用异常"
 */
+(JCMessageChannel* __nullable)create:(JCClient* __nonnull)client callback:(id<JCMessageChannelCallback> __nonnull)callback;

/**
 * 销毁 JCMessageChannel 对象
 *
 * 该方法为同步调用，需要等待 JCMessageChannel 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCMessageChannel 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCMessageChannel 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCMessageChannel 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 发送文本消息
 *
 * @note 文本内容不要超过10KB
 *
 * @param type        类型:
 * - @ref JCMessageChannelType1To1 : 一对一消息
 * - @ref JCMessageChannelTypeGroup : 群组消息
 * @param keyId       对方唯一标识:
 * - 当 type 为 @ref JCMessageChannelType1To1 时为对方的 serverUid
 * - 当 type 为 @ref JCMessageChannelTypeGroup 时为群组的 serverUid
 * @param messageType 文本消息类型，用户可以自定义，例如text，xml等
 * @param text        文本内容
 * @param extraParams 自定义参数集
 * @param cookie      标志数据
 * @param atAll       是否@群体成员，针对群消息
 * @param atServerUidList   "@"成员的serverUid列表 针对群消息
 * @return
 * - 成功返回 JCMessageChannelItem 对象，并且会收到 {@link JCMessageChannelCallback#onMessageSendUpdate: onMessageSendUpdate} 通知
 * - 异常返回 null
 */
-(JCMessageChannelItem* __nullable)sendMessage:(JCMessageChannelType)type keyId:(NSString* __nonnull)keyId messageType:(NSString* __nonnull)messageType text:(NSString* __nonnull)text extraParams:(NSDictionary* __nullable)extraParams cookie:(id __nullable)cookie atAll:(bool)atAll atServerUidList:(NSArray<NSString*>* __nullable)atServerUidList;

/**
 * 发送文件消息
 *
 * @param type        类型：
 * - @ref JCMessageChannelType1To1 : 一对一消息
 * - @ref JCMessageChannelTypeGroup : 群组消息
 * @param keyId       对方唯一标识
 * - 当 type 为 @ref JCMessageChannelType1To1 时为对方的 serverUid
 * - 当 type 为 @ref JCMessageChannelTypeGroup 时为群组的 serverUid
 * @param messageType 文件消息类型，用户可以自定义，例如image，video等
 * @param fileUri     文件链接地址
 * @param thumbUri    缩略图文件链接地址
 * @param size        文件大小(字节)
 * @param duration    文件时长，针对语音，视频等消息
 * @param extraParams 自定义参数集
 * @param cookie      标志数据
 * @param atAll       是否@群体成员，针对群消息
 * @param atUidList   "@"成员的serverUid列表 针对群消息
 * @return
 * - 成功返回 JCMessageChannelItem 对象，并且会收到  {@link JCMessageChannelCallback#onMessageSendUpdate: onMessageSendUpdate} 通知
 * - 失败返回 null
 */
-(JCMessageChannelItem* __nullable)sendFile:(JCMessageChannelType)type keyId:(NSString* __nonnull)keyId messageType:(NSString* __nonnull)messageType fileUri:(NSString* __nonnull)fileUri thumbUri:(NSString* __nullable)thumbUri size:(int)size duration:(int)duration extraParams:(NSDictionary* __nullable)extraParams cookie:(id __nullable)cookie atAll:(bool)atAll atServerUidList:(NSArray<NSString*>* __nullable)atServerUidList;

/**
 * 获取消息会话
 *
 * @param serverUid 用户 @ref JCClient#serverUid "serverUid" 或者群组的 @ref JCGroupItem#groupId "groupId"，传 null返回全部
 * @param lastQueryTime 上次查询返回的时间，单位毫秒
 * @return
 * - >0：操作id，结果通过 {@link JCMessageChannelCallback#onRefreshConversation:result:conversations:reason:updateTime:refreshServerUid:  onRefreshConversation} 通知
 * - -1：调用失败，不会收到回调
 */
-(int)refreshConversation:(NSString* __nullable)serverUid lastQueryTime:(long)lastQueryTime;

/**
 * 获取历史消息
 *
 * @param serverUid      用户 serverUid 或者群组的 serverUid
 * @param startMessageId 起始消息ID，如果-1从最新开始拉取
 * @param count          拉取历史消息条数
 * @param pack           消息列表是否一次性返回
 * @return
 * - >0：操作id，结果通过 {@link JCMessageChannelCallback#onFetchMessageResult:result:reason:  onFetchMessageResult} 通知
 * - -1：调用失败，不会收到回调
 */
-(int)fetchMessages:(nonnull NSString*)serverUid startMessageId:(long)startMessageId count:(int)count pack:(bool)pack;

/**
 * 标志消息为已读
 *
 * @param serverUid 用户 serverUid 或者群组的 serverUid
 * @param messageId 消息ID，如果-1表示最后一条消息
 * @return
 * - >0：操作id，结果通过 {@link JCMessageChannelCallback#onMarkReadResult:result:reason: onMarkReadResult} 通知
 * - -1：调用失败，不会收到回调
 */
-(int)markReadMessage:(nonnull NSString*)serverUid messageId:(long)messageId isGroup:(bool)isGroup;

/**
 * 标志消息为已收
 *
 * @param serverUid 用户 serverUid 或者群组的 serverUid
 * @param messageId 消息ID，如果-1表示最后一条消息
 * @return
 * - >0：操作id，结果通过 {@link JCMessageChannelCallback#onMarkRecvResult:result:reason: onMarkRecvResult} 通知
 * - -1：调用失败，不会收到回调
 */
-(int)markRecvMessage:(nonnull NSString*)serverUid messageId:(long)messageId;

/**
 * 撤回消息
 *
 * @param serverUid 用户 serverUid 或者群组的 serverUid
 * @param messageId 消息ID
 * @param content      文本内容
 * @return
 * - >0：操作id，结果通过 {@link JCMessageChannelCallback#onWithdrawalMessageResult:result:message:reason: onDrawBackMessageResult} 通知
 * - -1：调用失败，不会收到回调
 */
-(int)withdrawalMessage:(nonnull NSString*)serverUid messageId:(long)messageId content:(NSString* __nonnull)content;

@end

/**
 * @}
 */
