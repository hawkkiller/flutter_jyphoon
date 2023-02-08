//
//  JCMediaChannel.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCMediaChannelCallback.h"
#import "JCMediaChannelParticipant.h"
#import "JCMediaChannelConstants.h"
#import "JCMediaChannelQueryInfo.h"

/**
 * @defgroup 多方通话模块
 * @{
 * 用于管理多方通话
 */

/**
 * 额外信息类
 */
@interface JCMediaChannelSipParamExtra : NSObject
/**
 * {@link JCMediaChannel#inviteSipUser:sipParam: inviteSipUser} 函数的入参 userId  的格式是号码还是 sipUri，默认入参为号码
 * - true: sipUri
 * - false: 号码
 */
@property (nonatomic) bool sipUri;
/**
 * 决定 sip 信令是否路由到 userId 的 sip 域里，sipUri 为 true 才生效，默认不路由
 * - true:  sip 信令路由到 userId 的 sip 域里
 * - false:  sip 信令不路由到 userId 的 sip 域里
 */
@property (nonatomic) bool route;
/**
 * sip用户加入会议后的昵称
 */
@property (nonatomic, strong) NSString* __nullable displayName;
/**
 * {@link JCMediaChannel.inviteSipUser:sipParam: inviteSipUser} 函数的入参 userId 是否为 Mcu 会议，默认不是 Mcu 会议
 * - true: Mcu 会议
 * - false: 不是 Mcu 会议
 */
@property (nonatomic) bool mcu;
/**
 * 是否需要视频接入，默认不需要
 * - true: 需要视频接入
 * - false: 不需要视频接入
 */
@property (nonatomic) bool video;
/**
 * dtmf 密码
 */
@property (nonatomic, strong) NSString* __nullable dtmfPassowrd;
/**
 * 将成员变量 sipUri、rout、displayName、mcu、video、dtmfPassword 组装成 json 字符串
 *
 * @return json 字符串
 */
-(NSString* __nonnull)toParamString;

@end

/**
 * Sip 参数类
 */
@interface JCMediaChannelSipParam : NSObject

/**
 * SIP呼叫 主叫号码
 */
@property (nonatomic, strong) NSString* __nullable callerNumber;
/**
 * 核心网ID
 */
@property (nonatomic, strong) NSString* __nullable coreNetwork;
/**
 * 额外信息
 */
@property (nonatomic) JCMediaChannelSipParamExtra* __nullable extra;

@end

/**
  * 录制高级参数
  */
@interface JCMediaChannelRecordParamVideoConfig : NSObject
     
/** 录制器录制时订阅的订阅等级, 默认为 JCMediaChannelVideoLevelMin */
@property (nonatomic) JCMediaChannelVideoLevel videoLevel;
/** 录制混屏模式，默认为 JCMediaChannelMergeModeIntellegence  */
@property (nonatomic) JCMediaChannelMergeMode mergeMode;
/**
 * 混屏的详细模式, 默认为 JCMediaChannelMergeModeExFreelayoutI, 当 mergeMode 为 JCMediaChannelMergeModeIntellegence 有效
 */
@property (nonatomic) JCMediaChannelMergeModeEx mergeModeEx;
/** 录制帧速率 1-30，默认为 20 */
@property (nonatomic) int mergeFPS;
/**  录制码率kpbs，默认为 300， 当 mergeMode 为 JCMediaChannelMergeModeIntellegence 有效 */
@property (nonatomic) int mergeBitrate;
/** 录制文件高 1-1080,  默认为 0 表示自动设置，当 mergeMode 为 JCMediaChannelMergeModeIntellegence 有效 */
@property (nonatomic) int mergeHeight;
/** 录制文件宽 1-1920，默认为 0 表示自动设置，当 mergeMode 为 JCMediaChannelMergeModeIntellegence 有效 */
@property (nonatomic) int mergeWidth;

@end

/**
 * 录制其他参数
 */
@interface JCMediaChannelRecordParam : NSObject

/**
 * 录制字符串
 *
 * 该属性在调用 {@link JCMediaChannel#enableRecord:recordParam: enableRecord} 录制视频时 recordParam 参数中用到，建议使用 {@link buildQiniuRecordParam:bucketName:secretKey:accessKey:fileName: buildQiniuRecordParam} 或 {@link buildAliossRecordParam:bucketName:secretKey:accessKey:fileName:endpoint: buildAliossRecordParam} 方法构造生成，不建议自己生成
 */
@property (nonatomic, strong) NSString* __nonnull recordString;

/**
 * 七牛录制参数构造
 *
 * bucketName、secretKey、accessKey 参数通过七牛开发者平台获取
 *
 * @param video 是否是视频录制
 * @param bucketName 七牛云 bucketName
 * @param secretKey 七牛云 secretKey
 * @param accessKey 七牛云 accessKey
 * @param fileName 录制文件名
 * @return 录制参数字符串
 */
+(NSString* __nonnull)buildQiniuRecordParam:(BOOL)video bucketName:(NSString* __nonnull)bucketName secretKey:(NSString* __nonnull)secretKey accessKey:(NSString* __nonnull)accessKey fileName:(NSString* __nonnull)fileName;

/**
 * 七牛录制参数构造
 *
 * bucketName、secretKey、accessKey 参数通过七牛开发者平台获取
 *
 * @param video 是否是视频录制
 * @param bucketName 七牛云 bucketName
 * @param secretKey 七牛云 secretKey
 * @param accessKey 七牛云 accessKey
 * @param fileName 录制文件名
 * @param videoConfig 录制高级参数
 * @return 录制参数字符串
 */
+(NSString* __nonnull)buildQiniuRecordParam:(BOOL)video bucketName:(NSString* __nonnull)bucketName secretKey:(NSString* __nonnull)secretKey accessKey:(NSString* __nonnull)accessKey fileName:(NSString* __nonnull)fileName videoConfig:(JCMediaChannelRecordParamVideoConfig* __nullable)videoConfig;

/**
 * 阿里云录制参数构造
 *
 * bucketName、secretKey、accessKey、endpoint 参数通过阿里云开发者平台获取
 *
 * @param video 是否是视频录制
 * @param bucketName 阿里云 bucketName
 * @param secretKey 阿里云 secretKey
 * @param accessKey 阿里云 accessKey
 * @param endpoint 阿里云 endpoint
 * @param fileName 录制文件名
 * @return 录制参数字符串
 */
+(NSString* __nonnull)buildAliossRecordParam:(BOOL)video bucketName:(NSString* __nonnull)bucketName secretKey:(NSString* __nonnull)secretKey accessKey:(NSString* __nonnull)accessKey endpoint:(NSString* __nonnull)endpoint fileName:(NSString* __nonnull)fileName;

/**
 * 阿里云录制参数构造
 *
 * bucketName、secretKey、accessKey、endpoint 参数通过阿里云开发者平台获取
 *
 * @param video 是否是视频录制
 * @param bucketName 阿里云 bucketName
 * @param secretKey 阿里云 secretKey
 * @param accessKey 阿里云 accessKey
 * @param endpoint 阿里云 endpoint
 * @param fileName 录制文件名
 * @param videoConfig 录制高级参数
 * @return 录制参数字符串
 */
+(NSString* __nonnull)buildAliossRecordParam:(BOOL)video bucketName:(NSString* __nonnull)bucketName secretKey:(NSString* __nonnull)secretKey accessKey:(NSString* __nonnull)accessKey endpoint:(NSString* __nonnull)endpoint fileName:(NSString* __nonnull)fileName videoConfig:(JCMediaChannelRecordParamVideoConfig* __nullable)videoConfig;

/**
 * minio录制参数构造
 *
 * bucketName、secretKey、accessKey、endpoint 参数通过阿里云开发者平台获取
 *
 * @param video 是否是视频录制
 * @param bucketName minio bucketName
 * @param secretKey minio secretKey
 * @param accessKey minio accessKey
 * @param endpoint minio endpoint
 * @param fileName 录制文件名
 * @return 录制参数字符串
 */
+(NSString *__nonnull)buildMinioRecordParam:(BOOL)video bucketName:(NSString *__nonnull)bucketName secretKey:(NSString *__nonnull)secretKey accessKey:(NSString * __nonnull)accessKey endpoint:(NSString * __nonnull)endpoint fileName:(NSString * __nonnull)fileName;

/**
 * minio录制参数构造
 *
 * bucketName、secretKey、accessKey、endpoint 参数通过minio开发者平台获取
 *
 * @param video 是否是视频录制
 * @param bucketName minio bucketName
 * @param secretKey minio secretKey
 * @param accessKey minio accessKey
 * @param endpoint minio endpoint
 * @param fileName 录制文件名
 * @param videoConfig 录制高级参数
 * @return 录制参数字符串
 */

+(NSString *__nonnull)buildMinioRecordParam:(BOOL)video bucketName:(NSString *__nonnull)bucketName secretKey:(NSString *__nonnull)secretKey accessKey:(NSString * __nonnull)accessKey endpoint:(NSString * __nonnull)endpoint fileName:(NSString * __nonnull)fileName videoConfig:(JCMediaChannelRecordParamVideoConfig* __nullable)videoConfig;


@end

/**
 * 加入会议参数类 作为 {@link JCMediaChannel#join:joinParam: join} 方法最后一个参数的入参
 */
@interface JCMediaChannelJoinParam : NSObject

/**
 * 会议最大人数，默认值为 16
 */
@property (nonatomic) int capacity;
/**
 * 推流参数，默认为 nil
 *
 * 如果用户在加入会议时没有设置推流参数，就无法进行推流
 */
@property (nonatomic, strong) NSString* __nullable cdn;
/**
 * 录制参数，默认为 nil
 *
 * 如果用户在加入会议时没有设置录制参数，就无法进行视频录制
 */
@property (nonatomic, strong) JCMediaChannelRecordParam * __nullable record;
/**
 * 密码，默认为 "123456"
 */
@property (nonatomic, strong) NSString* __nonnull password;
/**
 * 是否开启平滑模式，默认开启
 * - true: 开启
 * - false: 不开启
 */
@property (nonatomic) bool smooth;
/**
 * 会议最大分辨率，默认为 @ref JCMediaChannelMaxResolution360 ：
 * - @ref JCMediaChannelMaxResolution360 : 最大分辨率 360p
 * - @ref JCMediaChannelMaxResolution720 : 最大分辨率 720p
 * - @ref JCMediaChannelMaxResolution1080 : 最大分辨率 1080p
 */
@property (nonatomic) JCMediaChannelMaxResolution maxResolution;
/// @cond Doxygen_All
/**
 * 是否开启 uri 模式，{@link join:joinParam: join} 函数的参数为会议 uri，默认不开启
 * - true: 开启
 * - false: 不开启
 */
@property (nonatomic) bool uriMode;
/// @endcond
/**
 * 心跳间隔，默认值为 20
 */
@property (nonatomic) int heartbeatTime;
/**
 * 心跳超时，默认值为 60
 */
@property (nonatomic) int heartbeatTimeout;
/**
 * 帧率 1-30, 默认值为 24
 */
@property (nonatomic) int framerate;
/**
 * 自定义属性，默认为 ""
 */
@property (nonatomic, strong) NSString* __nullable customProperty;
/**
 * 自定义媒体每层参数
 *
 * - 1、格式
 * 高基数 第一层高倍数 第一层码率 第二层高倍数 第二层码率 第三层高倍数 第三层码率 第四层高倍数 第四层码率 <br>
 * 说明 <br>
 * 1）默认宽高比16:9 <br>
 * 2）编码宽高最后被裁成16整除 <br>
 * 3）码率计算可大致参考文件 《码流甜点区域》<br>
 * 例如 "120 3 750 4 950 6 1200 9 1600" <br>
 * 第一层 分辨率 宽640（120*3/9*16）高 360（120*3）； 码率750kbps <br>
 * 第二层 分辨率 宽848（120*4/9*16）高 480（120*4）； 码率950kbps <br>
 * 第三层 分辨率 宽1280（120*6/9*16）高 720（120*6）； 码率1200kbps <br>
 * 第四层 分辨率 宽1920（120*9/9*16）高 1080（120*9）； 码率1600kbps <br>
 * - 2、作用 <br>
 * 自定义分层参数和码率
 * - 3、其他说明 <br>
 * 二层或多层配置参数一致 <br>
 * 1）无意义，会增编码损耗。 <br>
 * 2）不会节约码率，码率取决于设置订阅层的码率；想减少流量，降低分层分配的码率 <br>
 * 如 "120 3 750 3 750 6 1200 9 1600" 第一层和第二层一样 <br>
 * 当第一层和第二层都被订阅，实际第一层和第二层都在编码，没必要；可改成 "120 3 750 6 1200 9 1600"，都订阅一层 <br>
 * 以上情况设置成 "120 3 750 6 1200 9 1600" 会比 "120 3 750 3 750 6 1200 9 1600" ，节约上行码率和减少编码损毁。
 */
@property (nonatomic, strong) NSString* __nullable customVideoResolution;
/**
 * 会议画面比例，传入值为宽高比浮点数，默认为 16:9
 */
@property (nonatomic) float videoRatio;
/**
 * 会议初始码率
 *
 * 单位 kbps，默认值为 0，如果为 0，内部会根据探测情况计算得出的码率值进行自动设置
 */
@property (nonatomic) int defaultBitrate;

@end

/**
 * 属性变化标识类
 */
@interface JCMediaChannelPropChangeParam : NSObject

/**
 * 上传声音是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool uploadLocalAudio;

/**
 * 上传视频是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool uploadLocalVideo;

/**
 * 输出声音是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool audioOutput;

/**
 * CDN状态是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool cdnState;

/**
 * 录制状态是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool recordState;

/**
 * 屏幕分享是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool screenShare;

/**
 * 标题是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool title;

/**
 * 自定义属性是否变化
 * - true: 变化
 * - false: 没变化
 */
@property (nonatomic) bool customProperty;

@end

/**
 * 屏幕分享参数类，作为 {@link JCMediaChannel#enableScreenShare: enableScreenShare} 方法最后一个参数
 */
@interface JCMediaChannelScreenShareParam : NSObject

/**
 * 屏幕分享码率
 *
 * 单位为 kbps，默认值 0 表示使用媒体引擎的默认值
 */
@property (nonatomic) int bitrate;
/**
 * 屏幕分享帧率
 *
 * 默认值 0 表示使用媒体引擎的默认值
 */
@property (nonatomic) int frameRate;
/**
 * 屏幕分享分辨率
 *
 * 默认值 0 表示使用媒体引擎的默认值<br/>
 * 这里的屏幕分辨率为宽高的乘积，会议屏幕共享时，媒体内部调用了采集宽高比不受编码宽高比影响的接口，所以编码宽高比和采集宽高比会基本保持一致。编码宽*高 >= 采集宽*高时，以采集宽*高编码；编码宽*高 < 采集宽*高时，编码宽高根据采集宽高计算出合适的编码宽高发送。如采集640*640，编码640*360=230400，编码根据230400和比例1:1计算出编码宽高480*480（乘积为230400）
 *
 */
@property (nonatomic) int resolution;

@end

/**
 * 多方通话模块，类似音视频房间的概念，可以通过频道号 @ref channelId 加入频道进行音视频通话
 */
@interface JCMediaChannel : NSObject

/**
 * 频道 Uri
 */
@property (nonatomic, readonly, copy) NSString* __nullable channelUri;

/**
 * 频道标识
 */
@property (nonatomic, readonly, copy) NSString* __nullable channelId;

/**
 * 频道号
 */
@property (nonatomic, readonly) int channelNumber;

/// @cond Doxygen_All
/**
 * 频道在服务器的序号
 */
@property (nonatomic, readonly) long confId;
/// @endcond

/**
 * 获取服务器唯一频道ID
 */
@property (nonatomic, readonly, copy) NSString* __nullable sessionId;

/**
 * 频道密码
 */
@property (nonatomic, readonly) NSString* __nonnull password;

/**
 * 自己当前在频道中的状态
 *
 * 当前在频道中的状态，参见：
 * - @ref JCMediaChannelStateIdle : 空闲状态
 * - @ref JCMediaChannelStateJoining : 加入中
 * - @ref JCMediaChannelStateJoined : 已加入
 * - @ref JCMediaChannelStateLeaving : 离开中
 */
@property (nonatomic, readonly) JCMediaChannelState state;

/**
 * 获得频道中的所有成员
 */
@property (nonatomic, readonly, strong) NSArray* __nonnull participants;

/**
 * 是否上传本地音频数据
 * - true: 上传中
 * - false: 未上传
 */
@property (nonatomic, readonly) bool uploadLocalAudio;

/**
 * 是否上传本地视频数据
 * - true: 上传中
 * - false: 未上传
 */
@property (nonatomic, readonly) bool uploadLocalVideo;

/**
 * 是否音频输出
 *
 * 本地没有音频输出的话，就听不到频道内其他成员的声音了
 *
 * - true: 输出中
 * - false: 未输出
 */
@property (nonatomic, readonly) bool audioOutput;

/**
 * 屏幕共享渲染标识
 *
 * 没有屏幕共享则为 nil
 */
@property (nonatomic, readonly, copy) NSString* __nullable screenRenderId;

/**
 * 屏幕共享用户标识
 *
 * 没有屏幕共享则为 nil
 */
@property (nonatomic, readonly, copy) NSString* __nullable screenUserId;

/**
 * 频道标题
 */
@property (nonatomic, readonly, copy) NSString* __nullable title;

/**
 * 获得视频录制状态，参见：
 * - @ref JCMediaChannelRecordStateNone : 无法进行视频录制。用户不在频道中或者加入频道时没有设置视频录制参数
 * - @ref JCMediaChannelRecordStateReady : 可以开启视频录制。用户在加入频道时设置了录制参数，并且没有在录制视频
 * - @ref JCMediaChannelRecordStateRunning : 视频录制中。用户在加入频道时设置了录制参数，并且正在视频录制中
 */
@property (nonatomic, readonly) JCMediaChannelRecordState recordState;

/**
 * 获得cdn推流状态
 * - @ref JCMediaChannelCdnStateNone : 无法进行Cdn推流。用户不在频道中或者加入频道时没有设置cdn推流参数
 * - @ref JCMediaChannelCdnStateReady : 可以开启Cdn推流。用户在加入频道时设置了cdn推流参数，并且没有在推流
 * - @ref JCMediaChannelCdnStateRunning : Cdn推流中。用户在加入频道时设置了cdn推流参数，并且正在cdn推流中
 */
@property (nonatomic, readonly) JCMediaChannelCdnState cdnState;

/**
 * 自身 JCMediaChannelParticipant 对象
 */
@property (nonatomic, readonly) JCMediaChannelParticipant* __nullable selfParticipant;

/**
 * 是否通知成员音量变化，默认不通知
 * - true: 通知
 * - false: 不通知
 */
@property (nonatomic) bool volumeChangeNotify;

/**
 * 获得频道最大分辨率
 *
 * 频道中的最大分辩由第一个加入频道的用户决定， JoinParam 参数中设置的分辩率并一定是频道的最大分辨率，只有加入成功后才能准确知道
 *
 * @note
 * 该接口需要在加入成功后调用才有意义
 *
 * 最大分辨率枚举值如下：
 * - @ref JCMediaChannelMaxResolution "JCMediaChannelMaxResolution360" : 最大分辨率 360p
 * - @ref JCMediaChannelMaxResolution "JCMediaChannelMaxResolution720" : 最大分辨率 720p
 * - @ref JCMediaChannelMaxResolution "JCMediaChannelMaxResolution1080" : 最大分辨率 1080p
 */
@property (nonatomic, readonly) JCMediaChannelMaxResolution maxResolution;

/**
 * 创建 JCMediaChannel 对象
 *
 * JCMediaChannel 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 调用此方法创建 JCMediaChannel 对象后，期间没有调用过 {@link destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCMediaChannel 对象
 * - 调用此方法前确保 JCClient 已完成初始化，即 @ref JCClient#state "state" 方法获取的状态值不等于 @ref JCClientStateNotInit
 *
 *
 * @param client      JCClient 对象
 * @param mediaDevice JCMediaDevice 对象
 * @param callback    JCMediaChannelCallback 对象，用于回调相关通知
 * @return JCMediaChannel 对象
 * @exception "JCClient、JCMediaDevice、JCMediaChannelCallback 任意一个参数传空就会出现调用失败"
 */
+(JCMediaChannel* __nullable)create:(JCClient* __nonnull)client mediaDevice:(JCMediaDevice* __nonnull)mediaDevice callback:(id<JCMediaChannelCallback> __nonnull)callback;

/**
 * 销毁 JCMediaChannel 对象
 *
 * 该方法为同步调用，需要等待 JCMediaChannel 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCMediaChannel 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCMediaChannel 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCMediaChannel 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 查询频道相关信息
 *
 * 在登录后调用此接口可以查询频道相关信息，例如频道是否存在，频道人数等，结果通过 {@link JCMediaChannelCallback#onQuery:result:reason:queryInfo: onQuery} 通知
 *
 * @param channelId 频道标识
 * @return 操作id，与  {@link JCMediaChannelCallback#onQuery:result:reason:queryInfo: onQuery} 回调中的 operationId 对应
 */
-(int)query:(NSString* __nonnull)channelId;

/**
 * 加入频道
 *
 * 该方法让用户加入通话频道，在同一个频道内的用户可以互相通话 <br>
 * 如果已在频道中，用户必须退出当前频道，即处于空闲状态，才能进入下一个频道，否则将直接返回 false <br>
 *
 * @param channelId    多方通话标识
 * @param joinParam      JCMediaChannelJoinParam 对象，没有则填 nil
 * @return 调用是否正常
 * - true: 正常执行调用流程
 * - false: 调用失败
 *  - 在调用此方法时，用户的频道状态不是空闲状态，则不会收到回调通知
 *  - 在调用此方法时，用户的频道是空闲状态，则会收到 {@link JCMediaChannelCallback#onJoin:reason:channelId: onJoin} 方法通知
 */
-(bool)join:(NSString* __nonnull)channelId joinParam:(JCMediaChannelJoinParam* __nullable)joinParam;

/**
 * 离开频道
 *
 * 当前只支持同时加入一个频道，结果通过 {@link JCMediaChannelCallback#onLeave:channelId: onLeave} 通知
 *
 * @return 调用是否正常
 * - true: 正常执行调用流程
 * - false: 调用失败
 */
-(bool)leave;

/**
 * 关闭频道
 *
 * 此频道内的成员都将被强制退出
 *
 * @return 调用是否正常
 * - true: 正常执行调用流程
 *  - 在调用此方法时，用户的频道状态是空闲状态，不会收到回调通知
 *  - 在调用此方法时，用户的频道状态不是空闲状态，则会收到 {@link JCMediaChannelCallback#onStop:reason: onStop}  通知
 * - false: 调用失败
 */
-(bool)stop;

/**
 * 开启/关闭发送本地音频流
 *
 * 调用该方法可开启或关闭发送本地音频流。开启后，频道成员将听见本端声音；关闭后，频道成员将听不见本端声音  <br>
 * 初始化 JCMediaChannel 时，默认不发送本地音频流。若要加入频道时，让频道内其他成员听见本端声音，需要在调用   {@link join:joinParam: join} 加入频道前设置 <br>
 * 该方法在频道内和频道外均可调用，且在离开频道后该设置仍然有效。也就是说这一次设置了开启发送本地音频流，那么在下一次加入频道时默认会开启发送本地音频流 <br>
 * 会议中也可调用此方法开启或关闭发送本地音频流，服务器会更新状态并同步给其他频道成员 <br>
 * 会议中调用此方法不影响接收远端音频
 *
 * @param enable 开启/关闭发送本地音频流
 * - true: 开启，即发送本地音频流
 * - false: 关闭，即不发送本地音频流
 * @return 调用是否正常
 * - true: 正常执行调用流程
 *  - 在调用此方法时，用户不在频道中，则不会收到回调通知
 *  - 在调用此方法时，用户在频道中，则会收到 {@link JCMediaChannelCallback#onMediaChannelPropertyChange: onMediaChannelPropertyChange} 通知
 * - false: 调用失败，不会收到回调通知
 */
-(bool)enableUploadAudioStream:(bool)enable;

/**
 * 开启/关闭发送本地视频流
 *
 * 调用该方法可开启或关闭发送本地视频流。开启后，频道成员将可以看见本端视频画面；关闭后，频道成员将看不见本端视频画面  <br>
 * 初始化 JCMediaChannel 时，默认发送本地视频流。若要加入频道时，让频道内其他成员看见本端视频画面，建议在调用  {@link join:joinParam: join} 加入频道前设置 <br>
 * 该方法在频道内和频道外均可调用，且在离开频道后该设置仍然有效。也就是说这一次设置了关闭发送本地视频流，那么在下一次加入频道时默认会关闭发送本地视频流  <br>
 * 会议中也可调用此方法开启或关闭发送本地视频流，服务器会更新状态并同步给其他频道成员 <br>
 * 会议中调用此方法不影响接收远端视频
 *
 * @param enable 是否发送本地视频流
 * - true: 开启，即发送本地视频流
 * - false: 关闭，即不发送本地视频流
 * @return 调用是否正常
 * - true：正常执行调用流程
 *  - 在调用此方法时，用户不在频道中，则不会收到回调通知
 *  - 在调用此方法时，用户在频道中，则会收到 {@link JCMediaChannelCallback#onMediaChannelPropertyChange: onMediaChannelPropertyChange} 通知
 * - false：调用失败，不会收到回调通知
 */
-(bool)enableUploadVideoStream:(bool)enable;

/**
 * 开启/关闭远端音频输出
 *
 * 该方法可实现本地静音功能。关闭时听不到频道内其他成员的声音，不影响其他成员；开启时可以听到其他成员声音 <br>
 * 初始化 JCMediaChannel 时，音频输出功能默认是开启的。若要加入频道时听不见其他成员的声音，建议在调用  {@link join:joinParam: join} 加入频道前设置 <br>
 * 该方法可以关闭或重新开启音频输出功能，在频道内和频道外均可调用，且在离开频道后该设置仍然有效，也就是说这一次设置了关闭音频输出，那么下一次加入频道时也是默认关闭音频输出
 *
 * @param enable 是否开启音频输出
 * - true: 开启
 * - false: 关闭
 * @return 调用是否正常
 * - true：正常执行调用流程
 *  - 在调用此方法时，用户的频道状态不是已加入状态，则不会收到回调通知
 *  - 在调用此方法时，用户的频道状态是已加入状态，则会收到 {@link JCMediaChannelCallback#onMediaChannelPropertyChange: onMediaChannelPropertyChange} 通知
 * - false：调用失败，不会收到回调通知
 */
-(bool)enableAudioOutput:(bool)enable;

/**
 * 请求频道中其他用户的视频流
 *
 * 当 pictureSize 为 @ref JCMediaChannelPictureSizeNone 时表示关闭请求
 *
 * @param participant   JCMediaChannelParticipant 频道中其他成员对象
 * @param pictureSize   视频请求的尺寸类型：
 * - @ref JCMediaChannelPictureSizeNone : 不渲染
 * - @ref JCMediaChannelPictureSizeMin : 最小尺寸
 * - @ref JCMediaChannelPictureSizeSmall : 小尺寸
 * - @ref JCMediaChannelPictureSizeLarge : 大尺寸
 * - @ref JCMediaChannelPictureSizeMax : 最大尺寸
 * @return 调用是否正常
 * - true：正常执行调用流程，会收到 {@link JCMediaChannelCallback#onParticipantUpdate:participantChangeParam: onParticipantUpdate} 通知
 * - false：调用失败，不会收到回调通知
 */
-(bool)requestVideo:(JCMediaChannelParticipant* __nonnull)participant pictureSize:(JCMediaChannelPictureSize)pictureSize;

/**
 * 开启/关闭屏幕分享
 *
 * 在频道中时调用此方法才有效
 *
 * @param enable 开启/关闭屏幕分享
 * - true: 开启屏幕分享
 * - false: 关闭屏幕分享
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)enableScreenShare:(bool)enable screenShareParam:(JCMediaChannelScreenShareParam * __nullable)screenShareParam;

/**
 * 请求频道成员屏幕共享的视频流
 *
 * 当 pictureSize 为 @ref JCMediaChannelPictureSizeNone 表示关闭请求
 *
 * @param screenUri     屏幕分享uri
 * @param pictureSize   视频请求尺寸类型，参见：
 * - @ref JCMediaChannelPictureSizeNone : 不渲染
 * - @ref JCMediaChannelPictureSizeMin : 最小尺寸
 * - @ref JCMediaChannelPictureSizeSmall : 小尺寸
 * - @ref JCMediaChannelPictureSizeLarge : 大尺寸
 * - @ref JCMediaChannelPictureSizeMax : 最大尺寸
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)requestScreenVideo:(NSString* __nonnull)screenUri pictureSize:(JCMediaChannelPictureSize)pictureSize;

/**
 * 开启/关闭Cdn推流
 *
 * 在收到 {@link JCMediaChannelCallback#onMediaChannelPropertyChange: onMediaChannelPropertyChange} 回调后检查是否开启
 *
 * @param enable 开启/关闭Cdn推流
 * - true: 开启 Cdn 推流
 * - false: 关闭 Cdn 推流
 * @param keyInterval 推流关键帧间隔(毫秒)，当参数 enable 为 true 时有效，有效值需要>=1000
 * @return 调用是否正常
 * - true：正常执行调用流程，会收到 {@link JCMediaChannelCallback#onMediaChannelPropertyChange: onMediaChannelPropertyChange}  通知
 * - false：调用失败，不会收到通知回调
 */
-(bool)enableCdn:(bool)enable keyInterval:(int)keyInterval;

/**
 * 开启/关闭视频录制
 *
 * @param enable   开启/关闭视频录制
 * - true: 开启视频录制
 * - false: 关闭视频录制
 * @param recordParam JCMediaChannelRecordParam 录制参数对象，当参数 enable 为 true 时，可以更改由  {@link join:joinParam: join}  时传入的录制参数，不需更改则填 nil
 * @return 调用是否正常
 * - true：正常执行调用流程，会收到 {@link JCMediaChannelCallback#onMediaChannelPropertyChange: onMediaChannelPropertyChange}  通知
 * - false：调用失败，不会收到通知回调
 */
-(bool)enableRecord:(bool)enable recordParam:(JCMediaChannelRecordParam* __nullable)recordParam;

/**
 * 根据用户标识获取频道成员
 *
 * @param userId 用户唯一标识
 * @return
 * - 频道内无此用户标识的用户: nil
 * - 频道内有此用户标识的用户: JCMediaChannelParticipant 对象
 */-(JCMediaChannelParticipant* __nullable)getParticipant:(NSString* __nonnull)userId;

/**
 * 获取统计信息
 *
 * 以Json字符串形式返回，其中包含 "Config"， "Network"，"Transport" 和 "Participants" 4个节点
 *
 * @return 统计信息
 */
-(NSString * __nullable)getStatistics;

/**
 * 设置频道自定义属性
 *
 * 调用此接口来设置频道自定义属性
 *
 * @param property   自定义属性
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)setCustomProperty:(NSString * __nonnull)property;

/**
 * 获取自定义频道属性
 *
 * 调用此接口来获取频道自定义属性
 *
 * @return 自定义属性
 */
-(NSString * __nullable)getCustomProperty;

/**
 * 发送消息
 *
 * 此接口调用成功后，消息接收方会收到 @ref JCMediaChannelCallback.onMessageReceive "onMessageReceive" 回调，通过此回调可以获取消息的文本类型和文本内容
 *
 * @note 当参数content大于4K时消息的发送不可靠，为确保消息发送的可靠性可以对消息内容进行压缩。
 *
 * @param type 消息类型
 * @param content 消息内容，content不能为空，content不能大于 4k
 * @param toUserId 接收者id，null则发给频道所有人员
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)sendMessage:(NSString * __nonnull)type content:(NSString * __nonnull)content toUserId:(NSString * __nullable)toUserId;

/**
 * 邀请Sip用户
 *
 * 一般用于对接落地网关等，结果通过 {@link JCMediaChannelCallback#onInviteSipUserResult:result:reason: onInviteSipUserResult} 通知
 *
 * @param userId    一般为号码
 * @param sipParam  JCMediaChannelSipParam 参数对象
 * @return 调用是否正常
 * - > 0：操作id，结果通过 {@link JCMediaChannelCallback#onInviteSipUserResult:result:reason: onInviteSipUserResult} 通知
 * - -1：失败，不会收到回调通知
 */
-(int)inviteSipUser:(NSString * __nonnull)userId sipParam:(JCMediaChannelSipParam* __nonnull)sipParam;

/**
 * 发送指令<br>
 *
 * - 指令名: StartForward    指令作用：请求服务器开始转发音视频<br>
 * 参数格式:{"MtcConfUserUriKey": "用户Uri", "MtcConfMediaOptionKey": "类型"}<br>
 * 用户Uri: 通过调用底层Mtc接口获取 MtcUser.Mtc_UserFormUri(EN_MTC_USER_ID_USERNAME, userId)<br>
 * 类型:  服务器转发分三种 音频、视频、音视频，具体可参考底层mtc_conf.h下的MtcConfMedia的枚举值。<br>
 * 注意1:指令发送成功后会收到 {@link JCMediaChannelCallback#onParticipantUpdate:participantChangeParam: onParticipantUpdate} 回调 <br>
 * 举例: {"MtcConfUserUriKey": "[username:justin@sample.cloud.justalk.com]", "MtcConfMediaOptionKey": 3}<br><br>
 * - 指令名: StopForward    指令作用：请求服务器停止转发音视频<br>
 * 参数格式:{"MtcConfUserUriKey": "用户URL", "MtcConfMediaOptionKey": "类型"}<br>
 * 用户Uri: 通过调用底层Mtc接口获取 MtcUser.Mtc_UserFormUri(EN_MTC_USER_ID_USERNAME, userId)<br>
 * 类型:  服务器转发分三种 音频、视频、音视频，具体可参考底层mtc_conf.h下的MtcConfMedia的枚举值。<br>
 * 注意1:指令发送成功后会收到 {@link JCMediaChannelCallback#onParticipantUpdate:participantChangeParam: onParticipantUpdate} 回调 <br>
 * 举例: {"MtcConfUserUriKey": "[username:justin@sample.cloud.justalk.com]", "MtcConfMediaOptionKey": 3}<br><br>
 * - 指令名: ChangeTitle    指令作用：请求修改会议主题<br>
 * 参数格式: {"MtcConfTitleKey":"修改的内容"}<br>
 * 修改的内容: 比如原来主题设置的是"123"，现在改为"321"。<br>
 * 注意1:指令发送成功后会收到 {@link JCMediaChannelCallback#onMediaChannelStateChange:oldState: onMediaChannelPropertyChange} 回调<br>
 * 注意2:可通过 JCManager.shared.mediaChannel.title 获取主题<br>
 * 举例:{"MtcConfTitleKey": "321"}<br><br>
 * - 指令名: SetPartpProp     指令作用：批量修改成员状态，角色，昵称。<br>
 * 参数格式: {"MtcConfStateKey":1,"MtcConfDisplayNameKey":"1314","MtcConfPartpLstKey":["[username:10086@sample.cloud.justalk.com]"],"MtcConfRoleKey":7}<br>
 * 要修改的成员状态: 具体可参考底层 mtc_conf.h 下的 MtcConfState 的枚举值<br>
 * 要修改的成员角色: 具体可参考底层 mtc_conf.h 下的 MtcConfRole 的枚举值<br>
 * 要修改的成员昵称: 比如"123"<br>
 * 用户Uri:通过调用底层Mtc接口获取 MtcUser.Mtc_UserFormUri(EN_MTC_USER_ID_USERNAME, userId); <br>
 * 注意1:指令发送成功后会收到 {@link JCMediaChannelCallback#onParticipantUpdate:participantChangeParam: onParticipantUpdate}  回调 <br>
 * 注意2:MtcConfStateKey、MtcConfDisplayNameKey、MtcConfRoleKey这三个字段，可根据用户想修改哪个值，就在json字符串里面加入哪个。<br>
 * 注意3:MtcConfPartpLstKey 可包含多个用户uri进行批量修改<br>
 * 举例:{"MtcConfStateKey":4,"MtcConfDisplayNameKey":"123","MtcConfPartpLstKey":{"MtcConfUserUriKey":"[username:10086@sample.cloud.justalk.com]","MtcConfStateKey":4},"MtcConfRoleKey":4}<br><br>
 * - 指令名：ReplayApplyMode 指令作用：设置推流布局模式<br>
 * 指令参数格式：{"MtcConfCompositeModeKey": 参数值}<br>
 * 参数值：<br>
 * 1 平铺模式,所有视频均分平铺<br>
 * 2 讲台模式,共享为大图,其他视频为小图<br>
 * 3 演讲模式,共享为大图,共享者视频为小图,其他不显示<br>
 * 4 自定义模式,由ReplayApplyLayout指令设置所有视频布局<br>
 * 5 智能模式。<br>
 * 举例：输入指令参数{"MtcConfCompositeModeKey": 2}就是讲台模式<br><br>
 * - 指令名：ReplayApplyLayout 指令作用：为多用户设置自定义推流布局<br>
 * 指令参数格式：{[{"MtcConfUserUriKey": "用户uri", "MtcConfPictureSizeKey": 视频尺寸,"MtcConfRectangleKey": 图像矩形的具体方位和长宽}]，...}<br>
 * 用户uri：通过调用底层Mtc接口获取MtcUser.Mtc_UserFormUri((uint)EN_MTC_USER_ID_TYPE.EN_MTC_USER_ID_USERNAME，userId)<br>
 * 视频尺寸：一共5个枚举值，具体枚举值请参考底层mtc_conf.h下的MtcConfPs枚举<br>
 * 图像矩形的具体方位和长宽：这是一个Json格式的Array对象表示这个图像的位置和大小，第一个值是图像左上角的x坐标(0~1)<br>
 * 第二个值是图像左上角的y坐标(0~1)。第三个值是图像的宽(0~1)。第四个值是图像的高(0~1)。比如[0.5,0.5,0.5,0.5]表示图像在右下角长宽是原始屏幕的一半<br>
 * 举例：<br>
 * [{"MtcConfUserUriKey":"[username:zhang@xxxx.cloud.justalk.com]","MtcConfPictureSizeKey":512,"MtcConfRectangleKey":[0.5,0.5,0.5,0.5]}]<br>
 * 表示成员zhang小尺寸的视频在屏幕右下角位置，长宽是原始屏幕的一半<br>
 *
 * @param name  指令名
 * @param param 指令参数
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)sendCommand:(NSString * __nonnull)name commandParam:(NSString * __nonnull)param;

/**
 * 设置自定义角色
 *
 * @param customRole @ref JCMediaChannelCustomRole "自定义角色"
 * @param participant JCMediaChannelParticipant 对象，频道中的成员，nil 则默认设置自己
 */
-(void)setCustomRole:(JCMediaChannelCustomRole)customRole participant:(JCMediaChannelParticipant * __nullable)participant;

/**
 * 获得自定义角色
 *
 * @return @ref JCMediaChannelCustomRole "自定义角色"
 */
-(JCMediaChannelCustomRole)getCustomRole;

/**
 * 设置自定义状态
 *
 * @param customState @ref JCMediaChannelCustomState "自定义状态"
 * @param participant JCMediaChannelParticipant 对象，频道中的成员，nil 则默认设置自己
 */
-(void)setCustomState:(JCMediaChannelCustomState)customState participant:(JCMediaChannelParticipant * __nullable)participant;

/**
 * 获得自定义状态
 *
 * @return @ref JCMediaChannelCustomState "自定义状态"
 */
-(JCMediaChannelCustomState)getCustomState;

/**
 * 将成员踢出频道
 *
 * @param participant 成员
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(BOOL)kick:(JCMediaChannelParticipant * __nonnull)participant;

/**
 * 发送命令给推流或录制器
 *
 * 发送命令给推流时，只有加入成功并且推流状态为 @ref JCMediaChannelCdnStateReady 才生效 <br>
 * 发送命令给录制器时，只有加入成功并且录制状态为 @ref JCMediaChannelRecordStateReady 才生效
 *
 * @param command 命令字符串
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)sendCommandToDelivery:(NSString* __nonnull)command;

/**
 * 设置自身视频宽高比
 *
 * @note 必须加入频道后设置才能生效
 *
 * @param enable 是否开启自身视频宽高比
 * - true: 开启
 * - false: 关闭
 * @param ratio 视频宽高比
 */
-(void)enableSelfVideoRatio:(bool)enable ratio:(float)ratio;

/**
 * 启动频道成员的屏幕分享视频渲染
 *
 * 频道成员开启屏幕分享时，调用此方法可获得屏幕分享视频 @ref JCMediaDeviceVideoCanvas "渲染对象"
 *
 * @param type 渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @param pictureSize 视频请求的尺寸类型：
 * - @ref JCMediaChannelPictureSizeNone : 不渲染
 * - @ref JCMediaChannelPictureSizeMin : 最小尺寸
 * - @ref JCMediaChannelPictureSizeSmall : 小尺寸
 * - @ref JCMediaChannelPictureSizeLarge : 大尺寸
 * - @ref JCMediaChannelPictureSizeMax : 最大尺寸
 * @return JCMediaDeviceVideoCanvas 渲染对象
 */
-(JCMediaDeviceVideoCanvas* __nullable)startScreenShareVideo:(JCMediaDeviceRender)type pictureSize:(JCMediaChannelPictureSize)pictureSize;

/**
 * 停止屏幕分享视频渲染
 *
 * 调用 {@link JCMediaChannel#startScreenShareVideo:pictureSize: startScreenShareVideo} 启动屏幕分享视频渲染后，调用此方法可停止
 */
-(void)stopScreenShareVideo;

/**
 * 订阅或取消订阅指定用户的声音
 *
 * @note 该接口需要在自己加入会议成功后才能调用
 *
 * @param participant    JCMediaChannelParticipant 对象，频道中的成员对象
 * @param subscribe 是否订阅
 * - true：订阅
 * - false：取消订阅
 * @return 调用是否正常
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)subscribeParticipantAudio:(JCMediaChannelParticipant *__nonnull)participant subscribe:(bool)subscribe;

@end

/**
 * @}
 */
