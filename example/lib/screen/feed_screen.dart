import 'dart:async';
import 'dart:developer';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:jc/jc.dart';
import 'package:jc_example/main.dart';

/// {@template feed_screen}
/// FeedScreen widget
/// {@endtemplate}
class FeedScreen extends StatefulWidget {
  /// {@macro feed_screen}
  const FeedScreen({super.key});

  @override
  State<FeedScreen> createState() => _FeedScreenState();
}

class _FeedScreenState extends State<FeedScreen> {
  late final JCApi _jcApi;
  bool isInitialized = false;

  @override
  void initState() {
    super.initState();
    _jcApi = JCApi();
  }

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Column(
        children: [
          SDKField(
            label: 'AppKey',
            onTap: _jcApi.setAppKey,
          ),
          MaterialButton(
            color: Colors.deepPurple,
            onPressed: () async {
              await _jcApi.setAppKey('36731340dcf305c7c5234096');
              final res = await _jcApi.initialize();
              await _jcApi.setDisplayName('fdsdf');
              final res2 = await _jcApi.setAccountNumber(
                'llgrishakova_gmail_com',
              );
              await _jcApi.setServerAddress(
                'http:cn.router.justalkcloud.com:8080',
              );
              await _jcApi.setTimeout(5000);
              log('initialize: $res');
            },
            child: const Text('initialize'),
          ),
        ],
      ),
    );
  }
} // FeedScreen

class SDKField extends StatefulWidget {
  const SDKField({
    required this.label,
    this.isActive = true,
    this.onTap,
    this.controller,
    super.key,
  });

  final String label;
  final TextEditingController? controller;
  final FutureOr<void> Function(String)? onTap;
  final bool isActive;

  @override
  State<SDKField> createState() => _SDKFieldState();
}

class _SDKFieldState extends State<SDKField> {
  late final TextEditingController _controller;

  @override
  void initState() {
    super.initState();
    _controller = widget.controller ?? TextEditingController();
    _controller.text = prefs.getString(widget.label) ?? '';
  }

  @override
  void dispose() {
    super.dispose();
    if (widget.controller == null) _controller.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(8),
      child: Row(
        children: [
          Expanded(
            child: TextField(
              enabled: widget.isActive,
              controller: _controller,
              decoration: InputDecoration(
                border: const OutlineInputBorder(),
                labelText: widget.label,
              ),
            ),
          ),
          const SizedBox(width: 8),
          if (widget.onTap != null)
            _MaterialButton(
              color: CupertinoColors.systemYellow,
              enabled: widget.isActive,
              title: 'Set ${widget.label}',
              onTap: () {
                widget.onTap?.call(widget.controller?.text ?? '');
                prefs.setString(
                  widget.label,
                  _controller.text,
                );
                ScaffoldMessenger.of(context).showSnackBar(SnackBar(
                  content: Text('Set ${widget.label} to ${_controller.text}'),
                ));
              },
            ),
        ],
      ),
    );
  }
} // _SDKField

class _MaterialButton extends StatelessWidget {
  const _MaterialButton({
    required this.onTap,
    required this.enabled,
    required this.title,
    this.color = CupertinoColors.systemYellow,
  });

  final VoidCallback? onTap;
  final bool enabled;
  final String title;
  final Color color;

  @override
  Widget build(BuildContext context) => MaterialButton(
        onPressed: enabled ? onTap : null,
        color: color,
        disabledColor: CupertinoColors.inactiveGray,
        child: Text(title),
      );
} // _SdkButton