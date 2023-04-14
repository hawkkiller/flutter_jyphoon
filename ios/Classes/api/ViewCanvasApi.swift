//
//  ViewCanvasApi.swift
//  jc
//
//  Created by Михаил on 13.04.2023.
//

import Foundation
import JCSDKOC

protocol ViewCanvasApi {
    func startVideo(mode: JCMediaDeviceRender) -> UIView?
}

class SelfViewCanvasApi : ViewCanvasApi {
    private var oneToOne: SelfViewCanvasApiOneToOne = SelfViewCanvasApiOneToOne()
    private var group: SelfViewCanvasApiGroup = SelfViewCanvasApiGroup()

    func startVideo(mode: JCMediaDeviceRender) -> UIView? {
        switch (JCCallUtils.getCallType()) {
        case .oneToOne: return oneToOne.startVideo(mode: mode)
        case .group: return group.startVideo(mode: mode)
        case .none:
            return nil
        }
    }
}

class SelfViewCanvasApiOneToOne : ViewCanvasApi {
    func startVideo(mode: JCMediaDeviceRender) -> UIView? {
        return JCRoom.shared.call.getActiveCallItem()?.startSelfVideo(mode)?.videoView
    }
}

class SelfViewCanvasApiGroup : ViewCanvasApi {
    func startVideo(mode: JCMediaDeviceRender) -> UIView? {
        return JCRoom.shared.mediaChannel.selfParticipant?.startVideo(
            mode,
            pictureSize: .large
        )?.videoView
    }
}


class CompanionViewCanvasApi : ViewCanvasApi {
    private var oneToOne: CompanionCanvasApiOneToOne = CompanionCanvasApiOneToOne()
    private var group: CompanionViewCanvasApiGroup = CompanionViewCanvasApiGroup()

    func startVideo(mode: JCMediaDeviceRender) -> UIView? {
        switch (JCCallUtils.getCallType()) {
        case .oneToOne: return oneToOne.startVideo(mode: mode)
        case .group: return group.startVideo(mode: mode)
        case .none:
            return nil
        }
    }
}

class CompanionCanvasApiOneToOne {
    func startVideo(mode: JCMediaDeviceRender) -> UIView? {
        return JCRoom.shared.call.getActiveCallItem()?.startOtherVideo(mode)?.videoView
    }
}

class CompanionViewCanvasApiGroup {
    func startVideo(mode: JCMediaDeviceRender) -> UIView? {
        return JCCallUtils.otherParticipant?.startVideo(
            mode,
            pictureSize: .large
        )?.videoView
    }
}
