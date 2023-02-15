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
        _view.frame = frame
        let canvas = JCRoomUtils.otherParticipant?.startVideo(.fullScreen, pictureSize: .min)
        if (canvas?.videoView != nil) {
            _view.addSubview(canvas!.videoView)
        }
        
    }

    func view() -> UIView {
        return _view
    }
}
