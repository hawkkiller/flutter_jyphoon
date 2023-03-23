import Foundation
import JCSDKOC.JCMediaChannel

class MediaChannel {
    private let jc = JCRoom.shared
    /// Must be called after initialization
    public func join(channelId: String, password: String, video: Bool, asr: Bool) -> Bool {
        let joinParam = JCMediaChannelJoinParam()
        joinParam.capacity = 2
        jc.mediaDevice.enableSpeaker(true)
        jc.mediaChannel.enableUploadAudioStream(true)
        jc.mediaChannel.enableUploadVideoStream(true)
        let userID = channelId.components(separatedBy: "_").last
        let jcCallParam = JCCallParam(extraParam: video ? "video" : "audio", ticket: channelId)
        let res = asr ?
        jc.call.call(userID!, video: video, callParam: jcCallParam) :
        jc.mediaChannel.join(channelId, joinParam: joinParam)
        if (res && video) {
            let videoRes = setVideo(video: true)
            print("VIDEORES: \(videoRes)")
        }
        return res
    }
    
    public func leave() -> Bool {
        return JCRoom.shared.mediaChannel.leave()
    }
    
    public func audio() -> Bool {
        let selfAudio = jc.mediaChannel.selfParticipant?.audio ?? false
        let audioStart = jc.mediaDevice.audioStart
        let uploadLocalAudio = jc.mediaChannel.uploadLocalAudio
        return selfAudio && audioStart && uploadLocalAudio
    }
    
    public func video() -> Bool {
        let selfVideo = jc.mediaChannel.selfParticipant?.video ?? false
        let cameraOpen = jc.mediaDevice.cameraOpen
        let uploadLocalVideo = jc.mediaChannel.uploadLocalVideo
        return selfVideo && cameraOpen && uploadLocalVideo
    }
    
    public func otherAudio() -> Bool {
        JCRoomUtils.otherParticipant?.audio ?? false
    }
    
    public func otherVideo() -> Bool {
        JCRoomUtils.otherParticipant?.video ?? false
    }
    
    public func setAudio(audio: Bool) {
        JCRoom.shared.mediaChannel.enableUploadAudioStream(audio)
    }
    
    public func setVideo(video: Bool) -> Bool {
        JCRoom.shared.mediaChannel.enableUploadVideoStream(video)
        if (video) {
            return JCRoom.shared.mediaDevice.startCamera()
        } else {
            return JCRoom.shared.mediaDevice.stopCamera()
        }
    }
    
    public func setSpeaker(speaker: Bool) {
        JCRoom.shared.mediaDevice.enableSpeaker(speaker)
    }
    
    public func confStatus() -> String {
        let participants = JCRoom.shared.mediaChannel.participants
        if (participants.isEmpty) {
            return "off"
        }
        if (participants.count == 1) {
            return "waiting"
        }
        return "on"
    }
    
    public func switchCamera() {
        JCRoom.shared.mediaDevice.switchCamera()
    }
}
