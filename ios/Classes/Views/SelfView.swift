import Flutter
import UIKit
import JCSDKOC

class SelfViewFactory: NSObject, FlutterPlatformViewFactory {
    private var messenger: FlutterBinaryMessenger

    init(messenger: FlutterBinaryMessenger) {
        self.messenger = messenger
        super.init()
    }

    func create(
        withFrame frame: CGRect,
        viewIdentifier viewId: Int64,
        arguments args: Any?
    ) -> FlutterPlatformView {
        return SelfView(
            frame: frame,
            viewIdentifier: viewId,
            arguments: args,
            binaryMessenger: messenger)
    }
}

class SelfView: NSObject, FlutterPlatformView, SelfViewApi {
    private var _view: UIView
    
    private var canvas: JCMediaDeviceVideoCanvas? = nil
    
    func setSelfFrame(width: Double, height: Double) {
        canvas?.videoView.frame = CGRect(x: 0, y: 0, width: width, height: height)
    }

    init(
        frame: CGRect,
        viewIdentifier viewId: Int64,
        arguments args: Any?,
        binaryMessenger messenger: FlutterBinaryMessenger?
    ) {
        _view = UIView()
        super.init()
        SelfViewApiSetup.setUp(binaryMessenger: messenger!, api: self)
        // iOS views can be created here
        let participant = JCRoomUtils.selfParticipant!
        canvas = participant.startVideo(.fullScreen, pictureSize: .large)
        JCRoom.shared.mediaChannel.requestVideo(participant, pictureSize: .large)
        _view.addSubview(canvas!.videoView)
    }

    func view() -> UIView {
        return _view
    }
}
