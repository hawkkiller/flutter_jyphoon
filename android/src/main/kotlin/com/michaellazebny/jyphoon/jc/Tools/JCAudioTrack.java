package com.michaellazebny.jyphoon.jc.tools;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

import com.michaellazebny.jyphoon.jc.JCWrapper.JCManager;
import com.justalk.cloud.zmf.ZmfAudio;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * @author juphoon
 * @since 2021/2/3
 */
public class JCAudioTrack {

    private static final String TAG = "JCAudioTrack";

    private AudioTrack _track;
    private ByteBuffer _spkBuffer;
    private byte[] _spkTmpBuf;
    private Thread _spkThread;
    private int _spkRateHz;
    private int _spkChannel;
    private boolean _playing;

    public void playAudio(int iSampleRateHz, int iChannels) {
        if (_playing) {
            return;
        }
        if (iSampleRateHz <= 0)
            iSampleRateHz = 16000;
        if (iChannels <= 0)
            iChannels = 1;
        else if (iChannels > 2)
            iChannels = 2;
        int chnCfg = (iChannels == 2) ? AudioFormat.CHANNEL_OUT_STEREO : AudioFormat.CHANNEL_OUT_MONO;

        int minPlayBufSize = AudioTrack.getMinBufferSize(iSampleRateHz,
                chnCfg, AudioFormat.ENCODING_PCM_16BIT);
        if (minPlayBufSize < 0) {
            if (iSampleRateHz != 44100 || chnCfg != AudioFormat.CHANNEL_OUT_MONO) {
                iSampleRateHz = 44100;
                chnCfg = AudioFormat.CHANNEL_OUT_MONO;
                iChannels = 1;
                minPlayBufSize = AudioTrack.getMinBufferSize(iSampleRateHz,
                        chnCfg, AudioFormat.ENCODING_PCM_16BIT);
            }
            if (minPlayBufSize < 0) {
                ZmfAudio.logError("AudioTrack.getMinBufferSize failed: " + minPlayBufSize + ", freq:" + iSampleRateHz + ",channel:" + iChannels);
            }
        }

        _track = new AudioTrack(AudioManager.STREAM_VOICE_CALL, iSampleRateHz,
                chnCfg, AudioFormat.ENCODING_PCM_16BIT,
                minPlayBufSize, AudioTrack.MODE_STREAM);

        _spkRateHz = _track.getSampleRate();
        _spkChannel = iChannels;
        _track.play();
        _spkBuffer = ByteBuffer.allocateDirect(_spkRateHz / 100 * 2 * _spkChannel).order(ByteOrder.nativeOrder());
        if (!_spkBuffer.hasArray()) {
            if (_spkTmpBuf == null || _spkTmpBuf.length < _spkBuffer.capacity())
                _spkTmpBuf = new byte[_spkBuffer.capacity()];
        }
        _playing = true;
        _spkThread = new Thread(() -> {
            AudioTrack track = _track;
            try {
                android.os.Process.setThreadPriority(
                        android.os.Process.THREAD_PRIORITY_URGENT_AUDIO);
            } catch (Exception e) {
                ZmfAudio.logError("Set play thread priority failed: " + e.getMessage());
            }
            boolean writing = true;
            while (_playing && writing) {
                JCManager.getInstance().mediaDevice.getAudioOutputData(_spkRateHz, _spkChannel, _spkBuffer);
                try {
                    int written = 0;
                    while (writing && _playing && written < _spkBuffer.capacity()) {
                        int ret;
                        if (_spkBuffer.hasArray()) {
                            ret = track.write(_spkBuffer.array(), written + _spkBuffer.arrayOffset(), _spkBuffer.capacity() - written);
                        } else {
                            _spkBuffer.rewind();
                            _spkBuffer.get(_spkTmpBuf);
                            ret = track.write(_spkTmpBuf, written, _spkBuffer.capacity() - written);
                        }

                        switch (ret) {
                            case AudioTrack.ERROR_INVALID_OPERATION:
                                writing = false;
                                ZmfAudio.logError("Invalid AudioTrack.write()");
                                break;
                            case AudioTrack.ERROR_BAD_VALUE:
                                writing = false;
                                ZmfAudio.logError("Bad arguments to AudioTrack.write()");
                                break;
                            default:
                                written += ret;
                                break;
                        }
                    }
                } catch (Exception e) {
                    writing = false;
                    ZmfAudio.logError("AudioTrack write failed: " + e.getMessage());
                }
            }
            if (track.getState() != AudioTrack.STATE_UNINITIALIZED
                    && track.getPlayState() != AudioTrack.PLAYSTATE_STOPPED) {
                try {
                    track.stop();
                } catch (IllegalStateException e) {
                    ZmfAudio.logError("AudioTrack stop failed: " + e.getMessage());
                }
            }
            track.release();
        });
        _spkThread.start();
    }

    public void stopAudio() {
        if (_track == null)
            return;
        _playing = false;
        try {
            _spkThread.join();
        } catch (InterruptedException e) {
            ZmfAudio.logError("AudioTrack Thread join failed: " + e.getMessage());
            return;
        }
        _spkThread = null;
        _track = null;
    }

}
