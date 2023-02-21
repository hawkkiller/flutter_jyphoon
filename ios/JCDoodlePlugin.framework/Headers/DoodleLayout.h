//
//  DoodleLayout.h
//  JCDoodlePlugin
//
//  Created by young on 17/1/3.
//  Copyright © 2017年 young. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "DoodleAction.h"
#import "DoodleConstant.h"

/**
 *  @brief DoodleLayout 回调代理
 */
@protocol DoodleLayoutDelegate <NSObject>

/**
 * @brief 结束涂鸦回调
 */
- (void)onCloseDoodle;
/**
 * @brief 清除涂鸦回调
*/
- (void)onWillCleanDoodle;

/**
 * @brief 暂停涂鸦回调（隐藏toolbar）
*/
- (void)onPauseDoodle;

/**
 * @brief 重启涂鸦回调（显示toolbar）
*/
- (void)onRestartDoodle;

/**
 *  @brief 涂鸦回调
 *  @param doodleAction DoodleAction对象
 *
 */
- (void)onDoodleActionGenerated:(DoodleAction *)doodleAction;


@end
/**
 *  @brief 涂鸦模块类
 */
@interface DoodleLayout : UIViewController


#pragma mark -  涂鸦动作相关

/**
 *  画笔宽度
 */
@property (nonatomic, assign) CGFloat brushWidth;

/**
 *  橡皮宽度
 */
@property (nonatomic, assign) CGFloat eraserWidth;

/**
 *  字体大小
 */
@property (nonatomic, assign) CGFloat textSize;

/**
 *  画笔颜色
 */
@property (nonatomic, strong) UIColor *brushColor;

/**
 *  涂鸦动作类型
 */
@property (nonatomic, assign) TouchActionMode actionMode;


/**
 * @brief 撤销
 */

- (void) undo;

/**
 * @brief 清除涂鸦
 */
- (void)cleanDoodle;

/**
 * @brief 保存图片
 */
- (void)saveImage;


#pragma mark - other

/**
 *  DoodleLayout代理
 */
@property (nonatomic, weak) id<DoodleLayoutDelegate> delegate;

/**
 * @brief 初始化DoodleLayout控件
 * @return DoodleLayout对象
 */
- (instancetype)initWithUserId:(NSString*)userId;

/**
 * @brief 结束白板涂鸦
 */
- (void)dismissDoodle;

/**
 * @brief 注入白板涂鸦动作 
 */
- (void)addAction:(DoodleAction*)doodleAction;

/**
 * @brief 字符串转doodleAction对象
 */

- (DoodleAction*)stringToDoodleAction:(NSString*)string;

/**
 * @brief 字符串转doodleAction对象
 */

- (NSString*)doodleActionToString:(DoodleAction*)doodleAction;

/**
 * @brief 设置画布尺寸
 */

- (void)resetDoodleViewFrame:(CGRect)rect;


/**
 * @brief 开关toolbar
 */

- (void)hideToolBar:(bool)hide;


@end
