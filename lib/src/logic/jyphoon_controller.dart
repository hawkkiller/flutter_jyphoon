import 'package:jc/generated/jyphoon_api.dart';
import 'package:jc/src/logic/jyphoon_state.dart';
import 'package:jc/src/model/call_state.dart';

abstract class JyphoonController {
  JyphoonState get state;
}

class JyphoonControllerImpl implements JyphoonReceiver, JyphoonController {
  factory JyphoonControllerImpl() => _instance;

  JyphoonControllerImpl._() : state = InnerJyphoonStateImpl() {
    JyphoonReceiver.setup(this);
  }
  static final JyphoonControllerImpl _instance = JyphoonControllerImpl._();

  @override
  final InnerJyphoonState state;

  @override
  void onEvent(String event, Map<String?, Object?> map) {
    final callState = CallState.fromJson(map);
    state.updateState(callState);
  }
}
