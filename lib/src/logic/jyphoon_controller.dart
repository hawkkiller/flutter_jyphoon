import 'package:jc/src/generated/jyphoon_api.dart';
import 'package:jc/src/logic/jyphoon_state.dart';

abstract class JyphoonController {
  JyphoonState get state;
}

class JyphoonControllerImpl implements JyphoonReceiver, JyphoonController {
  static final JyphoonControllerImpl _instance = JyphoonControllerImpl._();

  factory JyphoonControllerImpl() => _instance;

  JyphoonControllerImpl._() : state = InnerJyphoonStateImpl() {
    JyphoonReceiver.setup(this);
  }

  @override
  final InnerJyphoonState state;

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
        state
          ..updateVideoStatus()
          ..updateConfStatus();
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
