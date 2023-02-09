import Foundation
import UIKit
import JCSDKOC.JCMediaChannel

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
    
    static var selfParticipant: JCMediaChannelParticipant? {
        get {
            return JCRoom.shared.mediaChannel.selfParticipant
        }
    }
    
    static var otherParticipant: JCMediaChannelParticipant? {
        get {
            let participants = JCRoom.shared.mediaChannel.participants
            for participant in participants {
                let jcParticipant = participant as! JCMediaChannelParticipant?
                if (selfParticipant != jcParticipant) {
                    return jcParticipant
                }
            }
            return nil
        }
    }
}
