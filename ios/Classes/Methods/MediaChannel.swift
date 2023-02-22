import Foundation
import JCSDKOC.JCMediaChannel

class MediaChannel {
    /// Must be called after initialization
    public func join(channelId: String, password: String) -> Bool {
        let joinParam = JCMediaChannelJoinParam()
        joinParam.capacity = 2
        joinParam.smooth = true
        joinParam.password = password
        joinParam.heartbeatTime = 20
        joinParam.heartbeatTimeout = 60
        joinParam.uriMode = false
        joinParam.framerate = 24
        joinParam.customVideoResolution = ""
        joinParam.videoRatio = 1.78
        JCRoom.shared.mediaDevice.enableSpeaker(true)
        JCRoom.shared.mediaChannel.enableUploadAudioStream(true)
        return JCRoom.shared.mediaChannel.join(channelId, joinParam: joinParam)
    }
    
    public func leave() -> Bool {
        JCRoom.shared.mediaChannel.leave()
    }
    
    public func audio() -> Bool {
        JCRoom.shared.mediaChannel.selfParticipant?.audio ?? false
    }
    
    public func video() -> Bool {
        JCRoom.shared.mediaChannel.selfParticipant?.video ?? false
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
    
    public func setVideo(video: Bool) {
        if (video) {
            JCRoom.shared.mediaDevice.startCameraVideo(.fullScreen)
        } else {
            JCRoom.shared.mediaDevice.stopAudio()
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
