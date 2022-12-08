import 'dart:developer';

import 'package:flutter/material.dart';
import 'package:jc/jc.dart';
import 'package:permission_handler/permission_handler.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _jcPlugin = JCApi();
  final controller = JcController();
  bool started = false;

  @override
  void initState() {
    Permission.camera.request();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: SingleChildScrollView(
          child: Column(
            children: [
              ElevatedButton(
                onPressed: () async {
                  final res = await _jcPlugin.isInited();
                  log('isInited: $res');
                },
                child: const Text('isInited'),
              ),
              ElevatedButton(
                onPressed: () async {
                  setState(() {
                    started = !started;
                  });
                },
                child: const Text('setState'),
              ),
              ElevatedButton(
                onPressed: () {
                  _jcPlugin.stopSelfVideo();
                },
                child: const Text('stop self video'),
              ),
              ElevatedButton(
                onPressed: () {
                  _jcPlugin.startSelfVideo();
                },
                child: const Text('start self video'),
              ),
              ElevatedButton(
                onPressed: () {
                  _jcPlugin.answerCall();
                },
                child: const Text('answer'),
              ),
              ElevatedButton(
                onPressed: () async {
                  await _jcPlugin.setAppKey('36731340dcf305c7c5234096');
                  final res = await _jcPlugin.initialize();
                  await _jcPlugin.setDisplayName('Flutter');
                  final res2 = await _jcPlugin.setAccountNumber('31');
                  await _jcPlugin.setServerAddress(
                    'http:cn.router.justalkcloud.com:8080',
                  );
                  await _jcPlugin.setTimeout(5000);
                  log('initialize: $res');
                },
                child: const Text('initialize'),
              ),
              // start call
              ElevatedButton(
                onPressed: () async {
                  final started = await _jcPlugin.startCall(
                    '353101510211658',
                    true,
                    "0151021165_1670491158",
                  );
                  setState(() {
                    this.started = started;
                  });
                },
                child: const Text('startCall'),
              ),
              if (started)
                const SizedBox(
                  height: 250,
                  width: 250,
                  child: LocalView(),
                ),
              if (started)
                const SizedBox(
                  height: 250,
                  width: 250,
                  child: RemoteView(),
                ),
            ],
          ),
        ),
      ),
    );
  }
}
