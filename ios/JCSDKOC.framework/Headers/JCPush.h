//
//  JCPush.h
//  JCSDKOC
//
//  Created by maikireton on 2017/9/14.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCPushTemplate.h"

/**
 * @defgroup 推送模块
 * @{
 * 用于管理推送
 */

/**
 * 推送类，其中的接口请在登录成功后调用
 */
@interface JCPush : NSObject

/**
 * 创建 JCPush 对象
 *
 * @param client   JCClient 对象
 * @return 返回 JCPush 对象
 */
+(JCPush*)create:(JCClient*)client;

/**
 * 销毁 JCPush 对象
 *
 * 该方法为同步调用，需要等待 JCPush 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCPush 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCPush 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCPush 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 添加推送模板，用于服务器将不同类型的推送以不同的内容格式推给客户端
 *
 * @param info 推送信息
 */
-(void)addPushInfo:(JCPushTemplate*)info;

/**
 * 添加自定义推送模板，用于服务器将不同类型的推送以不同的内容格式推给客户端，登录成功后调用
 * @param pushTemplate     json格式字符串 包含Token模板，通话模板和消息模板，可以根据需要选择对应的模板进行配置，但是最终的json必须包含Token模板
 * 格式为：
 * {
     //通话推送模板格式, JCCall 使用
     "Notify.APNS.AppId": "注册推送服务的AppId,需要与您在Juphoon网站上传证书时填入的AppId一致",
     "Notify.APNS.Invite.ResendCount": "推送内容重发次数，会加1", //例如填5，则会发送6次
     "Notify.APNS.Invite.ResendTimeout": "推送通知重发的超时时间，即每次重发的时间间隔，单位为妙",
     "Notify.APNS.Invite.Expiration": "推送过期时间",
     "Notify.APNS.Token": "注册推送时苹果下发的设备令牌，需转为16进制字符串"
     "Notify.APNS.Invite.Payload": {  // 推送的内容,必须包含一个aps键
         "aps": {
             "alert": {
                 "loc-args": ["${Caller}"],    // ${Caller}表示服务器传入的主叫userId，如果主叫设置了昵称则显示昵称
                 "loc-key": "${MediaType} call from %@"  //${MediaType}表示服务器传入的呼叫类型(视频或音频)，%@将会被 loc-args 中的宏定义替代
             },
             "sound": "%@"  //通知铃声，值为APP资源文件内或者Library/Sounds文件夹内的铃声文件名,如果文件不能被找到或者设置了默认值，则会使用系统默认铃声
         },
         "callid": "${CallId}", // ${CallId}表示服务器生成的callid
         "resend": "${ResendIndex}"  //${ResendIndex}表示服务器返回的第几次重发
     }, //Payload可灵活配置，具体参考官网，https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/CreatingtheNotificationPayload.html#//apple_ref/doc/uid/TP40008194-CH10-SW1
     
     //文本类消息推送模板格式 JCMessageChannel 使用
     "Notify.APNS.Message.Info.text.Expiration": "推送消息过期时间", // text 为 sendMessage 中传入的 type
     "Notify.APNS.Message.Info.text.Payload":{ // 推送的内容,必须包含一个aps键
         "aps": {
             "alert": {
                 "loc-key": "收到来自%@的消息: %@",  // %@将会被 loc-args 中的宏定义替代
                 "loc-args": ["${Sender}", "${Text}"]    //${Sender}表示服务器传入的消息发送者，${Text}表示消息的内容
             },
             "badge": 1,    // 代表app图标右上角的消息数，如果不包含这个key值，消息数量不会改变，如果要删掉这个                                  badge，则把对应的key值设为0即可

             "sound": "default"    // 当推送信息送达时手机播放的声音，传defalut就标明使用系统默认声音
         },
         "to": "${Receiver}"    //${Receiver}表示服务器传入的消息接收对象
     }
 }
 *
 *例如：
 {
     "Notify.APNS.AppId": "com.juphoon.cloud.JCSample", // APNS生产环境
     //"Notify.APNS.AppId": "com.juphoon.cloud.JCSample.DEBUG", // APNS沙盒环境
     //"Notify.APNS.AppId": "com.juphoon.cloud.JCSample.VOIP", // VOIP 生产环境
     //"Notify.APNS.AppId": "com.juphoon.cloud.JCSample.VOIP.DEBUG", // VOIP 沙盒环境
     "Notify.APNS.Token": "640652DF9891C3CDD7AB30086697713233AAA72F74924A36FAC3C1E60B30AF16",
     "Notify.APNS.Invite.ResendCount": "3",
     "Notify.APNS.Invite.ResendTimeout": "3",
     "Notify.APNS.Invite.Expiration": "3",
     "Notify.APNS.Invite.Payload": {
         "aps": {
             "alert": {
                 "loc-args": ["${Caller}", "${MediaType}"],
                 "loc-key": "收到%@的%@来电"
             },
             "sound": "default"
         },
         "callid": "${CallId}",
         "resend": "${ResendIndex}"
     },
     "Notify.APNS.Message.Info.text.Expiration": "20",
     "Notify.APNS.Message.Info.text.Payload": {
         "aps": {
             "alert": {
                 "loc-key": "收到来自%@的消息: %@",
                 "loc-args": ["${Sender}", "${Text}"]
             },
             "badge": 1,
             "sound": "default"
         },
         "to": "${Receiver}"
     }
 }
 *
 */
-(void)addPushTemplate:(NSString *)pushTemplate;

@end

/**
 * @}
 */
