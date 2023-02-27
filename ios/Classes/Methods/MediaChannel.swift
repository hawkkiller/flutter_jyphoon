import Foundation
import JCSDKOC.JCMediaChannel

class MediaChannel {
    private let jc = JCRoom.shared
    /// Must be called after initialization
    public func join(channelId: String, password: String, video: Bool) -> Bool {
        let joinParam = JCMediaChannelJoinParam()
        joinParam.capacity = 2
        jc.mediaDevice.enableSpeaker(true)
        jc.mediaChannel.enableUploadAudioStream(true)
        jc.mediaChannel.enableUploadVideoStream(true)
        let res = jc.mediaChannel.join(channelId, joinParam: joinParam)
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
        let audio = (jc.mediaChannel.selfParticipant?.audio ?? false) && jc.mediaDevice.audioStart && jc.mediaChannel.uploadLocalAudio
        return audio
    }
    
    public func video() -> Bool {
        let video = (jc.mediaChannel.selfParticipant?.video ?? false) && jc.mediaDevice.cameraOpen && jc.mediaChannel.uploadLocalVideo
        return video
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
