import JCSDKOC

import Foundation

class OneToOneCallApi : JyphoonCallApi {
    func call(destination: String, password: String, video: Bool, did: String, type: CallType) -> Bool {
        let callParam = JCCallParam(
            extraParam: video ? "video" : "audio",
            ticket: "\(did)_\(Date().timeIntervalSince1970)"
        )
        let res = JCRoom.shared.call.call(
            destination,
            video: video,
            callParam: callParam
        )
        if (res && video) {
            setVideo(video: true)
            setSpeaker(speaker: true)
        }
        return res
    }
    
    func callStatus() -> String {
        guard let activeCallItem = JCRoom.shared.call.getActiveCallItem() else {
            return "off"
        }
        
        switch (activeCallItem.state) {
        case .`init`, .pending, .connecting:
            return "waiting"
        case .talking, .ok:
            return "on"
        case .cancel, .canceled, .missed, .error:
            return "off"
        @unknown default:
            return "off"
        }
    }
    
    func audio() -> Bool {
        let audioStart = JCRoom.shared.mediaDevice.audioStart
        let uploadLocalAudio = JCRoom.shared.call.getActiveCallItem()?.microphoneMute ?? false
        return audioStart && uploadLocalAudio
    }
    
    func video() -> Bool {
        let videoStart = JCRoom.shared.mediaDevice.cameraOpen
        let uploadVideoStreamSelf = JCRoom.shared.call.getActiveCallItem()?.uploadVideoStreamSelf ?? false
        let video = JCRoom.shared.call.getActiveCallItem()?.video ?? false
        return videoStart && uploadVideoStreamSelf && video
    }
    
    func otherAudio() -> Bool {
        return !(JCRoom.shared.call.getActiveCallItem()?.otherAudioInterrupt ?? false)
    }
    
    func otherVideo() -> Bool {
        return !(JCRoom.shared.call.getActiveCallItem()?.uploadVideoStreamOther ?? false)
    }
    
    func leave() -> Bool {
        let call = JCRoom.shared.call.getActiveCallItem()
        if (call == nil) {
            return false
        }
        return JCRoom.shared.call.term(call!, reason: JCCallReason.none, description: "")
    }
    
    func switchCamera() {
        JCRoom.shared.mediaDevice.switchCamera()
    }
    
    func setVideo(video: Bool) {
        if (video) {
            JCRoom.shared.mediaDevice.startCamera()
        } else {
            JCRoom.shared.mediaDevice.stopCamera()
        }
    }
    
    func setAudio(audio: Bool) {
        if (audio) {
            JCRoom.shared.mediaDevice.startAudio()
        } else {
            JCRoom.shared.mediaDevice.stopAudio()
        }
    }
    
    func setSpeaker(speaker: Bool) {
        JCRoom.shared.mediaDevice.enableSpeaker(speaker)
    }
}
