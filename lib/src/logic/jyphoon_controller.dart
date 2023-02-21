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
    await state.updateConfStatus();
    await state.updateVideoStatus();
  }
}
