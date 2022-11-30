import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:jc/jc.dart';

void main() {
  JC platform = JC();
  const MethodChannel channel = MethodChannel('jc');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {});
}
