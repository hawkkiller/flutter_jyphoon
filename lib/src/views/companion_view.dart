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
  Widget build(BuildContext context) => const _CompanionView();
}

class _CompanionView extends StatefulWidget {
  const _CompanionView();

  @override
  State<_CompanionView> createState() => _CompanionViewState();
}

class _CompanionViewState extends State<_CompanionView> {
  late final CompanionController _controller;

  @override
  void initState() {
    _controller = CompanionController();
    super.initState();
  }

  @override
  Widget build(BuildContext context) => LayoutBuilder(
        builder: (context, constraints) {
          _controller.setCompanionFrame(
            constraints.maxWidth,
            constraints.maxHeight,
          );
          if (Platform.isIOS) {
            return UiKitView(
              viewType: CompanionView.viewType,
              layoutDirection: TextDirection.ltr,
              onPlatformViewCreated: (_) => _controller.setCompanionFrame(
                constraints.maxWidth,
                constraints.maxHeight,
              ),
              creationParamsCodec: const StandardMessageCodec(),
            );
          }
          if (Platform.isAndroid) {
            return AndroidView(
              viewType: CompanionView.viewType,
              layoutDirection: TextDirection.ltr,
              onPlatformViewCreated: (_) => _controller.setCompanionFrame(
                constraints.maxWidth,
                constraints.maxHeight,
              ),
              creationParamsCodec: const StandardMessageCodec(),
            );
          }
          throw UnsupportedError('Unsupported platform');
        },
      );
}
