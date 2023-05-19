import 'package:flutter/material.dart';
import 'package:jc/generated/jyphoon_api.dart';
import 'package:jc/jyphoon.dart';

/// {@template conference_screen}
/// ConferenceScreen widget
/// {@endtemplate}
class ConferenceScreen extends StatefulWidget {
  /// {@macro conference_screen}
  const ConferenceScreen({super.key});

  @override
  State<ConferenceScreen> createState() => _ConferenceScreenState();
} // ConferenceScreen

/// State for widget ConferenceScreen
class _ConferenceScreenState extends State<ConferenceScreen> {
  late final TextEditingController _sessionId;
  late final JyphoonSDK _sdk;

  /// true -> 2
  /// false -> 1
  bool type = false;

  @override
  void initState() {
    super.initState();
    _sdk = JyphoonSDK();

    _sessionId = TextEditingController();
  }

  @override
  Widget build(BuildContext context) => Scaffold(
        body: CustomScrollView(
          slivers: [
            const SliverAppBar(
              title: Text('Conference'),
              centerTitle: true,
            ),
            SliverList(
              delegate: SliverChildListDelegate(
                [
                  TextField(
                    controller: _sessionId,
                    decoration: const InputDecoration(
                      labelText: 'Session ID',
                    ),
                  ),
                  ElevatedButton(
                    onPressed: () async {
                      await _sdk.call(
                        _sessionId.text,
                        video: true,
                        type: type ? CallType.oneToOne : CallType.group,
                      );
                    },
                    child: const Text('Join'),
                  ),
                  ElevatedButton(
                    onPressed: () async {
                      await _sdk.leave();
                    },
                    child: const Text('Leave'),
                  ),
                  StreamBuilder<AudioStatus>(
                    stream: _sdk.state.selfAudio,
                    builder: (context, snapshot) {
                      if (snapshot.data == null) {
                        return const Text('data is null');
                      }
                      return TextButton(
                        onPressed: () async {
                          await _sdk.setAudio(audio: !snapshot.data!.value);
                        },
                        child: Text(
                          snapshot.data!.value ? 'Mute' : 'Unmute',
                        ),
                      );
                    },
                  ),
                  StreamBuilder<SpeakerStatus>(
                    stream: _sdk.state.selfSpeaker,
                    builder: (context, snapshot) {
                      if (snapshot.data == null) {
                        return const Text('data is null');
                      }
                      return TextButton(
                        onPressed: () async {
                          await _sdk.setSpeaker(speaker: !snapshot.data!.value);
                        },
                        child: Text(
                          snapshot.data!.value ? 'off speaker' : 'on speaker',
                        ),
                      );
                    },
                  ),
                  StreamBuilder<VideoStatus>(
                    stream: _sdk.state.selfVideo,
                    builder: (context, snapshot) {
                      if (snapshot.data == null) {
                        return const Text('data is null');
                      }
                      return TextButton(
                        onPressed: () {
                          _sdk.setVideo(video: !snapshot.data!.value);
                        },
                        child: Text(
                          snapshot.data == VideoStatus.on ? 'Turn video off' : 'Turn video on',
                        ),
                      );
                    },
                  ),
                  Text('Call type $type'),
                  Switch.adaptive(
                    value: type,
                    onChanged: (t) {
                      setState(() {
                        type = !type;
                      });
                    },
                  ),
                  StreamBuilder<CallStatus>(
                    stream: _sdk.state.call,
                    builder: (context, snapshot) {
                      return Center(
                        child: Text(
                          snapshot.data.toString(),
                        ),
                      );
                    },
                  ),
                  Container(
                    height: 500,
                    width: double.infinity,
                    decoration: BoxDecoration(
                      color: Colors.grey[200],
                    ),
                    child: Stack(
                      children: [
                        Badge(
                          label: const Text('Self'),
                          child: DecoratedBox(
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: Colors.grey[300]!,
                                width: 5,
                              ),
                            ),
                            child: StreamBuilder(
                              stream: _sdk.state.selfVideo,
                              builder: (context, snapshot) {
                                if (snapshot.data != VideoStatus.on) {
                                  return const SizedBox.expand();
                                }
                                return StreamBuilder<CallStatus>(
                                  stream: _sdk.state.call,
                                  builder: (context, snapshot) {
                                    return const SelfView();
                                  },
                                );
                              },
                            ),
                          ),
                        ),
                        Positioned(
                          top: 0,
                          right: 0,
                          width: 100,
                          height: 100,
                          child: Badge(
                            label: const Text('Companion'),
                            child: DecoratedBox(
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: Colors.grey[300]!,
                                  width: 5,
                                ),
                              ),
                              child: StreamBuilder(
                                stream: _sdk.state.companionVideo,
                                builder: (context, snapshot) {
                                  if (snapshot.data != VideoStatus.on) {
                                    return const SizedBox.expand();
                                  }
                                  return const CompanionView();
                                },
                              ),
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      );
}
