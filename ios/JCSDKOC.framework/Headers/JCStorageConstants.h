//
//  JCIMConstants.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 错误码
/// @{

/**
 * 文件传输错误原因
 */
typedef NS_ENUM(NSInteger, JCStorageReason) {
    /// 无异常
    JCStorageReasonNone,
    /// 未登录
    JCStorageReasonNotLogin,
    /// 网络异常
    JCStorageReasonNetWork,
    /// 文件太大
    JCStorageReasonTooLarge = 30,
    /// 超时
    JCStorageReasonTimeOut,
    /// 文件过期
    JCStorageReasonExpire,
    /// 其他错误
    JCStorageReasonOther = 100,
};
/// @}

/// @addtogroup 文件存储模块
/// @{

/**
 * 文件传输状态
 */
typedef NS_ENUM(NSInteger, JCStorageItemState) {
    /// 文件初始状态
    JCStorageItemStateInit,
    /// 文件传输中状态
    JCStorageItemStateTransfering,
    /// 文件传输成功状态
    JCStorageItemStateOK,
    /// 文件传输失败状态
    JCStorageItemStateFail,
    /// 文件传输取消状态
    JCStorageItemStateCancel,
};

/**
 * 文件传输方向
 */
typedef NS_ENUM(NSInteger, JCStorageItemDirection) {
    /// 上传
    JCStorageItemDirectionUpload,
    /// 下载
    JCStorageItemDirectionDownload,
};
/// @}
