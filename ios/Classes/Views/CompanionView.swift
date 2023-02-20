import Flutter
import UIKit
import JCSDKOC

class CompanionViewFactory: NSObject, FlutterPlatformViewFactory {
    private var messenger: FlutterBinaryMessenger
    
    public func createArgsCodec() -> FlutterMessageCodec & NSObjectProtocol {
          return FlutterStandardMessageCodec.sharedInstance()
    }

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

class CompanionView: NSObject, FlutterPlatformView, JyphoonViewApi {
    
    private var canvas: JCMediaDeviceVideoCanvas? = nil
    
    func setFrame(width: Double, height: Double) {
        canvas?.videoView.frame = CGRect(x: 0, y: 0, width: width, height: height)
    }
    
    private var _view: UIView

    init(
        frame: CGRect,
        viewIdentifier viewId: Int64,
        arguments args: Any?,
        binaryMessenger messenger: FlutterBinaryMessenger?
    ) {
        _view = UIView()
        super.init()
        JyphoonViewApiSetup.setUp(binaryMessenger: messenger!, api: self)
        // iOS views can be created here
        let participant = JCRoomUtils.otherParticipant!
        canvas = participant.startVideo(.fullContent, pictureSize: .large)
        JCRoom.shared.mediaChannel.requestVideo(participant, pictureSize: .large)
        _view.addSubview(canvas!.videoView)
        
    }

    func view() -> UIView {
        return _view
    }
}
