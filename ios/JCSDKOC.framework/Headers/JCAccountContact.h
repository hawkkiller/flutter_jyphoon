//
//  JCAccountContact.h
//  JCSDKOCShare
//
//  Created by maikireton on 2019/12/18.
//  Copyright © 2019 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @addtogroup 账号模块
 * @{
 */

/**
 * 联系人对象
 */
@interface JCAccountContact : NSObject

/**
 * 获取/设置联系人在服务器上的 uid
 */
@property (nonatomic, copy) NSString *serverUid;

/**
 * 获取/设置自己与该联系人的关系
 * - @ref JCAccountContactTypeNone : 无关系
 * - @ref JCAccountContactTypeStranger : 陌生人
 * - @ref JCAccountContactTypeSystem : 系统联系人
 */
@property (nonatomic) JCAccountContactType type;

/**
 * 获取/设置昵称
 */
@property (nonatomic, copy) NSString *displayName;

/**
 * 获取/设置联系人备注
 */
@property (nonatomic, copy) NSString *tag;

/**
 * 是否已开启免打扰模式
 * - true: 已开启免打扰
 * - false: 未开启免打扰
 */
@property (nonatomic) bool dnd;

/**
 * 联系人变化状态：
 * - @ref JCAccountContactChangeStateAdd : 新增
 * - @ref JCAccountContactChangeStateUpdate : 更新
 * - @ref JCAccountContactChangeStateRemove : 删除
 */
@property (nonatomic) JCAccountContactChangeState changeType;

@end

/**
 * @}
 */

NS_ASSUME_NONNULL_END
