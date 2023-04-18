import Foundation
import UIKit
import JCSDKOC.JCClient

@objcMembers
class JCRoom: NSObject, JCCallCallback {
    func onCallItemAdd(_ item: JCCallItem) {
        JCHandler.instance.onEvent(event: JCHandler.ON_CALL_ITEM_ADD)
    }
    
    func onCallItemRemove(_ item: JCCallItem, reason: JCCallReason, description: String?) {
        JCHandler.instance.onEvent(event: JCHandler.ON_CALL_ITEM_REMOVE)
    }
    
    func onCallItemUpdate(_ item: JCCallItem, changeParam: JCCallChangeParam?) {
        JCHandler.instance.onEvent(event: JCHandler.ON_CALL_ITEM_UPDATE)
    }
    
    func onMessageReceive(_ item: JCCallItem, type: String, content: String) {
        
    }
    
    func onMissedCallItem(_ item: JCCallItem) {
        
    }
    
    func onDtmfReceived(_ item: JCCallItem, value: JCCallDtmf) {
        
    }
    
    // 通过关键字 static 来保存实例引用
    private static let instance = JCRoom()
    public static var APP_KEY = ""
    public static var SERVER_ADDRESS = ""

    public static var shared : JCRoom {
        return self.instance
    }
    
    var client: JCClient {
        get {
            return _client!
        }
    }
    
    var mediaDevice: JCMediaDevice {
        get {
            return _mediaDevice!
        }
}
    
    var mediaChannel: JCMediaChannel {
        get {
            return _mediaChannel!
        }
    }
    
    var call: JCCall {
        get {
            return _jcCall!
        }
    }

    private var _client : JCClient?
    private var _mediaDevice : JCMediaDevice?
    private var _mediaChannel : JCMediaChannel?
    private var _jcCall: JCCall?
    
    private var _inited: Bool = false
    
    public var inited: Bool {
        get {
            _inited
        }
    }
    
    
    
    public func setDisplayName(name: String) {
        client.displayName = name
    }

    public func initialize() -> Bool {
        let appkey: String = UserDefaults.standard.string(forKey: "kAppkey") ?? JCRoom.APP_KEY
        let server: String = UserDefaults.standard.string(forKey: "kServer") ?? JCRoom.SERVER_ADDRESS

        let client = JCClient.create(appkey, callback: self, createParam: nil)
        let mediaDevice = JCMediaDevice.create(client!, callback: self)
        mediaDevice!.setCameraProperty(1280, height:720, framerate:24)
        let mediaChannel = JCMediaChannel.create(client!, mediaDevice: mediaDevice!, callback: self)
        JCNet.shared()?.add(self)
        
        _client = client
        _mediaDevice = mediaDevice
        _mediaChannel = mediaChannel
        _jcCall = JCCall.create(_client!, mediaDevice: _mediaDevice!, callback: self)
        
        UserDefaults.standard.setValue(appkey, forKey: "kAppkey")
        UserDefaults.standard.setValue(server, forKey: "kServer")
        UserDefaults.standard.synchronize()
        _inited = client != nil && mediaDevice != nil && mediaChannel != nil
        return _inited
    }
}

extension JCRoom: JCClientCallback {
    
    func onLogin(_ result: Bool, reason: JCClientReason) {
        
    }

    func onLogout(_ reason: JCClientReason) {
        
//        if reason != .netWork {
//            let app = UIApplication.shared.delegate as? AppDelegate
//            app?.changeToLogin()
//        }
    }

    func onClientStateChange(_ state: JCClientState, oldState: JCClientState) {
        JCHandler.instance.onEvent(event: JCHandler.ON_CLIENT_STATE_CHANGE)
    }
    
    func onOnlineMessageReceive(_ userId: String!, content: String!) {
        
    }
    
    func onOnlineMessageSend(_ operationId: Int32, result: Bool) {
        
    }
}

extension JCRoom: JCMediaDeviceCallback {

    func onCameraUpdate() {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_PROP_CHANGE)
    }

    func onAudioOutputTypeChange(_ audioOutputType: String!) {
        JCHandler.instance.onEvent(event: JCHandler.ON_AUDIO_OUTPUT_TYPE_CHANGE)
    }

    func onRenderReceived(_ canvas: JCMediaDeviceVideoCanvas!) {
        JCHandler.instance.onEvent(event: JCHandler.ON_RENDER_RECEIVED)
    }

    func onRenderStart(_ canvas: JCMediaDeviceVideoCanvas!) {
        JCHandler.instance.onEvent(event: JCHandler.ON_RENDER_START)
    }

    func onAudioInerruptAndResume(_ interrupt: Bool) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_PROP_CHANGE)
    }
}

extension JCRoom: JCMediaChannelCallback {

    func onParticipantVolumeChange(_ participant: JCMediaChannelParticipant!) {
        
    }
    
    func onMediaChannelStateChange(_ state: JCMediaChannelState, oldState: JCMediaChannelState) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_MD_CHANNEL_STATE_CHANGE)
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelStateChangeNotification), object: nil, userInfo: nil);
    }

    func onMediaChannelPropertyChange(_ changeParam: JCMediaChannelPropChangeParam!) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_PROP_CHANGE)
    }

    func onJoin(_ result: Bool, reason: JCMediaChannelReason, channelId: String!) {
        if result {
            JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_JOIN)
//            self.mediaDevice.enableSpeaker(true)
            NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnJoinSuccessNotification), object: nil, userInfo: nil);
        } else {
            NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnJoinFailNotification), object: nil, userInfo: nil);
        }
    }

    func onLeave(_ reason: JCMediaChannelReason, channelId: String!) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_LEAVE)
        if reason == .over {
            NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnLeaveOverNotification), object: nil, userInfo: nil);
        } else {
            NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnLeaveNotification), object: nil, userInfo: nil);
        }
    }

    func onStop(_ result: Bool, reason: JCMediaChannelReason) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_STOP)
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnStopNotification), object: nil, userInfo: nil);
    }

    func onQuery(_ operationId: Int32, result: Bool, reason: JCMediaChannelReason, queryInfo: JCMediaChannelQueryInfo!) {

    }

    func onParticipantJoin(_ participant: JCMediaChannelParticipant!) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_PARTP_JOIN)
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnParticipantJoinNotification), object: participant, userInfo: nil);
    }

    func onParticipantLeft(_ participant: JCMediaChannelParticipant!) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_PARTP_LEAVE)
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnParticipantLeftNotification), object: participant, userInfo: nil);
    }

    func onParticipantUpdate(_ participant: JCMediaChannelParticipant!, participantChangeParam: JCMediaChannelParticipantChangeParam!) {
        JCHandler.instance.onEvent(event: JCHandler.CONFERENCE_PARTP_UPDATE)
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: kMediaChannelOnParticipantUpdateNotification), object: nil, userInfo: nil);
    }

    func onMessageReceive(_ type: String!, content: String!, fromUserId: String!) {
    }

    func onInviteSipUserResult(_ operationId: Int32, result: Bool, reason: Int32) {

    }
}

extension JCRoom: JCNetCallback {
    func onNetChange(_ newNetType: JCNetType, oldNetType: JCNetType) {
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: kNetWorkNotification), object: nil, userInfo: nil);
    }
}
