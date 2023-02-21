//
//  JCCall.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCCallCallback.h"
#import "JCCallItem.h"

/**
 * @defgroup 一对一通话模块
 * @{
 * 用于管理一对一通话
 */

/**
 *通话参数，作为 {@link JCCall#call:video:callParam: call} 方法最后一个参数的入参
 */
@interface JCCallParam : NSObject
/**
 * 透传参数
 *
 * 主叫方可以设置该参数，通过调用 {@link JCCall#call:video:callParam: call} 方法可传给被叫方 <br>
 * 设置后被叫方可获取该参数，通过 JCCallItem 的 @ref JCCallItem#extraParam "extraParam" 属性获取
 */
@property (nonatomic) NSString * __nullable extraParam;
/**
 * 与小系统通话使用，服务端需要的凭证，用于标识通话唯一性，此参数只有在 @ref JCCallMediaConfigModeIOT 模式生效
 *
 * 主叫方可以设置该参数，通过调用 {@link JCCall#call:video:callParam: call} 方法可传给被叫方 <br>
 * 设置后被叫方可获取该参数，通过 JCCallItem 的 @ref JCCallItem#ticket "ticket" 属性获取
 */
@property (nonatomic) NSString * __nullable ticket;
/**
 * 构造方法
 *
 * @param extraParam 透传参数，设置后被叫方可获取该参数
 * @param ticket     与小系统通话使用，服务端需要的凭证，用于标识通话唯一性，此参数只有在 @ref JCCallMediaConfigModeIOT 模式生效
 */
+ (instancetype __nullable )callParamWithExtraParam:(NSString *__nullable)extraParam ticket:(NSString *__nullable)ticket;

@end

/**
 * 一对一通话媒体参数配置类，在调用{@link call:video:callParam: call} 方法之前，设置 @ref JCCall#mediaConfig "mediaConfig" 属性
 */
@interface JCCallMediaConfig : NSObject

/**
 * 音频编解码
 *
 * 协商优先级按顺序排列, 每个编解码用";"间隔, 注意大小写， 默认值为 "opus;AMR;G729"
 */
@property (nonatomic, strong) NSString* __nonnull audioEnableCodecs;
/**
 * 回声消除模式，默认为 @ref JCCallAecModeSDE ，参见：
 * - @ref JCCallAecModeAEC : 声学回声消除
 * - @ref JCCallAecModeOS : 使用操作系统提供的声学回声消除功能
 * - @ref JCCallAecModeAES : 声学回声抑制
 * - @ref JCCallAecModeFDE : 软件自适应声学回声消除，能适应更大延时
 * - @ref JCCallAecModeSDE : 软件自适应声学回声消除，追踪延迟精度高
 */
@property (nonatomic) JCCallAecMode audioAecMode;
/**
 * 是否开启音频，默认开启
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool audioArsEnable;
/**
 * 音频最小码率，默认值为 20 kb
 */
@property (nonatomic) int audioArsBitrateMin;
/**
 * 音频最大码率，默认值为 75 kb
 */
@property (nonatomic) int audioArsBitrateMax;
/**
 * 是否打开语音red抗丢包，默认开启
 *
 * @note 网络不稳定，一般选择打开
 *
 * - true: 打开，能够增加payload码率
 * - false: 关闭，能力节省码率从而降低功耗
 */
@property (nonatomic) bool audioRed;
/**
 * 是否开启噪声抑制，默认关闭
 *
 * @note 一般接收端声音质量好可关闭噪声抑制, 减少声音dsp处理, 降低功耗
 *
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool audioRxAnr;
/**
 * 是否开启rtx重传，默认关闭
 *
 * @note
 * - 同FEC、NACK一起用, 能够降低功耗
 * - 网络不稳定, 一般选择打开
 * <p>
 * - true: 打开
 * - false: 关闭
 */
@property (nonatomic) bool audioRtx;
/**
 * 是否打开接收端声音自动增益控制，默认关闭
 *
 * @note 接收端声音过大过小时, 可尝试打开
 *
 * - true: 打开
 * - false: 关闭
 */
@property (nonatomic) bool audioRxAgc;
/**
 * 是否开启回声消除，默认开启
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool audioQosAec;
/**
 * 是否开启发送端噪声抑制，默认开启
 *
 * @note
 * - 接收端声音噪声大，提高抑制等级
 * - 接收端声音小，可在不影响声音质量情况下降低抑制等级或者关闭抑制
 *
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool audioQosAnr;
/**
 * 是否开启发送端声音自动增益控制，默认开启
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool audioQosAgc;
/**
 * 是否开启静音检测，默认关闭
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool audioQosVad;
/**
 * 音频打包时长，默认值为 20
 */
@property (nonatomic) int audioPacketTime;
/**
 * 发送端声音自动增益控制强度，默认值为9
 *
 * 取值范围为[0,90]，数值越大，增益强度越大。当 @ref JCCallMediaConfig.audioQosAgc "audioQosAgc" 为 true 时有效
 */
@property (nonatomic) int audioQosAgcGain;

/**
 * 视频编解码，协商优先级按顺序排列，默认值为 "H264-SVC;H264;VP8"
 */
@property (nonatomic, strong) NSString* __nonnull videoEnableCodecs;
/**
 * 视频接收宽，默认值值为 640
 */
@property (nonatomic) int videoResolutionRecvWidth;
/**
 * 视频接收高，默认值为 360
 */
@property (nonatomic) int videoResolutionRecvHeight;
/**
 * 视频发送宽，默认值为 640
 */
@property (nonatomic) int videoResolutionSendWidth;
/**
 * 视频发送高，默认值为 360
 */
@property (nonatomic) int videoResolutionSendHeight;
/**
 * 视频初始码率，默认值为 800 kb
 */
@property (nonatomic) int videoBitrate;
/**
 * 发送帧率，默认值为 24
 */
@property (nonatomic) int videoSendFramerate;
/**
 * 是否开启视频 ars，默认开启
 * - true： 开启
 * - false: 关闭
 */
@property (nonatomic) bool videoArsEnable;
/**
 * 视频最小码率，默认值为 50 kb
 */
@property (nonatomic) int videoArsBitrateMin;
/**
 * 视频最大码率，默认值为 1500 kb
 */
@property (nonatomic) int videoArsBitrateMax;
/**
 * 视频最小帧率，默认值为 1 kb
 */
@property (nonatomic) int videoArsFramerateMin;
/**
 * 视频最大帧率，默认值为 30 kb
 */
@property (nonatomic) int videoArsFramerateMax;
/**
 * 是否开启rfc 2198 语音fec-red，默认开启
 *
 * @note 开启后可以增强抗丢包能力，会增加一倍的payload码率，不会增加包头。比如Opus 55kbps增加一倍码率后，最终码率达到90kbps=55+35；Opus 10kbps增加一倍码率后，最终码率达到16kbps=10+6
 *
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool videoRedFec;

/**
 * 本端视频分辨率是否影响请求分辨率，默认影响
 *
 * 这里举个例子，有假设条件：
 * 1. 本端默认请求是640*360的分辨率
 * 2. 本端屏幕分辨率为360*360
 * - 若此参数设置成 true：请求分辨率 360*360
 * - 若此参数设置成 false: 请求分辨率 640*360
 * <p>
 * - true: 影响
 * - false: 不影响
 */
@property (nonatomic) bool videoRecvFullScreen;
/**
 * 是否开启视频数据以 SmallNalu 方式打包，默认开启
 *
 * 开启后一个包打包的数据多，减少包头的码率，从而降低功耗
 *
 * - true: 开启
 * - false: 关闭
 */
@property (nonatomic) bool videoSmallNalu;
/**
 * 是否开启分辨率控制，默认开启
 * - true: 开启, 分辨率随网络波动而变化
 * - false: 关闭, 固定分辨率
 */
@property (nonatomic) bool videoResolutionControl;

/**
 * 视频关键帧间隔（毫秒），@ref JCCallMediaConfigMode "JCCallMediaConfigModeIOT" 模式下默认为 5000
 *
 * 仅在 @ref JCCallMediaConfigMode "JCCallMediaConfigModeIOT" 模式下生效，其他模式下设置无效
 */
@property (nonatomic) int videoKeyPeriod;

/**
 * 心跳间隔，默认心跳间隔为30秒
 *
 * 取值范围为(0,3600)。比如本端设置了心跳间隔为 X 秒，那么对端在 3*X 秒内都没有收到本端的心跳时，对端将收到 {@link JCCallCallback.onCallItemRemove:reason:description:  onCallItemRemove} 通话结束的回调
 */
@property (nonatomic) int heartbeatTime;

/**
 * 字符串信息
 * @return 返回 JCCall 实例信息
 */
-(NSString* __nonnull)toString;

/**
 * 根据模式生成配置参数
 *
 * 可通过此方法生成 JCCallMediaConfig 对象，然后在调用 {@link JCCall#call:video:callParam: call} 方法前，将 JCCallMediaConfig 对象赋值给 @ref JCCall#mediaConfig "mediaConfig" 属性
 *
 * @param mode  通话媒体配置模式，参见：
 * - @ref JCCallMediaConfigMode360P : 360P
 * - @ref JCCallMediaConfigMode720P : 720P
 * - @ref JCCallMediaConfigModeIntelligentHardware : 智能硬件场景，比如会和手表通话等
 * - @ref JCCallMediaConfigModeIOT : 与asr，展讯等小系统互通
 * @return JCCallMediaConfig 通话媒体配置对象
 */
+(JCCallMediaConfig* __nonnull)generateByMode:(JCCallMediaConfigMode)mode;

@end

/**
 * 一对一通话类
 *
 * 该类的所有实例方法在调用时需保证用户的登录状态为已登录
 */
@interface JCCall : NSObject

/**
 * 获得通话对象列表
 *
 * 当 @ref maxCallNum > 1 时，callItems 通话对象列表中可能存在多个音频通话
 */
@property (nonatomic, readonly, strong) NSArray* __nullable callItems;

/**
 * 最大通话数，默认值为1
 *
 * @note 当通话数到达最大通话数后，调用 {@link call:video:callParam: call} 接口呼出会失败，收到来电会自动拒绝
 */
@property (nonatomic) int maxCallNum;

/**
 * 当音频接收网络状态为无网络时是否挂断，默认为 false
 *
 * 即  @ref JCCallItem.audioNetReceiveStatus "audioNetReceiveStatus" 状态为 @ref JCCallNetWorkDisconnected 时是否挂断
 *
 * - true: 挂断
 * - false: 不挂断
 */
@property (nonatomic) bool termWhenNetDisconnected;

/**
 * 当前的媒体配置参数
 * @note
 * 该属性在调用 {@link call:video:callParam: call} 方法之前设置才生效<br>
 * JCCallMediaConfig 对象建议通过 {@link JCCallMediaConfig#generateByMode: generateByMode} 方法创建
 */
@property (nonatomic, strong) JCCallMediaConfig* __nonnull mediaConfig;

/**
 * 创建 JCCall 对象
 *
 * JCCall 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 调用此方法创建 JCCall 对象后，期间没有调用过 {@link destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCCall 对象
 * - 调用此方法前确保 JCClient 已完成初始化，即 @ref JCClient.state "state" 状态值不等于 @ref JCClientStateNotInit
 *
 * @param client      JCClient 对象
 * @param mediaDevice JCMediaDevice 对象，通过 {@link JCMediaDevice#create:callback: create} 方法创建
 * @param callback    JCCallCallback 对象，用于回调相关通知
 * @return JCCall 对象
 * @exception "JCClient、JCMediaDevice、JCCallCallback 任意一个参数传空就会创建失败"
 */
+(JCCall* __nullable)create:(JCClient* __nonnull)client mediaDevice:(JCMediaDevice* __nonnull)mediaDevice callback:(id<JCCallCallback> __nonnull)callback;
 
/**
 * 销毁 JCCall 对象
 *
 * 该方法为同步调用，需要等待 JCCall 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCCall 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCCall 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCCall 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 发起一对一呼叫
 *
 * 若发起的是音频呼叫，需要保证本地不存视频通话，并且本地通话数未达到最大通话数，最大通话数为：@ref maxCallNum <br>
 * 若发起的是视频呼叫，需要保证本地不存在通话 <br>
 * 发起呼叫成功后，会收到 {@link JCCallCallback#onCallItemAdd: onCallItemAdd} 通知 <br>
 * 以下两种情况会收到 {@link JCCallCallback#onCallItemRemove:reason:description: onCallItemRemove} 通知：
 * - 本端发起视频呼叫时，对方已存在通话
 * - 本端发起音频呼叫时，对方已存在视频通话
 *
 * @note 在调用此接口时确保用户的登录状态为已登录
 *
 * @param userId            对方的用户标识
 * @param video              是否视频呼叫
 * - true: 视频呼叫
 * - false: 音频呼叫
 * @param callParam     JCCallParam 通话参数对象，此参数可为空。详细定义见: JCCallParam
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)call:(NSString* __nonnull)userId video:(bool)video callParam:(JCCallParam * __nullable)callParam;

/**
 * 挂断
 *
 * 调用接口成功会收到 {@link JCCallCallback#onCallItemRemove:reason:description: onCallItemRemove} 通知
 *
 * @param item                  JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象
 * @param reason              @ref JCCallReason "挂断原因"
 * @param description   挂断描述
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)term:(JCCallItem* __nonnull)item reason:(JCCallReason)reason description:(NSString* __nullable)description;

/**
 * 接听
 *
 * 调用接口成功会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate}  通知<br>
 * 另外还有两种情况也会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知：1、若收到的是视频呼叫，而本端选择了音频接听 2、若此路通话不是活跃的，会将此路通话设为活跃通话。<br>
 * 调用接口失败会收到  {@link  JCCallCallback.onCallItemRemove:reason:description:  onCallItemRemove}  通知
 *
 * @param item  JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象
 * @param video 针对视频呼入可以选择以视频接听还是音频接听
 * - true: 视频接听
 * - false: 音频接听
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)answer:(JCCallItem* __nonnull)item video:(bool)video;

/**
 * 开启/取消音频输入静音
 *
 * @deprecated 从 v2.7.1 废弃。Juphoon 不建议你使用。如果你想开启/取消音频输入静音，请改用 {@link muteMicrophone:mute: muteMicrophone} 方法
 *
 * 调用成功会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知
 *
 * 开启后对端听不到本端的声音，通过 @ref JCCallItem#mute "mute" 来决定开启/取消静音
 * - @ref JCCallItem#mute "mute" 为 true，即静音状态时: 取消静音
 * - @ref JCCallItem#mute "mute" 为 false，即不是静音状态时: 开启静音
 *
 * @param   item JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象，此对象的通话状态必须为通话中
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)mute:(JCCallItem* __nonnull)item;

/**
 * 开启/取消音频输入静音
 *
 * 开启后对端将听不到本端的声音
 * - @ref JCCallItem#microphoneMute "microphoneMute" 为 true，即静音状态时: 取消静音
 * - @ref JCCallItem#microphoneMute "microphoneMute" 为 false，即不是静音状态时: 开启静音
 *
 * @param   item JCCallItem 对象，不能为空，并且本地缓存的通话列表中要包含此对象，此对象的通话状态必须为通话中
 * @param   mute 是否静音
 * @return 是否正常调用
 * - true：正常执行调用流程，会收到 {@link JCCallCallback#onCallItemUpdate:changeParam: onCallItemUpdate} 通知
 * - false：调用失败，不会收到通知
 */
-(bool)muteMicrophone:(JCCallItem* __nonnull)item mute:(bool)mute;

/**
 * 开启/取消音频输出静音
 *
 * 开启后本端将听不到远端的声音
 * - @ref JCCallItem#speakerMute "speakerMute" 为 true，即静音状态时: 取消静音
 * - @ref JCCallItem#speakerMute "speakerMute" 为 false，即不是静音状态时: 开启静音
 *
 * @param    item JCCallItem 对象，不能为空，并且本地缓存的通话列表中要包含此对象，此对象的通话状态必须为通话中
 * @param    mute 是否静音
 * @return 是否正常调用
 * - true：正常执行调用流程，会收到 {@link JCCallCallback#onCallItemUpdate:changeParam: onCallItemUpdate} 通知
 * - false：调用失败，不会收到通知
 */
-(bool)muteSpeaker:(JCCallItem* __nonnull)item mute:(bool)mute;

/**
 * 开启/取消呼叫保持
 *
 * 调用成功会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知
 *
 * 开启呼叫保持后，通话将被挂起，通过 @ref JCCallItem#hold "hold" 来决定开启/取消呼叫保持
 * - @ref JCCallItem#hold "hold" 为 true，即呼叫保持状态时: 取消呼叫保持
 * - @ref JCCallItem#hold "hold" 为 false，即不是呼叫保持状态时: 开启呼叫保持
 *
 * @note 只针对音频，如果是视频通话则要上层处理视频逻辑
 *
 * @param item JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象，此对象的通话状态必须为通话中
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)hold:(JCCallItem* __nonnull)item;

/**
 * 开启/关闭通话录音
 *
 * 调用成功会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知
 *
 * 开启通话录音，需要保证没有在录音也没有在录制视频<br>
 * 关闭通话录音，需要保证当前通话正在录音
 *
 * @param item      JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象
 * @param enable    开启/关闭录音
 * - true: 开启录音
 * - false: 关闭录音
 * @param filePath  **录音文件的本地保存路径，由用户自行指定，需精确到文件名及格式，例如：/Documents/JuphoonCloud/audio.wmv。请确保目录存在且可写。**
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)audioRecord:(JCCallItem* __nonnull)item enable:(bool)enable filePath:(NSString* __nullable)filePath;

/**
 * 开启/关闭视频通话录制
 *
 * 调用成功会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知
 *
 * 开启视频录制，需要保证 1、没有在录音 2、若是录制远端视频，要保证没有在录制远端视频，并且远端在上传视频流 3、若是录制本端视频，要保证没有在录制本端视频，并且本端在上传视频流。<br>
 * 关闭视频录制，需要保证 1、若是关闭远端视频，要保证正在录制远端视频 2、若是关闭本端视频，要保证正在录制本端视频
 *
 * @param item         JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象
 * @param enable    是否开启视频通话录制
 * - true: 开启
 * - false: 关闭
 * @param remote    是否录制远端视频源
 * - true: 录制远端视频
 * - false: 录制本端视频
 * @param width     录制视频宽像素
 * @param height    录制视频高像素
 * @param filePath  **录制视频文件的本地保存路径，由用户自行指定，需精确到文件名及格式，例如：/Documents/JuphoonCloud/video.mp4。请确保目录存在且可写。**
 * @param bothAudio 是否录制两端音频
 * - true: 录制两端音频
 * - false: 录制视频端音频。也就是说 remote 为 true 就录制远端音频，remote 为 false 录制本端音频。
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)videoRecord:(JCCallItem* __nonnull)item enable:(bool)enable remote:(bool)remote width:(int)width height:(int)height filePath:(NSString* __nullable)filePath bothAudio:(bool)bothAudio;

/**
 * 切换活跃通话
 *
 * 调用此方法时，入参 JCCallItem 对象不是活跃的，则会收到 {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知<br>
 * 入参 JCCallItem 对象已是活跃的，则不会收到通知
 *
 * @param item  需要变为活跃状态的 JCCallItem 对象
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)becomeActive:(JCCallItem* __nonnull)item;

/**
 * 开启/关闭视频流发送
 *
 * 调用成功会收到  {@link  JCCallCallback.onCallItemUpdate:changeParam:  onCallItemUpdate} 通知
 *
 * 通过 JCCallItem 对象的 @ref JCCallItem.uploadVideoStreamSelf "uploadVideoStreamSelf" 状态来决定开启还是关闭视频流的发送
 * - 若 @ref JCCallItem.uploadVideoStreamSelf "uploadVideoStreamSelf" 为 true，即已在上传视频流: 关闭视频流发送
 * - 若 @ref JCCallItem.uploadVideoStreamSelf "uploadVideoStreamSelf" 为 false，即未上传视频流: 开启视频流发送
 *
 * @note 用于视频通话中
 *
 * @param item  JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)enableUploadVideoStream:(JCCallItem* __nonnull)item;

/**
 * 通过通话建立的通道发送数据
 *
 * @param item      需要发送数据的 JCCallItem 对象，不能为空，并且 @ref callItems 通话列表中要包含此对象
 * @param type      文本消息类型，用户可以自定义，例如text，xml等
 * @param content   文本内容
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)sendMessage:(JCCallItem * __nonnull)item type:(NSString * __nonnull)type content:(NSString * __nonnull)content;

/**
 * 获得当前通话统计信息
 *
 * 统计信息以Json字符串形式返回，其中包含 "Audio"、"Video"、"Mtp" 三个键值
 *
 * @return 当前通话统计信息
 */
-(NSString * __nullable)getStatistics;

/**
 * 获得当前活跃的通话
 *
 * 当上层收到 {@link JCCallCallback#onCallItemAdd: onCallItemAdd} 回调后，调用此方法可以获取到当前活跃的通话对象，可以使用该对象进行接听、渲染视频画面等操作。<br>
 * 若上层在收到 {@link JCCallCallback#onCallItemAdd: onCallItemAdd} 回调前调用了此方法，将会返回 nil。
 *
 * @return
 * - JCCallItem 对象：当前活跃的通话对象
 * - nil：当前没有活跃的通话
 */
-(JCCallItem* __nullable)getActiveCallItem;

/**
 * 发送DTMF信息
 *
 * @param item   需要发送数据的 JCCallItem 对象
 * @param value @ref JCCallDtmf "DTMF值"
 * @return 是否正常调用
 * - true：正常执行调用流程
 * - false：调用失败
 */
-(bool)sendDtmf:(JCCallItem *_Nonnull)item value:(JCCallDtmf)value;

/**
 * RUDP开关
 *
 *  true开启，false关闭
 */
-(bool)setRudpMode:(bool)open;
/**
 * RUDP开关状态
 *
 *  true开启，false关闭
 */
-(bool)getRudpMode;

@end

/**
 * @}
 */
