//
//  JCMediaDevice.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCClient.h"
#import "JCMediaDeviceVideoCanvas.h"
#import "JCMediaDeviceCallback.h"
#import "JCMediaDeviceConstants.h"

/**
 * @defgroup 设备模块
 * @{
 * 用于管理媒体设备
 */

/**
 * 摄像头对象
 */
@interface JCMediaDeviceCamera : NSObject

/**
 * 摄像头id
 */
@property (nonatomic, readonly) NSString* __nonnull cameraId;

/**
 * 摄像头名字
 */
@property (nonatomic, readonly) NSString* __nonnull cameraName;

/**
 * 摄像头类型：
 * - @ref JCMediaDeviceCameraTypeNone : 未获取到摄像头
 * - @ref JCMediaDeviceCameraTypeFront : 前置摄像头
 * - @ref JCMediaDeviceCameraTypeBack : 后置摄像头
 * - @ref JCMediaDeviceCameraTypeUnknown : 未知摄像头
 */
@property (nonatomic, readonly) JCMediaDeviceCameraType cameraType;

@end

/**
 * 音频设备对象，mac 使用
 */
@interface JCMediaDeviceAudio : NSObject

/**
 * 音频设备id
 */
@property (nonatomic, readonly) NSString* __nonnull audioId;

/**
 * 音频设备名字
 */
@property (nonatomic, readonly) NSString* __nonnull audioName;

/**
 * 输入还是输出设备
 */
@property (nonatomic, readonly) bool input;

@end

/**
 * 窗口对象，mac 使用
 */
@interface JCMediaDeviceWindow : NSObject

/**
 * 窗口id
 */
@property (nonatomic, readonly) NSString* __nonnull windowId;

/**
 * 窗口名字
 */
@property (nonatomic, readonly) NSString* __nonnull windowName;

@end

/**
 * 设备音频参数
 */
@interface JCMediaDeviceAudioParam : NSObject

/**
 * 音频输入采样率
 *
 * 0 表示自动选择，手表等设备可以设置为 8000，默认值为 0
 *
 * 不清楚如何选择音频采样率可不设置此参数，SDK将自动选择合适的音频采样率
 */
@property (nonatomic) int audioInputSamplingRate;

/**
 * 音频输出采样率
 *
 * 0 表示自动选择，手表等设备可以设置为 8000，默认值为 0
 *
 * 不清楚如何选择音频采样率可不设置此参数，SDK将自动选择合适的音频采样率
 */
@property (nonatomic) int audioOutputSamplingRate;

/**
 * 音频输入通道数量
 *
 * 0 表示自动选择，0 和 1 表示单通道，>= 2 表示双通道，默认值为0
 */
@property (nonatomic) int audioInputChannelNumber;

/**
 * 音频输出通道数量
 *
 * 0 表示自动选择，0 和 1 表示单通道，>= 2 表示双通道，默认值为0
 */
@property (nonatomic) int audioOutputChannelNumber;

/**
 * 是否自动打开音频输出设备
 *
 * 建议在一对一通话开始前或者加入频道前进行设置，默认值为 true，表示自动打开
 *
 * - true: 当一对一通话状态为连接中时或者自己加入频道成功时，SDK会自动打开音频输出设备
 * - false: SDK 不会自动打开音频输出设备，建议在一对一通话状态为连接中时或者加入频道成功后，在子线程不断的调用 {@link JCMediaDevice.getAudioOutputData:length:sampleRateHz:channels: getAudioOutputData} 方法获取音频输出数据
 */
@property (nonatomic) bool autoStartAudioOutputDevice;

/**
 * 是否自动打开音频输入设备
 *
 * 建议在一对一通话开始前或者加入频道前进行设置，默认值为 true，表示自动打开
 *
 * - true: 当一对一通话状态为连接中时或者自己加入频道成功时，SDK会自动打开音频输入设备
 * - false: SDK 不会自动打开音频输入设备，建议在一对一通话状态为连接中时或者加入频道成功后，在子线程不断的调用 {@link JCMediaDevice.inputCustomAudioData:sampleRateHz:channels:playDelayMS:recDelayMS:clockDrift: inputCustomAudioData} 方法传入音频数据
 */
@property (nonatomic) bool autoStartAudioInputDevice;

/**
 * 硬件AEC(回声消除)的开启状态
 *
 * 默认是打开状态
 *
 * - @ref JCMediaDeviceAudioAECTypeOn : 开启aec
 * - @ref JCMediaDeviceAudioAECTypeOn : 关闭aec
 * - @ref JCMediaDeviceAudioAECTypeOn : 自动
 */

@property (nonatomic) JCMediaDeviceAudioAECType aecType;

@end

/**
 * 原始音频数据回调事件
 */
@protocol JCAudioFrameCallback <NSObject>

/**
 * 获得采集的音频
 *
 * @param inputId      输入源的自定义字符串
 * @param sampleRateHz 输入源的采样频率
 * @param channels     输入源的频道数量
 * @param buf         该帧的采样数据
 * @param playDelayMS  播放延时
 * @param recDelayMS   采集延时
 * @param clockDrift   时钟漂移
 */
- (void)onAudioInputFrame:(NSString *_Nonnull)inputId sampleRateHz:(int)sampleRateHz channels:(int)channels buf:(unsigned char *_Nonnull)buf playDelayMS:(int)playDelayMS recDelayMS:(int)recDelayMS clockDrift:(int)clockDrift;

/**
 * 获得播放的声音
 *
 * @param outputId    输出源的自定义字符串
 * @param sampleRateHz 输出源的采集频率
 * @param channels     输出源的采样通道数
 * @param buf         该帧的采样数据
 */
- (void)onAudioOutputFrame:(NSString *_Nonnull)outputId sampleRateHz:(int)sampleRateHz channels:(int)channels buf:(unsigned char *_Nonnull)buf;

@end

/**
 * 原始视频数据回调事件
 */
@protocol JCVideoFrameCallback <NSObject>

/**
 * 获得采集的视频
 *
 * @param captureId     采集源id
 * @param face      镜头朝向
 * - @ref JCMediaDeviceCameraType "JCMediaDeviceCameraTypeFront"  前置摄像头
 * - @ref JCMediaDeviceCameraType "JCMediaDeviceCameraTypeBack"  后置摄像头
 * @param imageAngle    图像正立所需角度
 * @param captureOrient     镜头固定角度
 * @param width     图像宽
 * @param height    图像高
 * @param buf       图像数据
 */
- (void)onVideoCaptureFrame:(NSString *_Nonnull)captureId face:(JCMediaDeviceCameraType)face imageAngle:(int)imageAngle captureOrient:(int)captureOrient width:(int*_Nonnull)width height:(int*_Nonnull)height buf:(unsigned char *_Nonnull)buf;

/**
 * 获得播放的视频
 *
 * @param renderId      渲染id
 * @param sourceType    视频源类型
 * - @ref JCMediaDeviceVideoSource "JCMediaDeviceVideoSourcePeer"  用户
 * - @ref JCMediaDeviceVideoSource "JCMediaDeviceVideoSourceCapture"   采集设备
 * - @ref JCMediaDeviceVideoSource "JCMediaDeviceVideoSourceFile"  文件
 * @param angle     图像正立所需角度
 * @param mirror    镜像类型
 * - @ref JCMediaDeviceMirror "JCMediaDeviceMirrorNone"  不镜像
 * - @ref JCMediaDeviceMirror "JCMediaDeviceMirrorHorizontal"  水平方向镜像
 * - @ref JCMediaDeviceMirror "JCMediaDeviceMirrorVertical"  竖直方向镜像
 * - @ref JCMediaDeviceMirror "JCMediaDeviceMirrorAuto"  自动选择
 * - @ref JCMediaDeviceMirror "JCMediaDeviceMirrorFromLeft"  转场动画，从左侧翻转
 * - @ref JCMediaDeviceMirror "JCMediaDeviceMirrorFromTop"  转场动画，从上侧翻转
 * @param width     图像宽
 * @param height    图像高
 * @param buf     图像数据
 * @param timeStamp    渲染时间戳
 */
- (void)onVideoRenderFrame:(NSString *_Nonnull)renderId sourceType:(JCMediaDeviceVideoSource)sourceType angle:(int)angle mirror:(JCMediaDeviceMirror)mirror width:(int*_Nonnull)width height:(int*_Nonnull)height buf:(unsigned char *_Nonnull)buf timeStamp:(unsigned long)timeStamp;

@end

/**
 *  设备模块
 *  @note 扬声器通过 JCMediaDevice 类中 {@link enableSpeaker: enableSpeaker} 进行开关
 */
@interface JCMediaDevice : NSObject

/**
 * 摄像头是否已打开
 * - true： 已打开
 * - false： 未打开
 */
@property (nonatomic, readonly) bool cameraOpen;

/**
 * 文件播放是否打开
 * - true： 已打开文件播放
 * - false： 未打开文件播放
 */
@property (nonatomic, readonly) bool videoFileOpen;

/**
 * 当前使用的摄像头
 */
@property (nonatomic, strong, readonly) JCMediaDeviceCamera* __nullable camera;

/**
 * 摄像头列表
 */
@property (nonatomic, readonly) NSArray<JCMediaDeviceCamera*> *  __nonnull cameras;

/**
 * 默认摄像头
 */
@property (nonatomic, strong) JCMediaDeviceCamera* __nullable defaultCamera;

/**
 * 音频参数
 *
 * 此参数不设置，将使用默认值。此参数在调用 {@link startAudio} 方法前设置，即连接通话或加入频道前设置此参数
 */
@property (nonatomic, strong) JCMediaDeviceAudioParam * _Nonnull audioParam;

/**
 * 视频文件作为本地视频源的渲染标识
 */
@property (nonatomic, strong, readonly) NSString* __nonnull videoFileId;

/**
 * 是否声音被中断
 */
@property (nonatomic, readonly) bool audioInterrupt;

/**
 * 视频渲染窗体角度
 *
 * - @ref JCMediaDeviceVideoAngelAuto : 自动
 * - @ref JCMediaDeviceVideoAngel0 : 0°
 * - @ref JCMediaDeviceVideoAngel90 : 90°
 * - @ref JCMediaDeviceVideoAngel180 : 180°
 * - @ref JCMediaDeviceVideoAngel270 : 270°
 */
@property (nonatomic) JCMediaDeviceVideoAngel videoAngle;

/**
 * 是否使用内部音频设备逻辑
 * 内部音频设备逻辑如下：<br>
 * 1.打开扬声器 - 使用扬声器输出声音 <br>
 * 2.连上蓝牙耳机 - 使用蓝牙耳机输出声音，如果扬声器开着则关闭扬声器 <br>
 * 3.插入耳机 - 使用耳机输出声音，如果扬声器开着则关闭扬声器 <br>
 * 4.蓝牙耳机和有线耳机以最后连上的作为输出 <br>
 * 5.关闭扬声器 - (蓝牙耳机或有线耳机) 优于 听筒 <br>
 *
 * - true: 使用内部音频设备逻辑
 * - false: 不使用内部音频设备逻辑
 */
@property (nonatomic) bool useInternalAudioDeviceLogic;

/**
 * 音频是否启动
 *
 * 一般正式开启通话前需要调用此接口
 *
 * - true：调用成功
 * - false：调用失败
 */
@property (nonatomic, readonly) bool audioStart;

#if TARGET_OS_OSX
/**
 * 音频输入设备列表，mac 使用
 */
@property (nonatomic, readonly) NSArray<JCMediaDeviceAudio*>* __nonnull audioInputs;

/**
 * 当前音频输入设备，mac 使用
 */
@property (nonatomic, strong) JCMediaDeviceAudio* __nullable audioInput;

/**
 * 音频输出设备列表，mac 使用
 */
@property (nonatomic, readonly) NSArray<JCMediaDeviceAudio*>* __nonnull audioOutputs;

/**
 * 当前音频输出设备，mac 使用
 */
@property (nonatomic, strong) JCMediaDeviceAudio* __nullable audioOutput;

/**
 * 桌面列表，mac 使用
 */
@property (nonatomic, readonly) NSArray<JCMediaDeviceWindow*>* __nonnull desktops;

/**
 * 窗口列表，mac 使用
 */
@property (nonatomic, readonly) NSArray<JCMediaDeviceWindow*>* __nonnull windows;

/**
 * 屏幕分享的窗口，mac 使用
 */
@property (nonatomic, strong) JCMediaDeviceWindow* __nullable screenshareWindow;
#endif

/**
 * 创建 JCMediaDevice 对象
 *
 * JCMediaDevice 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 调用此方法创建 JCMediaDevice 对象后，期间没有调用过 {@link destroy destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCMediaDevice 对象
 * - 调用此方法前确保 JCClient 已完成初始化，即 @ref JCClient.state "state" 状态值不等于 @ref JCClientStateNotInit
 *
 * @param client       JCClient 对象
 * @param callback   JCMediaDeviceCallback 对象，用于回调相关通知
 * @return JCMediaDevice 对象
 * @exception "JCClient、JCMediaDeviceCallback 任意一个参数传空就会调用失败"
 */
+(JCMediaDevice* __nullable)create:(JCClient* __nonnull)client callback:(id<JCMediaDeviceCallback> __nonnull)callback;

/**
 * 销毁 JCMediaDevice 对象
 *
 * 该方法为同步调用，需要等待 JCMediaDevice 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCMediaDevice 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCMediaDevice 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCMediaDevice 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 开始自身视频渲染
 *
 * 获取本端视频预览对象 JCMediaDeviceVideoCanvas，通过此对象能获得视图用于UI显示
 *
 * 一对一通话建议使用 {@link JCCallItem.startSelfVideo: startSelfVideo} 方法代替，多方通话建议使用 {@link JCMediaChannelParticipant.startVideo:pictureSize: startVideo} 方法代替
 *
 * @note 调用此方法时需要保证默认摄像头不为空，即 @ref defaultCamera 不为空，否则将直接返回 nil
 *
 * @param type 渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @return
 * - JCMediaDeviceVideoCanvas 对象：开始自身视频渲染成功
 * - nil：开始自身视频渲染失败
 */
-(JCMediaDeviceVideoCanvas* __nullable)startCameraVideo:(JCMediaDeviceRender)type;

/**
 * 开始自身视频渲染
 *
 * 获取本端视频预览对象 JCMediaDeviceVideoCanvas，通过此对象能获得视图用于UI显示
 *
 * 一对一通话建议使用 {@link JCCallItem#startSelfVideo: startSelfVideo} 方法代替，多方通话建议使用 {@link JCMediaChannelParticipant#startVideo:pictureSize: startVideo} 方法代替
 *
 * @note 调用此方法时需要保证默认摄像头不为空，即 @ref defaultCamera 不为空，否则将直接返回 nil
 *
 * @param type 渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @param view 渲染视图
 * @return
 * - JCMediaDeviceVideoCanvas 对象：开始自身视频渲染成功
 * - nil：开始自身视频渲染失败
 */
-(JCMediaDeviceVideoCanvas* __nullable)startCameraVideo:(JCMediaDeviceRender)type view:(JCView* __nonnull)view;

/**
 * 开始其他端的视频渲染
 *
 * 获取其他端的视频预览对象 JCMediaDeviceVideoCanvas，通过此对象能获得视图用于UI显示
 *
 * 一对一通话建议使用 {@link JCCallItem#startOtherVideo: startOtherVideo} 方法代替，多方通话建议使用 {@link JCMediaChannelParticipant#startVideo:pictureSize: startVideo} 方法代替
 *
 * @param videoSource 渲染标识串，通过 JCMediaChannelParticipant 的 @ref JCMediaChannelParticipant.renderId  "renderId" 方法和 JCCallItem 的 @ref JCCallItem.renderId  "renderId" 方法可以得到
 * @param type  渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口，会有裁剪
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @return
 * - JCMediaDeviceVideoCanvas 对象：开始自身视频渲染成功
 * - nil：开始自身视频渲染失败
 */
-(JCMediaDeviceVideoCanvas* __nullable)startVideo:(NSString* __nonnull)videoSource renderType:(JCMediaDeviceRender)type;

/**
 * 开始其他端的视频渲染
 *
 * 获取其他端的视频预览对象 JCMediaDeviceVideoCanvas，通过此对象能获得视图用于UI显示
 *
 * 一对一通话建议使用 {@link JCCallItem#startOtherVideo: startOtherVideo} 方法代替，多方通话建议使用 {@link JCMediaChannelParticipant.startVideo:pictureSize: startVideo} 方法代替
 *
 * @param videoSource 渲染标识串，通过 JCMediaChannelParticipant 的 @ref JCMediaChannelParticipant.renderId  "renderId" 方法和 JCCallItem 的 @ref JCCallItem.renderId  "renderId" 方法可以得到
 * @param type  渲染模式：
 * - @ref JCMediaDeviceRenderFullScreen : 铺满窗口
 * - @ref JCMediaDeviceRenderFullContent : 全图像显示，会有黑边
 * - @ref JCMediaDeviceRenderFullAuto : 自适应
 * @param view 渲染视图
 * @return JCMediaDeviceVideoCanvas 对象
 */
-(JCMediaDeviceVideoCanvas* __nullable)startVideo:(NSString* __nonnull)videoSource renderType:(JCMediaDeviceRender)type view:(JCView* __nonnull)view;

/**
 * 停止视频渲染
 *
 * 一对一通话建议使用 {@link JCCallItem#stopSelfVideo stopSelfVideo} 和 {@link JCCallItem#stopOtherVideo stopOtherVideo} 方法代替，多方通话渲染建议使用 {@link JCMediaChannelParticipant#stopVideo stopVideo} 方法代替
 *
 * @param canvas JCMediaDeviceVideoCanvas 对象，由 {@link startVideo:renderType: startVideo} 或 {@link startCameraVideo: startCameraVideo} 返回
 */
-(void)stopVideo:(JCMediaDeviceVideoCanvas* __nonnull)canvas;

/**
 * 启动音频
 *
 * 在通话连接中或者加入频道成功时，SDK内部会自动调用此方法来启动音频，上层无需再调用此方法
 *
 * @return 调用是否成功
 * - true：调用成功
 * - false：调用失败
 */
-(bool)startAudio;

/**
 * 停止音频
 *
 * 在通话挂断时或者离开频道时，SDK内部会自动调用此方法来停止音频，上层无需再调用此方法
 *
 * @return 调用是否成功
 * - true：调用成功
 * - false：调用失败
 */
-(bool)stopAudio;

/**
 * 开启摄像头
 *
 * @note 调用此方法时需要保证默认摄像头不为空，即 @ref defaultCamera 不为空，否则将直接返回 false
 *
 * @return 调用是否成功
 * - true：正常执行调用流程
 *  - 若调用此方法前摄像头已打开，不会收到回调通知
 *  - 若调用此方法前摄像头未打开，会收到 {@link JCMediaDeviceCallback#onCameraUpdate onCameraUpdate} 通知
 * - false：调用失败
 */
-(bool)startCamera;

/**
 * 关闭摄像头
 *
 * @return 调用是否成功
 * - true：正常执行调用流程
 *  - 调用此方法前摄像头已打开，不会收到回调通知
 *  - 调用此方法前摄像头未打开，会收到 {@link JCMediaDeviceCallback#onCameraUpdate onCameraUpdate} 通知
 * - false：调用失败
 */
-(bool)stopCamera;

/**
 * 切换摄像头
 *
 * 内部会根据当前摄像头类型来进行切换
 *
 * - 调用此方法时要保证摄像头已打开，否则将直接返回 false
 * - 设备拥有两个以上摄像头，否则将直接返回 true
 * - 满足以上两个条件后，内部会调用 {@link switchCamera: switchCamera:(JCMediaDeviceCamera *)camera}  方法并提供返回值
 *
 * @return 调用是否成功
 * - true：调用成功
 * - false：调用失败
 */
-(bool)switchCamera;

/**
 * 切换摄像头
 *
 * 调用此方法时需要保证摄像头已打开并且摄像头数大于0，否则将直接返回 false
 *
 * @param camera 摄像头
 * @return 调用是否成功
 * - true：正常执行调用流程
 *  - 摄像头个数为1，不会收到回调
 *  - 摄像头个数大于1，会收到 {@link JCMediaDeviceCallback#onCameraUpdate onCameraUpdate} 通知
 * - false：调用失败，不会收到回调
 */
-(bool)switchCamera:(JCMediaDeviceCamera* __nonnull)camera;

/**
 * 设置摄像头采集属性
 *
 * 在调用 {@link JCCallItem#startSelfVideo: startSelfVideo} 方法或 {@link JCMediaChannelParticipant#startVideo:pictureSize: startVideo} 方法开启自身视频渲染前设置即可生效
 *
 * @param width     采集宽度，默认640
 * @param height    采集高度，默认360
 * @param frameRate 采集帧速率，默认24
 */
- (void)setCameraProperty:(int)width height:(int)height framerate:(int)framerate;

/**
 * 设置屏幕共享采集属性
 *
 * 在调用 {@link JCMediaChannel#enableScreenShare: enableScreenShare} 方法开启屏幕共享前设置即可生效
 *
 * @param width     采集宽度，默认1280
 * @param height    采集高度，默认720
 * @param frameRate 采集帧速率，默认10
 */
- (void)setScreenCaptureProperty:(int)width height:(int)height framerate:(int)framerate;

/**
 * 开启视频文件作为视频输入源
 *
 * @note
 * - 加入会议前或者一对一通话接听前调用
 * - 文件和摄像头作为视频输入源只能存在一种，如果当前摄像头已开启的话会关闭摄像头
 *
 * @return 调用是否成功
 * - true：正常执行调用流程
 *  - 若调用此方法时文件视频源已开启，则不会收到回调
 *  - 若调用此方法时文件视频源还未开启，则会收到 {@link JCMediaDeviceCallback#onCameraUpdate onCameraUpdate} 回调
 * - false：调用失败，不会收到回调
 */
-(bool)startVideoFile;

/**
 * 逐帧采集视频画面
 *
 * 调用此方法时要保证文件视频源已开启
 *
 * @note 当 format 为 H264 格式并且是关键帧时：
 * - 第一帧一定要包含关键帧，并且需要将 0x67 0x68 0x65 的数据作为完整一帧传入，其中0x67，0x68为pps，0x65为关键帧标识
 * - 后续P帧以 0x41 数据形式传入
 * - 关键帧要以固定间隔传入，例如5秒，否则一开始可能有几秒对端无法显示视频
 *
 * @param data        画面二进制数据
 * @param format   @ref JCMediaDeviceVideoPixelFormat "视频像素格式"
 * @param width     宽
 * @param height   高
 */
-(void)setVideoFileFrame:(NSData* __nonnull)srcFrame format:(JCMediaDeviceVideoPixelFormat)format width:(int)width height:(int)height;

/**
 * 向文件视频源逐帧添加视频数据
 *
 * 调用此方法时要保证文件视频源已开启
 *
 * @note 当 format 为 H264 格式并且是关键帧时：
 * - 第一帧一定要包含关键帧，并且需要将 0x67 0x68 0x65 的数据作为完整一帧传入，其中0x67，0x68为pps，0x65为关键帧标识
 * - 后续P帧以 0x41 数据形式传入
 * - 关键帧要以固定间隔传入，例如5秒，否则一开始可能有几秒对端无法显示视频
 *
 * @param srcFrame  视频数据
 * @param angle 角度, 为 90 的倍数
 * @param mirror 是否镜像，0 不镜像，1 镜像
 */
-(void)setVideoFileFrame:(CVPixelBufferRef __nonnull)srcFrame angle:(int)angle mirror:(int)mirror;

/**
 * 关闭逐帧采集画面
 *
 * @return 调用是否成功
 * - true：正常执行调用流程
 *  - 若调用此方法时文件视频源已关闭，不会收到回调
 *  - 若调用此方法时文件视频源未关闭，则会收到 {@link JCMediaDeviceCallback#onCameraUpdate onCameraUpdate} 回调
 * - false：调用失败
 */
-(bool)stopVideoFile;

/**
 * 获取摄像头曝光补偿最大最小值,单位EV
 *
 * @return 最小曝光补偿：
 */
-(int)getMinExposureCompensation;

/**
 * 获取摄像头曝光补偿最大最小值,单位EV
 *
 * @return 最大曝光补偿：
 */
-(int)getMaxExposureCompensation;

/**
 * 获取摄像头曝光补偿步长
 *
 * @return 获取曝光补偿步长：
 */
-(float)getExposureCompensationStep;

/**
 * 设置摄像头曝光补偿
 *
 * @return 返回使用结果
 */

-(int)setExposureCompensation:(float)exposureValue;


/**
 * 设置摄像头变焦
 *
 * @return 返回使用结果
 */

-(int)setCameraZoom:(float)zoom;

/**
 * 查询摄像头是否支持闪光灯
 *
 * @return 是否支持闪光灯：
 */
-(bool)isCameraFlashSupported;

/**
 * 是否使用闪光灯
 *
 * @return 返回使用结果
 */
-(bool)enableFlash:(bool)enable;


#pragma mark - 音频数据管理

/**
 * 注册语音观测器对象。
 *
 * 该方法用于注册语音观测器对象，即注册回调。当需要 SDK 给出 {@link JCAudioFrameCallback.onAudioInputFrame:sampleRateHz:channels:buf:playDelayMS:recDelayMS:clockDrift: onAudioInputFrame}
 * 或 {@link JCAudioFrameCallback.onAudioOutputFrame:sampleRateHz:channels:buf: onAudioOutputFrame} 回调时，需要使用该方法注册回调。 该方法需要在加入频道前或开始通话前调用。
 *
 * @param callback 实现 JCAudioFrameCallback 协议的对象。传入 nil 表示取消注册。我们建议在收到 {@link JCMediaChannelCallback.onLeave:channelId: onLeave} 或 {@link JCMediaChannelCallback.onStop:reason: onStop} 或 {@link JCCallCallback.onCallItemRemove:reason:description: onCallItemRemove} 后调用，来释放语音观测器对象。
 */
- (void)registerAudioFrameCallback:(id<JCAudioFrameCallback> __nullable)callback;

/**
 * 注册视频观测器对象。
 *
 * 该方法用于注册视频观测器对象，即注册回调。当需要 SDK 给出 {@link JCVideoFrameCallback.onVideoCaptureFrame:face:imageAngle:captureOrient:width:height:buf: onVideoCaptureFrame}
 * 或 {@link JCVideoFrameCallback.onVideoRenderFrame:sourceType:angle:mirror:width:height:buf:timeStamp: onVideoRenderFrame} 回调时，需要使用该方法注册回调。 该方法需要在加入频道前或开始通话前调用。
 *
 * @param callback JCVideoFrameCallback 对象。传入 nil 表示取消注册。我们建议在收到 {@link JCMediaChannelCallback.onLeave:channelId: onLeave} 或 {@link JCMediaChannelCallback.onStop:reason: onStop} 或 {@link JCCallCallback.onCallItemRemove:reason:description: onCallItemRemove} 后调用，来释放语音观测器对象。
 *
 * @return 是否正常调用
 * - true: 正常执行调用流程
 * - false: 调用失败
 */
- (void)registerVideoFrameCallback:(id<JCVideoFrameCallback> __nullable)callback;

/**
 * 将音频输入数据输入到媒体层
 * 当 @ref JCMediaDeviceAudioParam.autoStartAudioInputDevice "autoStartAudioInputDevice" 为 false 时才可以将音频输入数据输入到媒体层
 * 建议在一对一通话状态为连接中时或者加入频道成功后，在子线程不断的调用此方法传入音频数据
 *
 * @param data       外部采集数据源，需要传入 NSData 对象
 * @param sampleRateHz 外部输入源的采样频率，取值范围：8000，16000，32000，44100，48000
 * @param channels     外部输入源的采样通道数，取值范围：1或2
 * @param playDelayMS  播放延时 一般设为0
 * @param recDelayMS   采集延时 一般设为0
 * @param clockDrift   时钟漂移 一般设为0
 *
 * @return 是否正常调用
 * - true: 正常执行调用流程
 * - false: 调用失败
 */
- (bool)inputCustomAudioData:(NSData *_Nonnull)data sampleRateHz:(int)sampleRateHz channels:(int)channels playDelayMS:(int)playDelayMS recDelayMS:(int)recDelayMS clockDrift:(int)clockDrift;

/**
 * 获取音频输出数据
 *
 * 当 @ref JCMediaDeviceAudioParam.autoStartAudioOutputDevice "autoStartAudioOutputDevice" 为 false 时才可以获取到音频输出数据
 * 建议在一对一通话状态为连接中时或者加入频道成功后，在子线程不断的调用此方法获取音频输出数据
 *
 * @param buf   字节缓冲区，从媒体层获取的音频输出数据将被存入此缓冲区，需要传入 unsigned char* 对象。缓冲区的容量为(采样频率*采样通道数/100)
 * @param sampleRateHz 输出源的采集频率，取值范围：8000，16000，32000，44100，48000
 * @param channels     输出源的采样通道数，取值范围：1或2
 * @param length    音频输出数据的字节长度，即 buf 参数的字节长度
 *
 * @return 是否正常调用
 * - true: 正常执行调用流程
 * - false: 调用失败
 */
- (bool)getAudioOutputData:(unsigned char*_Nonnull)buf length:(int)length sampleRateHz:(int)sampleRateHz channels:(int)channels;


#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

/**
 * 没有插入耳机或外接蓝牙时是否默认开启扬声器，默认关闭，iOS 使用
 * - true 默认开启
 * - false 默认不开启
 */
@property (nonatomic) bool defaultSpeakerOn;

/**
 * 开启/关闭扬声器，iOS 使用
 *
 * 只有在音频已经启动的情况下调用才会生效
 *
 * @param enable 开启或者关闭扬声器
 * - true: 开启
 * - false: 关闭
 */
-(void)enableSpeaker:(bool)enable;

/**
 * 获得当前音频模式，目前只支持听筒和扬声器，iOS 使用
 * @return 音频模式
 */
-(NSString* __nullable)getAudioOutputType;

/**
 * 扬声器是否已打开，iOS 使用
 * - true: 已打开
 * - false: 未打开
 */
-(bool)isSpeakerOn;

#endif
@end

/**
 * @}
 */
