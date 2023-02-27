import 'package:jc/src/generated/jyphoon_api.dart';

class UiKitController {
  factory UiKitController() => instance;

  UiKitController._()
      : _companionViewApi = CompanionViewApi(),
        _selfViewApi = SelfViewApi();

  static final instance = UiKitController._();

  final CompanionViewApi _companionViewApi;
  final SelfViewApi _selfViewApi;

  void setCompanionFrame(double width, double height) {
    _companionViewApi.setCompanionFrame(width, height);
  }

  void setSelfFrame(double width, double height) {
    _selfViewApi.setSelfFrame(width, height);
  }
}
