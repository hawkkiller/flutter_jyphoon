import Flutter
import UIKit
import JCSDKOC.JCClient

public class SwiftJcPlugin: NSObject, FlutterPlugin {
  
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "jc", binaryMessenger: registrar.messenger())
    let instance = SwiftJcPlugin()
    let api = JcApi()
    JyphoonApiSetup.setUp(binaryMessenger: registrar.messenger(), api: api)
    JCHandler.initialize(receiver: JyphoonReceiver.init(binaryMessenger: registrar.messenger()), api: api)
    registrar.addMethodCallDelegate(instance, channel: channel)
    let selfViewFactory = SelfViewFactory(messenger: registrar.messenger())
    registrar.register(selfViewFactory, withId: "self-view")
    let companionViewFactory = CompanionViewFactory(messenger: registrar.messenger())
    registrar.register(companionViewFactory, withId: "companion-view")
  }
}

private class JcApi: JyphoonApi {
  
  lazy var initialization = Initialization()
  lazy var userInfo = UserInfo()
  lazy var mediaChannel = MediaChannel()
  
  private var _isInited = false
  
  func clientState() -> Int32 {
    Int32(userInfo.clientState())
  }
    
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
  
  func call(confId: String, password: String, video: Bool, asr: Bool) -> Bool {
    mediaChannel.join(channelId: confId, password: password, video: video, asr: asr)
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
  
  func leave() -> Bool {
    mediaChannel.leave()
  }
  
  func otherVideo() -> Bool {
    mediaChannel.otherVideo()
  }
  
  func callStatus() -> String {
    mediaChannel.callStatus()
  }
  
  func switchCamera() {
    mediaChannel.switchCamera()
  }
}
