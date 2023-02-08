import Flutter
import UIKit
import JCSDKOC.JCClient

public class SwiftJcPlugin: NSObject, FlutterPlugin {
  
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "jc", binaryMessenger: registrar.messenger())
    let instance = SwiftJcPlugin()
    let api = JcApi()
    JyphoonApiSetup.setUp(binaryMessenger: registrar.messenger(), api: api)
    registrar.addMethodCallDelegate(instance, channel: channel)
  }
}
extension String: Error {}

private class JcApi: JyphoonApi {
  
  lazy var initialization = Initialization()
  lazy var userInfo = UserInfo()
  
  private var _isInited = false
  
  func isInited() -> Bool {
    return _isInited
  }
  
  func initialize() -> Bool {
    _isInited = initialization.initialize()
    return _isInited
  }
  
  func setAppKey(appKey: String) {
    initialization.setAppKey(key: appKey)
  }
  
  func setDisplayName(displayName: String) {
    userInfo.setDisplayName(name: displayName)
  }
  
  func setAccountNumber(accountNumber: String) -> Bool {
    return false
  }
  
  func setTimeout(timeout: Int32) {
    
  }
  
  func confJoin(confId: String, password: String) -> Bool {
    return false
  }
  
  func setServerAddress(serverAddress: String) {
    initialization.setServerAddress(serverAddress: serverAddress)
  }
  
  func setVideo(video: Bool) {
    
  }
  
  func setAudio(audio: Bool) {
    
  }
  
  func setSpeaker(speaker: Bool) {
    
  }
  
  func audio() -> Bool {
    return false
  }
  
  func otherAudio() -> Bool {
    return false
  }
  
  func video() -> Bool {
    return false
  }
  
  func getCurrentUserId() -> String? {
    return ""
  }
  
  func confLeave() -> Bool {
    return false
  }
  
  func otherVideo() -> Bool {
    return false
  }
  
  func confStatus() -> String {
    return ""
  }
  
  func switchCamera() {
    
  }
  
  
}
