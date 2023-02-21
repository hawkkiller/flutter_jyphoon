import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:jc/src/generated/jyphoon_api.dart';

/// {@template companion_view}
/// CompanionView widget
/// Display this widget to show the companion view in the call.
/// {@endtemplate}
@immutable
class CompanionView extends StatelessWidget {
  /// {@macro companion_view}
  const CompanionView({super.key});

  static const String viewType = 'companion-view';

  @override
  Widget build(BuildContext context) {
    if (Platform.isIOS) return const _UiKitView();
    if (Platform.isAndroid) {
      return const AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
        creationParamsCodec: StandardMessageCodec(),
      );
    }
    throw UnsupportedError('Unsupported platform');
  }
}

class _UiKitView extends StatefulWidget {
  const _UiKitView();

  @override
  State<_UiKitView> createState() => __UiKitViewState();
}

class __UiKitViewState extends State<_UiKitView> {
  late final _UiKitController _controller;

  @override
  void initState() {
    _controller = _UiKitController();
    super.initState();
  }

  void _setFrame(double width, double height) => _controller.setFrame(
        width,
        height,
      );

  @override
  Widget build(BuildContext context) {
    return LayoutBuilder(builder: (context, constraints) {
      _setFrame(constraints.maxWidth, constraints.maxHeight);
      return UiKitView(
        viewType: CompanionView.viewType,
        layoutDirection: TextDirection.ltr,
        onPlatformViewCreated: (_) => _setFrame(
          constraints.maxWidth,
          constraints.maxHeight,
        ),
        creationParamsCodec: const StandardMessageCodec(),
      );
    });
  }
}

class _UiKitController {
  _UiKitController() : _jyphoonViewApi = JyphoonViewApi();

  final JyphoonViewApi _jyphoonViewApi;

  void setFrame(double width, double height) {
    _jyphoonViewApi.setFrame(width, height);
  }
}
