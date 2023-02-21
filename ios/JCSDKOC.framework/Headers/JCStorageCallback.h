//
//  JCIMCallback.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/11.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JCStorageItem.h"

/**
 * @addtogroup 文件存储模块
 * @{
 */

/**
 *  JCStorage 回调
 */
@protocol JCStorageCallback <NSObject>

/**
 * 文件状态更新回调
 *
 * @param item 文件消息对象，通过该对象可以获得当前文件传输的属性及状态
 */
-(void)onFileUpdate:(JCStorageItem*)item;

/**
 * 文件传输结果回调
 *
 * @param item 文件消息对象，通过该对象可以获得当前文件传输的属性及状态
 */
-(void)onFileResult:(JCStorageItem*)item;

@end

/**
 * @}
 */
