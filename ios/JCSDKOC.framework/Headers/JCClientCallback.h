//
//  JCClientCallback.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/10.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCClientConstants.h"

/**
 * @addtogroup 登录模块
 * @{
 */

/**
 * JCClient 回调
 */
@protocol JCClientCallback <NSObject>

/**
 * 登录结果回调
 *
 * 在调用 {@link JCClient#login:password:loginParam: login} 方法成功后会收到此回调
 *
 * @param result 登录是否成功
 * - true：登录成功
 * - false：登录失败
 * @param reason 登录失败原因，当 result 为 false 时该值有效。参见：@ref JCClientReason  "错误原因"
 */
-(void)onLogin:(bool)result reason:(JCClientReason)reason;

/**
 * 登出回调
 *
 * 在调用 {@link JCClient#logout logout} 方法成功会收到此回调
 *
 * @param reason 登出失败原因，参见：@ref JCClientReason  "错误原因"
*/
-(void)onLogout:(JCClientReason)reason;

/**
 * 登录状态变化回调
 *
 * 在用户的登录状态发生改变时会收到此回调，登录状态：
 * - @ref JCClientStateNotInit : 未初始化
 * - @ref JCClientStateIdle : 未登录
 * - @ref JCClientStateLogining : 登录中
 * - @ref JCClientStateLogined : 登录成功
 * - @ref JCClientStateLogouting : 登出中
 *
 * @param state         当前状态值
 * @param oldState  之前状态值
*/
-(void)onClientStateChange:(JCClientState)state oldState:(JCClientState)oldState;

/**
 * 在线消息发送结果
 *
 * @param operationId 操作id, 由 @ref JCClient#sendOnlineMessage "sendOnlineMessage" 返回
 * @param result 消息发送是否成功
 */
-(void)onOnlineMessageSend:(int)operationId result:(bool)result;

/**
 * 收到在线消息
 *
 * @param userId 消息发送方用户标识
 * @param content 消息内容
 */
-(void)onOnlineMessageReceive:(NSString *)userId content:(NSString *)content;


@end

/**
 * @}
 */
