import 'package:jc/src/jc.dart';

class JcController extends JcReceiver {
  JcController() {
    JcReceiver.setup(this);
  }

  @override
  void onCallStarted() {}

  @override
  void onCallEnded() {}

  @override
  void onVideoStarted() {}

  @override
  void onVideoStopped() {}
}
