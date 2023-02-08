//
//  JCClient.h
//  JCSDK-OC
//
//  Created by maikireton on 2017/8/10.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCClientCallback.h"

/**
 * @defgroup 登录模块
 * @{
 * 用于初始化 sdk 以及登录 Juphoon Cloud 平台
 */

/**
 * 创建参数
 */
@interface JCClientCreateParam : NSObject

/**
 * sdk 相关信息存放目录
 *
 * 包括账号信息，日志信息等，默认目录为 沙盒 Documents/JuphoonCloud 路径下
 *
 * @note App 必须保证指定的目录可写
 */
@property (nonatomic, copy) NSString* __nonnull sdkInfoDir;

/**
 * sdk 日志目录
 *
 * 默认在 @ref sdkInfoDir 下的 log 目录下
 *
 * @note App 必须保证指定的目录可写
 */
@property (nonatomic, copy) NSString* __nonnull sdkLogDir;

/**
 * sdk 日志等级，默认是 @ref  JCLogLevelInfo
 *
 * - @ref JCLogLevelDisable : 不打印日志
 * - @ref JCLogLevelError : 只打印 error 等级的日志
 * - @ref JCLogLevelInfo : 只打印 info 和 error 等级的日志
 * - @ref JCLogLevelDebug : 打印所有等级的日志
 */
@property (nonatomic) JCLogLevel sdkLogLevel;

@end


/**
 * 登录参数
 *
 * 用于  {@link JCClient#login:password:loginParam: login}  方法最后一个参数
 */
@interface JCClientLoginParam : NSObject

/**
 * 设备id
 *
 * 一般模拟器使用，因为模拟器可能获得的设备id都一样
 */
@property (nonatomic, copy) NSString* __nonnull deviceId;

/**
 * https代理地址
 *
 * 例如 192.168.1.100:3128
 */
@property (nonatomic, copy) NSString* __nullable httpsProxy;

/**
 * 登录账号不存在的情况下是否内部自动创建该账号，默认会自动创建
 * - true: 自动创建账号
 * - false: 不自动创建账号
 */
@property (nonatomic) bool autoCreateAccount;

/**
 * 终端类型
 *
 * 如果需要多终端登录，则需要为每一类型的设备设置一个类型
 * 例如需要手机端和PC端同时能登录，则手机端设置 mobile，pc端设为 pc，在调用  {@link login:password:loginParam: login} 接口时会把同一类型登录的其他终端踢下线。
 */
@property (nonatomic, strong) NSString* __nonnull terminalType;


/**
 * callserver接入方式
 * - true: arc形式
 * - false: endpoint形式
 */
@property (nonatomic) bool  directConnectEnable;

@end


/**
 * 全局基础类
 *
 * 主要负责登录登出管理及账户属性存储
 */
 @interface JCClient : NSObject

/**
 * 获取用户标识
 *
 * 得到的的用户标识就是用户在调用 {@link login:password:loginParam: login} 方法时传入的 userId 参数<br>
 * 需要注意的是只有用户状态为登录中或已登录才能获取到值，其他状态将返回 nil
 */
@property (nonatomic, readonly, copy) NSString* __nullable userId;

/**
 * 获取/设置自己的昵称
 *
 * 在发起呼叫、加入频道时、发送消息时，都会将自己的昵称发送给其他用户
 *
 * @note
 * - 每次调用 {@link create:callback:createParam: create} 初始化 SDK 后都需要重新设置
 * - 不支持 IOT 设备
 */
@property (nonatomic, copy) NSString* __nullable displayName;

/**
 * 获取当前登录状态
 *
 * - @ref JCClientStateNotInit : 未初始化
 * - @ref JCClientStateIdle : 未登录
 * - @ref JCClientStateLogining : 登录中
 * - @ref JCClientStateLogined : 登录成功
 * - @ref JCClientStateLogouting : 登出中
 */
@property (nonatomic, readonly) JCClientState state;

/**
 * 获取创建参数
 *
 * 得到的创建参数就是用户在调用 {@link create:callback:createParam: create} 方法时传入的 createParam 参数<br>
 * 若用户在调用 {@link create:callback:createParam: create} 方法时，createParam 传入了 nil，则返回默认的 JCClientCreateParam 对象
 */
@property (nonatomic, readonly) JCClientCreateParam* __nullable createParam;

/**
 * 获取登录参数
 *
 * 得到的登录参数就是用户在调用 {@link login:password:loginParam: login}  方法时传入的 loginParam 参数<br>
 * 若用户在调用 {@link login:password:loginParam: login} 方法时， loginParam 传入了 nil，则将返回默认的 JCClientLoginParam 对象<br>
 * 需要注意的是只有用户状态为登录中或已登录时才能获取到值，其他状态将返回 nil
 */
@property (nonatomic, readonly) JCClientLoginParam* __nullable loginParam;

/**
 * 获取appkey
 *
 * 得到的appkey是由 {@link create:callback:createParam: create} 方法传入的
 */
@property (nonatomic, readonly) NSString* __nonnull appkey;

/// @cond Doxygen_All
/**
 * 获取自己在服务器上的 uid
 */
@property (nonatomic, readonly) NSString* __nonnull serverUid;
/// @endcond

/**
 * 获取/设置登录服务器地址
 *
 * 默认地址为 http:<span><span/>cn.router.justalkcloud.com:8080（国内环境）。如果是海外用户需要设置为 http:<span><span/>intl.router.justalkcloud.com:8080（国际环境）<br>
 * 该属性需要在调用登录方法 {@link login:password:loginParam: login}  之前进行设置。
 */
@property (nonatomic, copy) NSString * __nonnull serverAddress;


/**
 * 登入超时时间, 单位秒，默认60秒
 */
@property (nonatomic, assign) int timeout;

/**
 * arcChannel开关
 */
@property (nonatomic, assign) bool arcChannel;


/**
 * 创建 JCClient 对象
 *
 * JCClient 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 请确保在调用其他 API 前先调用该方法创建并初始化 JCClient 对象
 * - 调用此方法创建 JCClient 对象后，期间没有调用过 {@link destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCClient 对象
 *
 * @param appKey      用户从 Juphoon Cloud 平台上申请的 AppKey 字符串。详见 [获取 appKey](https://developer.juphoon.com/cn/document/V2.1/create-application.php)
 * @param callback    JCClientCallback 对象，用于回调相关通知
 * @param createParam    创建参数，传入 nil 则按默认值创建，详见 JCClientCreateParam
 * @return JCClient 对象
 * @exception "appKey、JCClientCallback 任意一个参数传空就会返回 nil"
 */
+(JCClient* __nullable)create:(NSString* __nonnull)appKey callback:(id<JCClientCallback> __nonnull)callback createParam:(JCClientCreateParam* __nullable)createParam;

/**
 * 销毁 JCClient 对象
 *
 * 该方法为同步调用，需要等待 JCClient 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 SDK 的其它方法和回调。<br>
 * 此模块为基础模块，所以需要在销毁其他模块的对象后，再调用此方法来销毁 JCClient 对象。此外，我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCClient 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCClient 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 登录 Juphoon Cloud 平台
 *
 * 只有登录成功后才能进行平台上的各种业务
 *
 * @param userId      用户名，长度在 64 字节以内的字符串。以下为支持的字符集范围（共 66 个字符）：
 * - 26 个小写英文字母 a-z
 * - 26 个大写英文字母 A-Z
 * - 10 个数字 0-9
 * - '+'，'-'，'_'，'.'。另外 '-'，'_'，'.' 这三个字符不能处于用户名的第一位
 * @param password      密码，不能为 nil 或 ""，长度不能超过 128 字符。免鉴权模式密码可以随意输入，Token 鉴权模式密码需要输入外部生成的 Token
 * @param loginParam      登录参数，一般不需要设置，如需设置请询问客服，传 nil 则按默认值，详见 JCClientLoginParam
 * @return 调用是否成功
 * - true：正常执行调用流程，登录结果通过 {@link JCClientCallback#onLogin:reason: onLogin} 通知
 * - false：调用异常，不会收到 {@link JCClientCallback#onLogin:reason: onLogin} 通知
 */
-(bool)login:(NSString* __nonnull)userId password:(NSString* __nonnull)password loginParam:(JCClientLoginParam* __nullable)loginParam;

/// @cond Doxygen_All
/**
 * 重登录
 *
 * 该接口在如果有其他同类型终端登录着则会登录失败，一般用于记住了账号后重启自动登录逻辑，登录结果通过 {@link JCClientCallback#onLogin:reason: onLogin} 通知
 *
 * @note 与 @ref login 接口的区别：
 * - 同一设备类型登录同一账号，使用“登录”接口后，后登录的账号会把前面的账号踢下线
 * - 同一设备类型登录同一账号，使用“重登录”接口后，后登录的账号会登录失败，上报已有账号登录错误
 * - 同一账号不同设备类型，使用“登录”和“重登录”都能正常登录
 *
 * @param userId        用户名
 * @param password      密码，免鉴权模式密码可以随意输入，但不能为空
 * @param loginParam    登录参数，传 nil 则按默认值，详见 JCClientLoginParam
 * @return 调用是否成功
 * - true：正常执行调用流程，登录结果通过 {@link JCClientCallback#onLogin:reason: onLogin} 通知
 * - false：调用异常，不会收到 {@link JCClientCallback#onLogin:reason: onLogin} 通知
 */
-(bool)relogin:(NSString* __nonnull)userId password:(NSString* __nonnull)password loginParam:(JCClientLoginParam* __nullable)loginParam;
/// @endcond

/**
 * 登出 Juphoon Cloud 平台
 *
 * 登出后不能进行平台上的各种业务
 *
 * @return 调用是否成功
 * - true：正常执行调用流程，登出结果通过 {@link JCClientCallback#onLogout: onLogout} 通知
 * - false：调用失败，不会收到 {@link JCClientCallback#onLogout: onLogout} 通知
 */
-(bool)logout;

/**
 * 发送在线消息
 *
 * 消息发送结果通过 @ref JCClientCallback#onOnlineMessageSendResult "onOnlineMessageSendResult" 通知
 *
 * @note
 * - 当前对方只有在线才能收到此消息
 * - 此接口调用频次限制 100次/分钟
 *
 * @param userId  对方的 userId
 * @param content 要发送的消息内容
 * @return
 * - &gt;0：成功返回操作id，与回调中的 operationId 一致
 * - -1：失败，不会触发消息发送结果回调
 */
-(int)sendOnlineMessage:(NSString* __nonnull)userId content:(NSString* __nonnull)content;

@end

/**
 * @}
 */
