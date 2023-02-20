import Flutter
import UIKit

class CompanionViewFactory: NSObject, FlutterPlatformViewFactory {
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
        return CompanionView(
            frame: frame,
            viewIdentifier: viewId,
            arguments: args,
            binaryMessenger: messenger)
    }
}

class CompanionView: NSObject, FlutterPlatformView {
    private var _view: UIView

    init(
        frame: CGRect,
        viewIdentifier viewId: Int64,
        arguments args: Any?,
        binaryMessenger messenger: FlutterBinaryMessenger?
    ) {
        _view = UIView()
        super.init()
        // iOS views can be created here
        
        let participant = JCRoomUtils.otherParticipant!
        let canvas = participant.startVideo(.fullContent, pictureSize: .large)
        JCRoom.shared.mediaChannel.requestVideo(participant, pictureSize: .large)
        _view.addSubview(canvas!.videoView)
        canvas?.videoView.frame = CGRect(x: 0, y: 0, width: 100, height: 200)
    }

    func view() -> UIView {
        return _view
    }
}
