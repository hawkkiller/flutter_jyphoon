//
//  ViewCanvasApi.swift
//  jc
//
//  Created by Михаил on 13.04.2023.
//

import Foundation
import JCSDKOC

protocol ViewCanvasApi {
    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas?
}

class SelfViewCanvasApi : ViewCanvasApi {
    private var oneToOne: SelfViewCanvasApiOneToOne = SelfViewCanvasApiOneToOne()
    private var group: SelfViewCanvasApiGroup = SelfViewCanvasApiGroup()

    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas? {
        switch (JCCallUtils.getCallType()) {
        case .oneToOne: return oneToOne.startVideo(mode: mode)
        case .group: return group.startVideo(mode: mode)
        case .none:
            return nil
        }
    }
}

class SelfViewCanvasApiOneToOne : ViewCanvasApi {
    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas? {
        return JCRoom.shared.call.getActiveCallItem()?.startSelfVideo(mode)
    }
}

class SelfViewCanvasApiGroup : ViewCanvasApi {
    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas? {
        let selfPart = JCRoomUtils.selfParticipant!
        let canvas = selfPart.startVideo(
            mode,
            pictureSize: .large
        )
        JCRoom.shared.mediaChannel.requestVideo(selfPart, pictureSize: .large)
        return canvas
    }
}

class CompanionViewCanvasApi : ViewCanvasApi {
    private var oneToOne: CompanionCanvasApiOneToOne = CompanionCanvasApiOneToOne()
    private var group: CompanionViewCanvasApiGroup = CompanionViewCanvasApiGroup()

    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas? {
        switch (JCCallUtils.getCallType()) {
        case .oneToOne: return oneToOne.startVideo(mode: mode)
        case .group: return group.startVideo(mode: mode)
        case .none:
            return nil
        }
    }
}

class CompanionCanvasApiOneToOne {
    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas? {
        return JCRoom.shared.call.getActiveCallItem()?.startOtherVideo(mode)
    }
}

class CompanionViewCanvasApiGroup {
    func startVideo(mode: JCMediaDeviceRender) -> JCMediaDeviceVideoCanvas? {
        return JCCallUtils.otherParticipant?.startVideo(
            mode,
            pictureSize: .large
        )
    }
}
