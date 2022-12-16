import 'package:flutter/material.dart';
import 'package:jc_example/screen/feed_screen.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:shared_preferences/shared_preferences.dart';

late final SharedPreferences prefs;

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  prefs = await SharedPreferences.getInstance();
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void initState() {
    // TODO: refactor camera request
    Permission.camera.request();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      builder: (context, child) {
        return GestureDetector(
          onTap: FocusManager.instance.primaryFocus?.unfocus,
          child: child,
        );
      },
      home: Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Juphoon Example SDK'),
        ),
        body: const FeedScreen(),
      ),
    );
  }
}
