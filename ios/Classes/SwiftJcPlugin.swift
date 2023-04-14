import Flutter
import UIKit
import JCSDKOC.JCClient

public class SwiftJcPlugin: NSObject, FlutterPlugin {
  
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "jc", binaryMessenger: registrar.messenger())
    let instance = SwiftJcPlugin()
    let api = JyphoonApi()
    registrar.addMethodCallDelegate(instance, channel: channel)
    JyphoonCallApiSetup.setUp(binaryMessenger: registrar.messenger(), api: api)
    JCHandler.initialize(receiver: JyphoonReceiver.init(binaryMessenger: registrar.messenger()), api: api)
    
    let selfViewFactory = CallViewFactory(messenger: registrar.messenger(), api: CompanionViewCanvasApi())
    registrar.register(selfViewFactory, withId: "self-view")
      
    let companionViewFactory = CallViewFactory(messenger: registrar.messenger(), api: CompanionViewCanvasApi())
    registrar.register(companionViewFactory, withId: "companion-view")
  }
}

class JyphoonApi : JyphoonCallApi, JyphoonInitializationApi {
    private let oneToOne = OneToOneCallApi()
    private let group = GroupCallApi()
    private let stub = JyphoonCallApiStub()
    private let initialization = InitializationApi()
    
    func call(destination: String, password: String, video: Bool, type: CallType) -> Bool {
        callApi.call(destination: destination, password: password, video: video, type: type)
    }
    
    func callStatus() -> String {
        callApi.callStatus()
    }
    
    func audio() -> Bool {
        callApi.audio()
    }
    
    func video() -> Bool {
        callApi.video()
    }
    
    func otherAudio() -> Bool {
        callApi.otherAudio()
    }
    
    func otherVideo() -> Bool {
        callApi.otherVideo()
    }
    
    func leave() -> Bool {
        callApi.leave()
    }
    
    func switchCamera() {
        callApi.switchCamera()
    }
    
    func setVideo(video: Bool) {
        callApi.setVideo(video: video)
    }
    
    func setAudio(audio: Bool) {
        callApi.setAudio(audio: audio)
    }
    
    func setSpeaker(speaker: Bool) {
        callApi.setSpeaker(speaker: speaker)
    }
    
    func isInited() -> Bool {
        initialization.isInited()
    }
    
    func initialize() -> Bool {
        initialization.initialize()
    }
    
    func setAppKey(appKey: String) {
        initialization.setAppKey(appKey: appKey)
    }
    
    func setDisplayName(displayName: String) {
        initialization.setDisplayName(displayName: displayName)
    }
    
    func setAccountNumber(accountNumber: String) -> Bool {
        initialization.setAccountNumber(accountNumber: accountNumber)
    }
    
    func setTimeout(timeout: Int32) {
        initialization.setTimeout(timeout: timeout)
    }
    
    func setServerAddress(serverAddress: String) {
        initialization.setServerAddress(serverAddress: serverAddress)
    }
    
    func getCurrentUserId() -> String? {
        initialization.getCurrentUserId()
    }
    
    func clientState() -> Int32 {
        initialization.clientState()
    }
    
    private var callApi: JyphoonCallApi {
        get {
            switch (JCCallUtils.getCallType()) {
            case .group: return group
            case .oneToOne: return oneToOne
            case .none: return stub
            }
        }
    }
}

private class JyphoonCallApiStub : JyphoonCallApi {
    func call(destination: String, password: String, video: Bool, type: CallType) -> Bool {
        false
    }
    
    func callStatus() -> String {
        "off"
    }
    
    func audio() -> Bool {
        false
    }
    
    func video() -> Bool {
        false
    }
    
    func otherAudio() -> Bool {
        false
    }
    
    func otherVideo() -> Bool {
        false
    }
    
    func leave() -> Bool {
        false
    }
    
    func switchCamera() {
        
    }
    
    func setVideo(video: Bool) {
        
    }
    
    func setAudio(audio: Bool) {
        
    }
    
    func setSpeaker(speaker: Bool) {
        
    }
    
    
}
