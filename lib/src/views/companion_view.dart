import 'package:flutter/material.dart';

/// {@template remote_view}
/// RemoteView widget
/// {@endtemplate}
class CompanionView extends StatelessWidget {
  /// {@macro remote_view}
  const CompanionView({super.key});

  static const String viewType = 'remote-view';

  @override
  Widget build(BuildContext context) => const AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
      );
}
