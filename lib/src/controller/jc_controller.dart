import 'package:jc/src/controller/call.dart';
import 'package:jc/src/jc.dart';

class JcController extends JcReceiver {
  JcController() : call = JCCallImpl() {
    JcReceiver.setup(this);
  }

  final JCCall call;

  @override
  void onVideoChange(bool value, bool self) => call.onVideoChange(
        value: value,
        self: self,
      );

  @override
  void onVoiceChange(bool value, bool self) {}
}

enum VideoStatus {
  on,
  off;

  static VideoStatus fromBool(bool value) {
    if (value) {
      return VideoStatus.on;
    }
    return VideoStatus.off;
  }
}

enum VoiceStatus { started, ended }
