import Flutter
import UIKit
import JCSDKOC

class CallViewFactory: NSObject, FlutterPlatformViewFactory {
    private var messenger: FlutterBinaryMessenger
    private var api: ViewCanvasApi
    
    public func createArgsCodec() -> FlutterMessageCodec & NSObjectProtocol {
          return FlutterStandardMessageCodec.sharedInstance()
    }

    init(messenger: FlutterBinaryMessenger, api: ViewCanvasApi) {
        self.messenger = messenger
        self.api = api
        super.init()
    }

    func create(
        withFrame frame: CGRect,
        viewIdentifier viewId: Int64,
        arguments args: Any?
    ) -> FlutterPlatformView {
        return CallView(binaryMessenger: messenger, api: api)
    }
}

class CallView: NSObject, FlutterPlatformView, CompanionViewApi, SelfViewApi {
    func setSelfFrame(width: Double, height: Double) {
        canvas?.videoView.frame = CGRect(x: 0, y: 0, width: width, height: height)
    }
    
    private var canvas: JCMediaDeviceVideoCanvas? = nil
    
    func setCompanionFrame(width: Double, height: Double) {
        canvas?.videoView.frame = CGRect(x: 0, y: 0, width: width, height: height)
    }
    
    private var _view: UIView

    init(
        binaryMessenger messenger: FlutterBinaryMessenger?,
        api: ViewCanvasApi
    ) {
        _view = UIView()
        super.init()
        if (api is CompanionViewCanvasApi) {
            CompanionViewApiSetup.setUp(binaryMessenger: messenger!, api: self)
        } else if (api is SelfViewCanvasApi) {
            SelfViewApiSetup.setUp(binaryMessenger: messenger!, api: self)
        }
        
        // iOS views can be created here
        let participant = JCRoomUtils.otherParticipant!
        canvas = participant.startVideo(.fullScreen, pictureSize: .large)
        JCRoom.shared.mediaChannel.requestVideo(participant, pictureSize: .large)
        _view.addSubview(canvas!.videoView)
    }

    func view() -> UIView {
        return _view
    }
}
