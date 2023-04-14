import JCSDKOC

class JCCallUtils {

    static var otherParticipant: JCMediaChannelParticipant? {
        let jc = JCRoom.shared
        guard let selfParticipant = jc.mediaChannel.selfParticipant else { return nil }
        var otherParticipant: JCMediaChannelParticipant? = nil
        let participants = jc.mediaChannel.participants
        for participant in participants where participant as? JCMediaChannelParticipant != selfParticipant {
            otherParticipant = participant as? JCMediaChannelParticipant
            break
        }
        return otherParticipant
    }
    
    static func getCallType() -> CallType? {
        let jc = JCRoom.shared
        if !(jc.call.callItems?.isEmpty ?? true) {
            return .oneToOne
        } else if jc.mediaChannel.selfParticipant != nil {
            return .group
        } else {
            return nil
        }
    }
}
