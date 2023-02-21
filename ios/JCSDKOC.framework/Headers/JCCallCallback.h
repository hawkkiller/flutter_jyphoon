//
//  JCCallCallback.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCCallItem.h"

/**
 * @addtogroup 一对一通话模块
 * @{
 */

/**
 *  JCCall 回调
 */
@protocol JCCallCallback <NSObject>

/**
 * 新增通话回调
 *
 * 当上层收到此回调时，可以根据 JCCallItem 对象获得该通话的所有信息及状态，从而更新该通话相关UI
 *
 * @param item JCCallItem 对象
 */
-(void)onCallItemAdd:(JCCallItem* __nonnull)item;

/**
 * 移除通话回调
 *
 * 当上层收到此回调时，可以根据 JCCallItem 对象获得该通话的所有信息及状态，从而更新该通话相关UI
 *
 * @param item                 JCCallItem 对象
 * @param reason            通话结束原因，参见：@ref JCCallReason "通话结束原因"
 * @param description 通话结束原因的描述，只有被动挂断的时候，才会收到这个值，其他情况下则返回空字符串
 */
-(void)onCallItemRemove:(JCCallItem* __nonnull)item reason:(JCCallReason)reason description:(NSString * __nullable)description;

/**
 * 通话状态更新回调
 *
 * 当上层收到此回调时，可以根据 JCCallItem 对象获得该通话的所有信息及状态，从而更新该通话相关UI
 *
 * @param item                 JCCallItem 对象
 * @param changeParam JCCallChangeParam 更新标识对象
 */
-(void)onCallItemUpdate:(JCCallItem* __nonnull)item changeParam:(JCCallChangeParam * __nullable)changeParam;

/**
 * 通话中收到消息的回调
 *
 * @param type    消息类型，对应 {@link JCCall#sendMessage:type:content: sendMessage} 方法中的 type 参数
 * @param content 消息内容，对应 {@link JCCall#sendMessage:type:content: sendMessage}  方法中的 content 参数
 * @param item    JCCallItem 对象
 */
-(void)onMessageReceive:(JCCallItem * __nonnull)item type:(NSString * __nonnull)type content:(NSString * __nonnull)content;

/**
 * 拉取未接来电的回调
 *
 * 有以下几种情况会收到此回调：
 * - 用户A未登录，用户B呼叫用户A，用户A登录后收到此回调
 * - 用户A已登录，但没开启应用，用户A在开启应用重新登录后会收到此回调
 * - 已存在语音通话又收到了视频通话来电，此时会收到此回调
 * - 已存在视频通话又收到了语音或视频来电，此时会收到此回调
 * - 当前通话数量已达到最大通话数时又收到了语音或视频来电，此时会收到此回调
 * @param item JCCallItem 对象
 */
-(void)onMissedCallItem:(JCCallItem * __nonnull)item;

/**
 * 通话中收到DTMF回调
 *
 * @param item  JCCallItem 对象
 * @param value @ref JCCallDtmf "DTMF值"
 */
- (void)onDtmfReceived:(JCCallItem *_Nonnull)item value:(JCCallDtmf)value;

@end

/**
 * @}
 */
