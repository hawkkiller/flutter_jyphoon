import 'package:jc/src/controller/call.dart';
import 'package:jc/src/jc.dart';

class JcController extends JcReceiver {
  static final JcController _instance = JcController._();

  factory JcController() => _instance;

  JcController._() : call = JCCallImpl() {
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

/// An enum to determinate types of the activity
///
///
/// where 0 is call
/// and 1 is conference
enum CallType {
  call,
  conference;
}

enum VoiceStatus { started, ended }
