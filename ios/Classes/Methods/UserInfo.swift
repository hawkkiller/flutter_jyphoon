import Foundation

class UserInfo {
    public func setDisplayName(name: String) {
        JCRoom.shared.setDisplayName(name: name)
    }
}
