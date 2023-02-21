//
//  JCStorage.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCStorageItem.h"
#import "JCStorageCallback.h"

/**
 * @defgroup 文件存储模块
 * @{
 * 用于管理文件存储
 */

extern const int JCStorageFileExpire;

/**
 *  文件存储类
 *
 *  上传文件：将文件上传至服务器，上传成功后服务器会返回文件地址，地址一般会有一定的有效期
 *
 *  下载文件：通过上传文件服务器返回的地址来下载该文件
 */
@interface JCStorage : NSObject

/**
 * 创建 JCStorage 对象
 *
 * JCStorage 的所有接口函数，如无特殊说明，都建议在主线程调用
 *
 * @note
 * - 调用此方法创建 JCStorage 对象后，期间没有调用过 {@link destroy} 方法销毁对象，然后又重复调用此方法，会直接返回第一次创建的 JCStorage 对象
 * - 调用此方法前确保 JCClient 已完成初始化，即 @ref JCClient#state "state" 获取的状态值不等于 @ref JCClientStateNotInit
 *
 * @param client   JCClient 对象
 * @param callback JCStorageCallback 对象，用于回调相关通知
 * @return 返回 JCStorage 对象
 * @exception "JCClient、JCStorageCallback 任意一个参数传空就会出现调用异常"
 */
+(JCStorage*)create:(JCClient*)client callback:(id<JCStorageCallback>)callback;

/**
 * 销毁 JCStorage 对象
 *
 * 该方法为同步调用，需要等待 JCStorage 实例资源释放后才能执行其他操作，调用此方法后，你将无法再使用 JCStorage 的其它方法和回调。<br>
 * 我们 **不建议** 在 JCSDK 的回调中调用此方法销毁 JCStorage 对象，否则会出现崩溃。<br>
 * 如需在销毁后再次创建 JCStorage 实例，需要等待 @ref destroy 方法执行结束后再创建实例。
 */
+(void)destroy;

/**
 * 上传文件
 *
 * @param path           **文件路径，需精确到文件名及格式，例如：/Documents/JuphoonCloud/audio.wmv。请确保目录存在。**
 * @param cookie         标志数据
 * @param expiredSeconds 过期秒数，-1表示永久
 * @return
 * - JCStorageItem 对象：
 *  - 调用底层接口成功，返回的 JCStorageItem 对象的状态为 @ref JCStorageItemStateTransfering，并且会收到 {@link JCStorageCallback#onFileUpdate: onFileUpdate} 回调
 *  - 调用底层接口失败，返回的 JCStorageItem 对象的状态为 @ref JCStorageItemStateFail，并且会收到 {@link JCStorageCallback.onFileResult: onFileResult} 回调
 * - null：异常调用，不会收到回调
 */
-(JCStorageItem*)uploadFileByExpireTime:(NSString*)path expiredSeconds:(int)expiredSeconds cookie:(id)cookie;

/**
 * 下载文件
 *
 * @param uri      文件地址
 * @param savePath  **本地文件保存地址，由用户自行指定，需精确到文件名及格式，例如：/Documents/JuphoonCloud/audio.wmv。请确保目录存在且可写。**
 * @param cookie   标志数据
 * - JCStorageItem 对象：
 *  - 调用底层接口成功，返回的 JCStorageItem 对象的状态为 @ref JCStorageItemStateTransfering，并且会收到 {@link JCStorageCallback#onFileUpdate: onFileUpdate} 回调
 *  - 调用底层接口失败，返回的 JCStorageItem 对象的状态为 @ref JCStorageItemStateFail，并且会收到 {@link JCStorageCallback.onFileResult: onFileResult} 回调
 * - null：异常调用，不会收到回调
 */
-(JCStorageItem*)downloadFile:(NSString*)uri savePath:(NSString*)savePath cookie:(id)cookie;

/**
 * 取消正在进行的文件上传下载
 *
 * @param item JCStorageItem 对象，由 {@link uploadFileByExpireTime:expiredSeconds:cookie: uploadFileByExpireTime} ，{@link downloadFile:savePath:cookie: downloadFile} 返回
 * @return
 * - true: 成功，会收到 {@link JCStorageCallback#onFileResult: onFileResult} 回调
 * - false: 失败，不会收到回调
 */
-(bool)cancelFile:(JCStorageItem*)item;

/**
 * 通过cookie取消正在进行的文件上传下载
 *
 * 通过 cookie 来匹配缓存中的 JCStorageItem 对象
 * - 若能匹配上，则会调用 {@link cancelFile: cancelFile} 方法并它提供返回值
 * - 若匹配不上，则会直接返回 false
 *
 * @param cookie 上传下载传入的 cookie
 * @return
 * - true: 成功
 * - false: 失败
 */
-(bool)cancelFileByCookie:(id)cookie;

@end

/**
 * @}
 */
