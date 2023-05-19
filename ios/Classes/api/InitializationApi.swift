import JCSDKOC

class InitializationApi : JyphoonInitializationApi {
    private let loginParam = JCClientLoginParam()
    
    func clientState() -> Int32 {
        return Int32(JCRoom.shared.client.state.rawValue)
    }
    
    func isInited() -> Bool {
        return JCRoom.shared.inited
    }
    
    func initialize() -> Bool {
       return JCRoom.shared.initialize()
    }
    
    func setAppKey(appKey: String) {
        JCRoom.APP_KEY = appKey
    }
    
    func setDisplayName(displayName: String) {
        JCRoom.shared.setDisplayName(name: displayName)
    }
    
    func setAccountNumber(accountNumber: String) -> Bool {
        let res = JCRoom.shared.client.login(accountNumber, password: "123", loginParam: loginParam)
        return res
    }
    
    func setTimeout(timeout: Int32) {
        JCRoom.shared.client.timeout = timeout
    }
    
    func setServerAddress(serverAddress: String) {
        JCRoom.SERVER_ADDRESS = serverAddress
    }
    
    func getCurrentUserId() -> String? {
        return JCRoom.shared.client.userId
    }
}
