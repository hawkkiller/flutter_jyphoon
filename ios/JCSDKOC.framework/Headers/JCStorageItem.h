//
//  JCIMMessage.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCStorageConstants.h"

/**
 * @addtogroup 文件存储模块
 * @{
 */

/**
 *  文件消息对象类
 */
@interface JCStorageItem : NSObject

/**
 * 文件唯一标识符
 */
@property (nonatomic, readonly, copy) NSString* fileId;
           
/**
 * 文件链接，上传文件可获得
 */
@property (nonatomic, readonly, copy) NSString* uri;

/**
 * 文件本地路径
 * @note 发送时表明发送文件路径，接收时表明文件下载保存路径
 */
@property (nonatomic, readonly, copy) NSString* path;

/**
 * 文件传输方向
 *
 * - @ref JCStorageItemDirectionUpload : 上传
 * - @ref JCStorageItemDirectionDownload : 下载
 */
@property (nonatomic, readonly) JCStorageItemDirection direction;

/**
 * 传输状态，参见 @ref JCStorageItemState
 */
@property (nonatomic, readonly) JCStorageItemState state;

/**
 * 文件传输失败的原因
 *
 * 当文件状态为 @ref JCStorageItemStateFail 时有效，参见 @ref JCStorageReason 错误原因
 */
@property (nonatomic, readonly) JCStorageReason error;

/**
 * 文件传输进度
 */
@property (nonatomic, readonly) int progress;

/**
 * 文件大小
 */
@property (nonatomic, readonly) int fileSize;

/**
 * cookie
 */
@property (nonatomic, strong) id cookie;

/**
 * 操作id
 */
@property (nonatomic) unsigned int operationId;

@end

/**
 * @}
 */
