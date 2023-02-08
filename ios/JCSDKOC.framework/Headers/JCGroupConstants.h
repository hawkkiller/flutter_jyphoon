//
//  JCGroupConstants.h
//  JCSDKOC
//
//  Created by maikireton on 2017/8/15.
//  Copyright © 2017年 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

/// @addtogroup 错误码
/// @{

/**
 *  群组错误原因
 */
typedef NS_ENUM(NSInteger, JCGroupReason) {
    /// 正常
    JCGroupReasonNone,
    /// 未登录
    JCGroupReasonNotLogin,
    /// 函数调用失败
    JCGroupReasonCallFunctionError,
    /// 超时
    JCGroupReasonTimeOut,
    /// 网络异常
    JCGroupReasonNetWork,
    /// 参考错误
    JCGroupReasonInvalid,
    /// 内部获得 Agent 失败
    JCGroupReasonGetAgent,
    /// 服务器错误
    JCGroupReasonServer,
    /// 更新时间无效
    JCGroupReasonUpdateTimeInvalid,
    /// 禁止操作
    JCGroupReasonPermissionDenied,
    /// Uid 找不到
    JCGroupReasonUidNotFound,
    /// 关系不存在
    JCGroupReasonChangeNotExists,
    /// 关系已存在
    JCGroupReasonAddAlreadyExists,
    /// 不能添加自己
    JCGroupReasonAddSelf,
    /// 关系类型错误
    JCGroupReasonRelationTypeInvalid,
    /// 删除的关系不存在
    JCGroupReasonRemoveNotExist,
    /// 状态类型错误
    JCGroupReasonStatusTypeError,
    /// 只允许一个创建者
    JCGroupReasonWriteOwnerError,
    /// 写入属性错误
    JCGroupReasonSetWriteProperty,
    /// 类型不被允许
    JCGroupReasonApplyTypeGranted,
    /// 缺少群名
    JCGroupReasonLackOfGroupName,
    /// 未知的群类型
    JCGroupReasonUnknownGroupType,
    /// 非群主
    JCGroupReasonOwnerNotInvoker,
    /// 不在群中
    JCGroupReasonNotInGroup,
    /// 在黑名单中
    JCGroupReasonBlacklist,
    /// 群已满
    JCGroupReasonCapacityFull,
    /// 不属于群
    JCGroupReasonNotBelongToGroup,
    /// 权限不够
    JCGroupReasonWriteExceedRight,
    /// 查询Uid错误
    JCGroupReasonQueryUid,
    /// 其他错误
    JCGroupReasonOther = 100
};
/// @}

/// @addtogroup 群组模块
/// @{

/**
 *  群组变化状态
 */
typedef NS_ENUM(NSInteger, JCGroupChangeState) {
    /// 无
    JCGroupChangeStateNone,
    /// 新增
    JCGroupChangeStateAdd,
    /// 更新
    JCGroupChangeStateUpdate,
    /// 删除
    JCGroupChangeStateRemove,
    /// 群属性
    JCGroupChangeStateProperties,
};

/**
 * 群组类型
 */
typedef NS_ENUM(NSInteger, JCGroupType) {
    /// 讨论组
    JCGroupTypeDiscussion = 0,
    /// 普通群
    JCGroupTypeNormal,
    /// 大群
    //JCGroupTypeLarge,
};

/**
 *  群成员角色类型
 */
typedef NS_ENUM(NSInteger, JCGroupMemberType) {
    /// 拥有者
    JCGroupMemberTypeOwner = 0x100 + 1,
    /// 管理员
    JCGroupMemberTypeManager = 0x100 + 2,
    /// 群成员
    JCGroupMemberTypeMember = 0x100 + 3,
};
/// @}

