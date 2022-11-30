import 'package:flutter_test/flutter_test.dart';
import 'package:jc/jc.dart';
import 'package:jc/jc_platform_interface.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockJcPlatform extends JcPlatform with MockPlatformInterfaceMixin {}

void main() {
  final JcPlatform initialPlatform = JcPlatform.instance;

  test('$JC is the default instance', () {
    expect(initialPlatform, isInstanceOf<JC>());
  });
}
