import Foundation

class JCHandler {
    
    static let CONFERENCE_STOP = "CONFERENCE_STOP"
    static let CONFERENCE_JOIN = "CONFERENCE_JOIN"
    static let CONFERENCE_LEAVE = "CONFERENCE_LEAVE"
    static let CONFERENCE_PARTP_UPDATE = "CONFERENCE_PARTP_UPDATE"
    static let CONFERENCE_PARTP_LEAVE = "CONFERENCE_PARTP_LEAVE"
    static let CONFERENCE_PARTP_JOIN = "CONFERENCE_PARTP_JOIN"
    static let CONFERENCE_PROP_CHANGE = "CONFERENCE_PROP_CHANGE"
    static let CONFERENCE_MD_CHANNEL_STATE_CHANGE = "CONFERENCE_MD_CHANNEL_STATE_CHANGE"
    static let ON_AUDIO_OUTPUT_TYPE_CHANGE = "ON_AUDIO_OUTPUT_TYPE_CHANGE"
    static let ON_RENDER_RECEIVED = "ON_RENDER_RECEIVED"
    static let ON_RENDER_START = "ON_RENDER_START"
    static let ON_CALL_ITEM_ADD = "ON_CALL_ITEM_ADD"
    static let ON_CALL_ITEM_REMOVE = "ON_CALL_ITEM_REMOVE"
    static let ON_CALL_ITEM_UPDATE = "ON_CALL_ITEM_UPDATE"
    static let ON_CLIENT_STATE_CHANGE = "ON_CLIENT_STATE_CHANGE"
    
    static private var _instance: JCHandler?
    
    static var instance: JCHandler {
        get {
            return _instance!
        }
    }
    
    static func initialize(receiver: JyphoonReceiver,api: JyphoonApi) {
        _instance = JCHandler(receiver: receiver, api: api)
    }
    
    private let receiver: JyphoonReceiver
    private let api: JyphoonApi

    init(receiver: JyphoonReceiver, api: JyphoonApi) {
        self.receiver = receiver
        self.api = api
    }
    
    public func onEvent(event: String) {
        var dataProtoc = [String? : Any]()
        dataProtoc["video"] = api.video()
        dataProtoc["audio"] = api.audio()
        dataProtoc["otherAudio"] = api.otherAudio()
        dataProtoc["otherVideo"] = api.otherVideo()
        dataProtoc["callStatus"] = api.callStatus()
        dataProtoc["clientState"] = api.clientState()
        
        receiver.onEvent(event: event, data: dataProtoc) {}
    }
}
