import Foundation

class JCHandler {
    
    static let CONFERENCE_STOP = "CONFERENCE_STOP"
    static let CONFERENCE_JOIN = "CONFERENCE_JOIN"
    static let CONFERENCE_PARTP_UPDATE = "CONFERENCE_PARTP_UPDATE"
    static let CONFERENCE_PARTP_LEAVE = "CONFERENCE_PARTP_LEAVE"
    static let CONFERENCE_PARTP_JOIN = "CONFERENCE_PARTP_JOIN"
    static let CONFERENCE_PROP_CHANGE = "CONFERENCE_PROP_CHANGE"
    
    
    static private var _instance: JCHandler?
    
    static var instance: JCHandler {
        get {
            return _instance!
        }
    }
    
    static func initialize(receiver: JyphoonReceiver) {
        _instance = JCHandler(receiver: receiver)
    }
    
    private let receiver: JyphoonReceiver

    init(receiver: JyphoonReceiver) {
        self.receiver = receiver
    }
    
    public func onEvent(event: String) {
        receiver.onEvent(event: event) {
            
        }
    }
}
