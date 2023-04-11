import 'package:jc/generated/jyphoon_api.dart';

class CompanionController {
  factory CompanionController() => instance;

  CompanionController._() : _companionViewApi = CompanionViewApi();

  static final instance = CompanionController._();

  final CompanionViewApi _companionViewApi;

  void setCompanionFrame(double width, double height) {
    _companionViewApi.setCompanionFrame(width, height);
  }
}

class SelfController {
  factory SelfController() => instance;

  SelfController._() : _selfViewApi = SelfViewApi();

  static final instance = SelfController._();

  final SelfViewApi _selfViewApi;

  void setSelfFrame(double width, double height) {
    _selfViewApi.setSelfFrame(width, height);
  }
}
