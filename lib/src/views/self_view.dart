import 'package:flutter/material.dart';

/// {@template self_view}
/// SelfView widget
/// {@endtemplate}
class SelfView extends StatelessWidget {
  /// {@macro self_view}
  const SelfView({super.key});

  static const String viewType = 'local-view';

  @override
  Widget build(BuildContext context) => const AndroidView(
        viewType: viewType,
        layoutDirection: TextDirection.ltr,
      );
}