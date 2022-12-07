import 'package:jc/src/jc.dart';

class JcController extends JcReceiver {
  JcController() {
    JcReceiver.setup(this);
  }

  @override
  void onCallStarted() {
    print('MISHA' + StackTrace.current.toString());
  }

  @override
  void onCallEnded() {
    print('MISHA' + StackTrace.current.toString());
  }

  @override
  void onVideoStarted() {
    print('MISHA' + StackTrace.current.toString());
  }

  @override
  void onVideoStopped() {
    print('MISHA' + StackTrace.current.toString());
  }
}
