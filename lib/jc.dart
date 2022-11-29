
import 'jc_platform_interface.dart';

class Jc {
  Future<String?> getPlatformVersion() {
    return JcPlatform.instance.getPlatformVersion();
  }
}
