import 'package:flutter/material.dart';
import 'package:jc/jc.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _jcPlugin = JC();

  @override
  void initState() {
    super.initState();
    init();
  }

  Future<void> init() async {
    await _jcPlugin.setAppKey('36731340dcf305c7c5234096');
    await _jcPlugin.initialize();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
      ),
    );
  }
}
