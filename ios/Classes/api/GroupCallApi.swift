import JCSDKOC

import Foundation

class GroupCallApi : JyphoonCallApi {
    private let jc = JCRoom.shared
    
    func call(destination: String, password: String, video: Bool, type: CallType) -> Bool {
        let joinParam = JCMediaChannelJoinParam()
        joinParam.capacity = 2
        let res = jc.mediaChannel.join(destination, joinParam: joinParam)
        if (res) {
            jc.mediaChannel.enableUploadAudioStream(true)
            
            if (video) {
                setVideo(video: true)
                setSpeaker(speaker: true)
            }
        }
        
        return res
    }
    
    func callStatus() -> String {
        let participants = JCRoom.shared.mediaChannel.participants
        if (participants.isEmpty) {
            return "off"
        }
        if (participants.count == 1) {
            return "waiting"
        }
        return "on"
    }
    
    func audio() -> Bool {
        let selfAudio = jc.mediaChannel.selfParticipant?.audio ?? false
        let audioStart = jc.mediaDevice.audioStart
        let uploadLocalAudio = jc.mediaChannel.uploadLocalAudio
        return selfAudio && audioStart && uploadLocalAudio
    }
    
    func video() -> Bool {
        let selfVideo = jc.mediaChannel.selfParticipant?.video ?? false
        let cameraOpen = jc.mediaDevice.cameraOpen
        let uploadLocalVideo = jc.mediaChannel.uploadLocalVideo
        return selfVideo && cameraOpen && uploadLocalVideo
    }
    
    func otherAudio() -> Bool {
        JCRoomUtils.otherParticipant?.audio ?? false
    }
    
    func otherVideo() -> Bool {
        JCRoomUtils.otherParticipant?.video ?? false
    }
    
    func leave() -> Bool {
        return JCRoom.shared.mediaChannel.leave()
    }
    
    func switchCamera() {
        JCRoom.shared.mediaDevice.switchCamera()
    }
    
    func setVideo(video: Bool) {
        JCRoom.shared.mediaChannel.enableUploadVideoStream(video)
        if (video) {
            JCRoom.shared.mediaDevice.startCamera()
        } else {
            JCRoom.shared.mediaDevice.stopCamera()
        }
    }
    
    func setAudio(audio: Bool) {
        JCRoom.shared.mediaChannel.enableUploadAudioStream(audio)
    }
    
    func setSpeaker(speaker: Bool) {
        JCRoom.shared.mediaDevice.enableSpeaker(speaker)
    }
}
