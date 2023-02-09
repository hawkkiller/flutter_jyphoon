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

private class JcApi: JyphoonApi {
  
  lazy var initialization = Initialization()
  lazy var userInfo = UserInfo()
  lazy var mediaChannel = MediaChannel()
  
  private var _isInited = false
  
  func isInited() -> Bool {
    _isInited
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
    userInfo.setAccountNumber(number: accountNumber)
  }
  
  func setTimeout(timeout: Int32) {
    userInfo.setTimeout(timeout: timeout)
  }
  
  func confJoin(confId: String, password: String) -> Bool {
    mediaChannel.join(channelId: confId, password: password)
  }
  
  func setServerAddress(serverAddress: String) {
    initialization.setServerAddress(serverAddress: serverAddress)
  }
  
  func setVideo(video: Bool) {
    mediaChannel.setVideo(video: video)
  }
  
  func setAudio(audio: Bool) {
    mediaChannel.setAudio(audio: audio)
  }
  
  func setSpeaker(speaker: Bool) {
    mediaChannel.setSpeaker(speaker: speaker)
  }
  
  func audio() -> Bool {
    mediaChannel.audio()
  }
  
  func otherAudio() -> Bool {
    mediaChannel.otherAudio()
  }
  
  func video() -> Bool {
    mediaChannel.video()
  }
  
  func getCurrentUserId() -> String? {
    userInfo.getCurrentUserId()
  }
  
  func confLeave() -> Bool {
    mediaChannel.leave()
  }
  
  func otherVideo() -> Bool {
    mediaChannel.otherVideo()
  }
  
  func confStatus() -> String {
    mediaChannel.confStatus()
  }
  
  func switchCamera() {
    mediaChannel.switchCamera()
  }
}
