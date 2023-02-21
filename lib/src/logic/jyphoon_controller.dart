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
  Future<void> onEvent(String event) async {
    switch (event) {
      case 'CONFERENCE_JOIN':
      case 'CONFERENCE_LEAVE':
      case 'CONFERENCE_STOP':
      case 'CONFERENCE_PARTP_JOIN':
      case 'CONFERENCE_PARTP_LEAVE':
      case 'CONFERENCE_PARTP_UPDATE':
      case 'CONFERENCE_PROP_CHANGE':
      case 'CONFERENCE_MESSAGE_RECEIVED':
        await state.updateConfStatus();
    }
  }
}
