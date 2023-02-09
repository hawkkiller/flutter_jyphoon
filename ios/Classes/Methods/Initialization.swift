import Foundation

class Initialization {
    /// Must be called before initialization
    public func setAppKey(key: String) {
        JCRoom.APP_KEY = key
    }
    /// Must be called before initialization
    public func setServerAddress(serverAddress: String) {
        JCRoom.SERVER_ADDRESS = serverAddress
    }
    
    public func initialize() -> Bool {
       return JCRoom.shared.initialize()
    }
}
