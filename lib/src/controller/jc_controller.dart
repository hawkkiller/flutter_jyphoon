import 'package:jc/src/controller/state.dart';
import 'package:jc/src/jc.dart';

class JcController extends JcReceiver {
  static final JcController _instance = JcController._();

  factory JcController() => _instance;

  JcController._() : state = JCStateImpl() {
    JcReceiver.setup(this);
  }

  final JCState state;

  @override
  void onEvent(String event) {
    switch (event) {
      case '':
        break;
    }
  }
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
