//
//  JcRoomConstants.swift
//  jc
//
//  Created by Михаил on 08.02.2023.
//

import Foundation
import UIKit


enum JCNavType {
    case JCNavTypeNoNavgationBar
    case JCNavTypeNavgationBar
}

let kMediaChannelReasonKey = "kMediaChannelReasonKey"
let kMdeiaChannelListKey = "kMdeiaChannelListKey"
let kMediaChannelStateChangeNotification = "kMediaChannelStateChangeNotification"
let kMediaChannelOnPropertyChangeNotification = "kMediaChannelOnPropertyChangeNotification"
let kMediaChannelOnJoinSuccessNotification = "kMediaChannelOnJoinSuccessNotification"
let kMediaChannelOnJoinFailNotification = "kMediaChannelOnJoinFailNotification"
let kMediaChannelOnParticipantJoinNotification = "kMediaChannelOnParticipantJoinNotification"
let kMediaChannelOnParticipantLeftNotification = "kMediaChannelOnParticipantLeftNotification"
let kMediaChannelOnParticipantUpdateNotification = "kMediaChannelOnParticipantUpdateNotification"
let kMediaChannelOnParticipantVolumeChangeNotification = "kMediaChannelOnParticipantVolumeChangeNotification"
let kMediaChannelOnLeaveNotification = "kMediaChannelOnLeaveNotification"
let kMediaChannelMessageNotification = "kMediaChannelMessageNotification"
let kMediaChannelOnStopNotification = "kMediaChannelOnStopNotification"
let kMediaChannelOnLeaveOverNotification = "kMediaChannelOnLeaveOverNotification"
let kMediaChannelQueryListNotification = "kMediaChannelQueryListNotification"
let kMediaChannelCreateRoomSuccessNotification = "kMediaChannelCreateRoomSuccessNotification"
let kMediaChannelCreateRoomFailNotification = "kMediaChannelCreateRoomFailNotification"
let kMediaChannelQueryRoomSuccessNotification = "kMediaChannelQueryRoomSuccessNotification"
let kMediaChannelQueryRoomFailNotification = "kMediaChannelQueryRoomFailNotification"
let kMediaChannelStopRoomSuccessNotification = "kMediaChannelStopRoomSuccessNotification"
let kMediaChannelStopRoomFailNotification = "kMediaChannelStopRoomFailNotification"
let kNetWorkNotification = "kNetWorkNotification"
let kQuitRoomVCNotifacation = "kQuitRoomVCNotifacation"

// MARK: - frame 相关
/********************** 屏幕尺寸 *********************/
// 屏幕宽度
let kScreenWidth = UIScreen.main.bounds.width
// 屏幕高度
let kScreenHeight = UIScreen.main.bounds.height
// iPhone X Xs
let iPhoneX = kScreenHeight == 812 ? true : false

let iPhoneXR = kScreenHeight == 1792 / 2 ? true : false

let iPhoneXs_Max = kScreenHeight == 2688 / 3 ? true : false

let kNavigationBarHeight = (iPhoneX || iPhoneXR || iPhoneXs_Max) ? 88 : 64

let kHomeIndicator = (iPhoneX || iPhoneXR || iPhoneXs_Max) ? 34 : 0

// MARK: - 颜色相关
/// 设置 RGB 颜色值
func kRGB(_ r: CGFloat, g: CGFloat, b: CGFloat) -> UIColor {
    return UIColor(red: r / 255.0, green: g / 255.0, blue: b / 255.0, alpha: 1.0)
}
/// 设置 RGBA 颜色值
func kRGBA(_ r: CGFloat, g: CGFloat, b: CGFloat, a: CGFloat) -> UIColor {
    return UIColor(red: r / 255.0, green: g / 255.0, blue: b / 255.0, alpha: a)
}
// MARK: - 随机数
public extension Int {
    /*这是一个内置函数
     lower : 内置为 0，可根据自己要获取的随机数进行修改。
     upper : 内置为 UInt32.max 的最大值，这里防止转化越界，造成的崩溃。
     返回的结果： [lower,upper) 之间的半开半闭区间的数。
     */
    static func randomIntNumber(lower: Int = 0,upper: Int = Int(UInt32.max)) -> Int {
        return lower + Int(arc4random_uniform(UInt32(upper - lower)))
    }
    /**
     生成某个区间的随机数
     */
    static func randomIntNumber(range: Range<Int>) -> Int {
        return randomIntNumber(lower: range.lowerBound, upper: range.upperBound)
    }
}

extension UIView {

    /// 部分圆角
    ///
    /// - Parameters:
    ///   - corners: 需要实现为圆角的角，可传入多个
    ///   - radii: 圆角半径
    func corner(byRoundingCorners corners: UIRectCorner, radii: CGFloat) {
        let maskPath = UIBezierPath(roundedRect: self.bounds, byRoundingCorners: corners, cornerRadii: CGSize(width: radii, height: radii))
        let maskLayer = CAShapeLayer()
        maskLayer.frame = self.bounds
        maskLayer.path = maskPath.cgPath
        self.layer.mask = maskLayer
    }
}

extension Date {

    /// 获取当前 秒级 时间戳 - 10位
    var timeStamp : String {
        let timeInterval: TimeInterval = self.timeIntervalSince1970
        let timeStamp = Int(timeInterval)
        return "\(timeStamp)"
    }

    /// 获取当前 毫秒级 时间戳 - 13位
    var milliStamp : String {
        let timeInterval: TimeInterval = self.timeIntervalSince1970
        let millisecond = CLongLong(round(timeInterval*1000))
        return "\(millisecond)"
    }
}
