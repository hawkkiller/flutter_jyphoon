//
//  DoodleConstant.h
//  JCDoodlePlugin
//
//  Created by 葛泽宁 on 2022/3/4.
//  Copyright © 2022 juphoon. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const kJCDataTypeDoodle;

/**
 *  @brief 涂鸦类型
 */
typedef NS_ENUM(NSInteger, DoodleActionType) {
    /// 开始涂鸦
    DoodleActionInvalid = 0x100 - 1,
    /// 开始涂鸦
    DoodleActionStart = 0x100,
    /// 结束涂鸦
    DoodleActionStop,
    /// 撤销
    DoodleActionUndo,
    /// 清除涂鸦
    DoodleActionClear,
    /// 画曲线
    DoodleActionDraw,
    /// 橡皮檫
    DoodleActionEraser,
    /// 贴图
    DoodleActionSticker,
    /// 翻页
    DoodleActionSelectPage,
    /// 获取数据
    DoodleActionFetch,
    /// 请求
    DoodleActionRequest,
    /// 回应
    DoodleActionResponse,
    /// 文本
    DoodleActionText,
    /// 椭圆
    DoodleActionOval,
    /// 矩形
    DoodleActionRect,
    /// 箭头
    DoodleActionArrow,
    
    /// 自定义类型
    DoodleActionExtraBase = 0x200
};

typedef NS_ENUM(NSInteger, TouchActionMode) {
    TouchActionNone = 0,
    TouchActionDraw,
    TouchActionEraser,
    TouchActionRect,
    TouchActionOval,
    TouchActionArrow,
    TouchActionText,
    TouchActionStrocker
};

/**
 *  @brief 绘图对象枚举
 */
typedef NS_ENUM(NSInteger, DrawGraph) {
    //无
    None,
    //画笔
    Draw,
    //橡皮
    Eraser,
    //矩形
    Ractangle,
    //圆形
    Ellipse,
    //三角形
    Triangle,
    //箭头
    Arrow,
    //文本
    Text,
    //贴图
    Sticker,
};





