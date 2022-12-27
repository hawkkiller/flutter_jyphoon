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
      case 'CONFERENCE_JOIN':
        state
          ..updateVideoStatus()
          ..updateConfStatus();
        break;
      case 'CONFERENCE_LEAVE':
        state
          ..updateVideoStatus()
          ..updateConfStatus();
        break;
      case 'CONFERENCE_STOP':
        state
          ..updateVideoStatus()
          ..updateConfStatus();

        break;
      case 'CONFERENCE_PARTP_JOIN':
        state.updateVideoStatus();
        break;
      case 'CONFERENCE_PARTP_LEAVE':
        state
          ..updateVideoStatus()
          ..updateConfStatus();
        break;
      case 'CONFERENCE_PARTP_UPDATE':
        state
          ..updateVideoStatus()
          ..updateConfStatus();
        break;
      case 'CONFERENCE_PROP_CHANGE':
        state
          ..updateVideoStatus()
          ..updateVoiceStatus();
        break;
      case 'CONFERENCE_MESSAGE_RECEIVED':
        break;
    }
  }
}
