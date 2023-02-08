//
//  JcRoomUtils.swift
//  jc
//
//  Created by Михаил on 08.02.2023.
//

import Foundation
import UIKit

class JCRoomUtils: NSObject {
    //验证手机号
    static func isPhoneNumber(phoneNumber:String) -> Bool {
        if phoneNumber.count == 0 {
            return false
        }
        let mobile = "^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$"
        let regexMobile = NSPredicate(format: "SELF MATCHES %@", mobile)
        return regexMobile.evaluate(with: phoneNumber)
    }
}
