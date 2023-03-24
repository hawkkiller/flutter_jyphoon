import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:jc/src/views/controller.dart';

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
    if (Platform.isIOS) return const _CompanionUiKitView();
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

class _CompanionUiKitView extends StatefulWidget {
  const _CompanionUiKitView();

  @override
  State<_CompanionUiKitView> createState() => _CompanionUiKitViewState();
}

class _CompanionUiKitViewState extends State<_CompanionUiKitView> {
  late final UiKitController _controller;

  @override
  void initState() {
    _controller = UiKitController();
    super.initState();
  }

  @override
  Widget build(BuildContext context) => LayoutBuilder(
        builder: (context, constraints) {
          _controller.setCompanionFrame(
            constraints.maxWidth,
            constraints.maxHeight,
          );
          return UiKitView(
            viewType: CompanionView.viewType,
            layoutDirection: TextDirection.ltr,
            onPlatformViewCreated: (_) => _controller.setCompanionFrame(
              constraints.maxWidth,
              constraints.maxHeight,
            ),
            creationParamsCodec: const StandardMessageCodec(),
          );
        },
      );
}
