import Foundation
import JCSDKOC.JCClient

class UserInfo {
    private let loginParam = JCClientLoginParam()
    
    /// must be called after initialization
    public func setDisplayName(name: String) {
        JCRoom.shared.setDisplayName(name: name)
    }
    
    /// Must be called after initialization
    public func setTimeout(timeout: Int32) {
        JCRoom.shared.client.timeout = timeout
    }
    
    /// Must be called after initialization
    public func setAccountNumber(number: String) -> Bool {
        return JCRoom.shared.client.login(number, password: "123", loginParam: loginParam)
    }
    
    public func getCurrentUserId() -> String? {
        return JCRoom.shared.client.userId
    }
    
    public func clientState() -> Int {
        return JCRoom.shared.client.state.rawValue
    }
}
