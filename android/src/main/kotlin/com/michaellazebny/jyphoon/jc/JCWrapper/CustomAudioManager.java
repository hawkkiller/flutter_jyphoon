package com.michaellazebny.jyphoon.jc.JCWrapper;

import android.content.Context;

import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCEvent;
import com.michaellazebny.jyphoon.jc.Toos.JCAudioTrack;
import com.juphoon.cloud.JCAudioFrameCallback;
import com.juphoon.cloud.JCCall;
import com.juphoon.cloud.JCMediaChannel;
import com.juphoon.cloud.JCMediaDevice;
import com.juphoon.cloud.JCVideoFrameCallback;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

import static com.michaellazebny.jyphoon.jc.Toos.CustomAudioInputUtil.encodeValue;
import static com.michaellazebny.jyphoon.jc.Toos.CustomAudioInputUtil.getByteArrayFromFilePath;
import static com.michaellazebny.jyphoon.jc.Toos.CustomAudioInputUtil.saveAssetFile;

/**
 * @author juphoon
 * @since 2021/2/3
 */
public class CustomAudioManager implements JCAudioFrameCallback, JCVideoFrameCallback {

    private Context mContext;
    private JCAudioTrack mAudioTrack = new JCAudioTrack();
    private Thread mCustomAudioInputThread;
    private Thread mCustomVideoInputThread;

    public static CustomAudioManager getInstance() {
        return CustomAudioManagerHolder.INSTANCE;
    }

    public void init(Context context) {
        mContext = context;
        EventBus.getDefault().register(this);
    }

    public void destroy() {
        EventBus.getDefault().unregister(this);
        if (JCManager.getInstance().isInited()) {
            JCManager.getInstance().mediaDevice.setAudioFrameCallback(null);
            JCManager.getInstance().mediaDevice.setVideoFrameCallback(null);
        }
        stopInputCustomAudio();
        mAudioTrack.stopAudio();
        stopInputVideoFileFrame();
    }

    public void setAudioFrameCallback(boolean register) {
        if (register) {
            JCManager.getInstance().mediaDevice.setAudioFrameCallback(this);
        } else {
            JCManager.getInstance().mediaDevice.setAudioFrameCallback(null);
        }
    }

    public void setVideoFrameCallback(boolean register) {
        if (register) {
            JCManager.getInstance().mediaDevice.setVideoFrameCallback(this);
        } else {
            JCManager.getInstance().mediaDevice.setVideoFrameCallback(null);
        }
    }

    public void enableVideoFileFrame(boolean enable) {
        if (enable) {
            JCManager.getInstance().mediaDevice.startVideoFile();
            if (JCManager.getInstance().call.getActiveCallItem() != null || JCManager.getInstance().mediaChannel.getState() == JCMediaChannel.STATE_JOINED) {
                startInputCustomVideo();
            }
        } else {
            stopInputVideoFileFrame();
            JCManager.getInstance().mediaDevice.stopVideoFile();
            if (JCManager.getInstance().call.getActiveCallItem() != null || JCManager.getInstance().mediaChannel.getState() == JCMediaChannel.STATE_JOINED) {
                JCManager.getInstance().mediaDevice.startCamera();
            }
        }
    }

    @Subscribe
    public void onEvent(JCEvent event) {
        if (event.getEventType() == JCEvent.EventType.CALL_UPDATE) {
            if ((JCManager.getInstance().call.getActiveCallItem() != null && JCManager.getInstance().call.getActiveCallItem().getState() == JCCall.STATE_CONNECTING)) {
                if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioInputDevice) {
                    startInputCustomAudio();
                }
                if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioOutputDevice) {
                    mAudioTrack.playAudio(16000, 1);
                }
                if (JCManager.getInstance().mediaDevice.isVideoFileOpen()) {
                    startInputCustomVideo();
                }
            }
        } else if (event.getEventType() == JCEvent.EventType.CALL_REMOVE) {
            if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioInputDevice) {
                stopInputCustomAudio();
            }
            if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioOutputDevice) {
                mAudioTrack.stopAudio();
            }
            stopInputVideoFileFrame();
        } else if (event.getEventType() == JCEvent.EventType.CONFERENCE_JOIN) {
            if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioInputDevice) {
                startInputCustomAudio();
            }
            if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioOutputDevice) {
                mAudioTrack.playAudio(16000, 1);
            }
            if (JCManager.getInstance().mediaDevice.isVideoFileOpen()) {
                startInputCustomVideo();
            }
        } else if (event.getEventType() == JCEvent.EventType.CONFERENCE_LEAVE || event.getEventType() == JCEvent.EventType.CONFERENCE_STOP) {
            if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioInputDevice) {
                stopInputCustomAudio();
            }
            if (!JCManager.getInstance().mediaDevice.audioParam.autoStartAudioOutputDevice) {
                mAudioTrack.stopAudio();
            }
            stopInputVideoFileFrame();
        }
    }

    private void startInputCustomVideo() {
        if (mCustomVideoInputThread == null) {
            mCustomVideoInputThread = new Thread(() -> {
                try {
                    String customVideoPath = mContext.getFilesDir().getAbsolutePath() + "/video.h264";
                    File file = new File(customVideoPath);
                    if (!file.exists()) {
                        saveAssetFile(mContext, "video.h264", customVideoPath);
                    }
                    byte[] buffer = getByteArrayFromFilePath(mContext.getFilesDir().getAbsolutePath() + "/" + "video.h264");
                    if (buffer == null) {
                        return;
                    }
                    int len = buffer.length;
                    List<Integer> framesIndex = new ArrayList<>();
                    List<Integer> framesType = new ArrayList<>();
                    for (int i = 0; i < len; i++) {
                        if (buffer[i] == 0x00 && buffer[i + 1] == 0x00 && buffer[i + 2] == 0x00 && buffer[i + 3] == 0x01) {
                            framesIndex.add(i);
                            if (buffer[i + 4] == 0x67) {
                                framesType.add(1);
                            } else {
                                framesType.add(0);
                            }
                        }
                    }
                    int index = 0;
                    boolean keyFrame;
                    int length;
                    byte[] data;
                    if (framesIndex.size() < 1) {
                        return;
                    }
                    while (JCManager.getInstance().mediaDevice.isVideoFileOpen()) {
                        if (index >= framesIndex.size() - 1) {
                            index = 0;
                        }
                        if (framesType.get(index) == 1) {
                            keyFrame = true;
                            length = framesIndex.get(index + 3) - framesIndex.get(index);
                            data = new byte[length];
                            System.arraycopy(buffer, framesIndex.get(index), data, 0, length);
                            index = index + 3;
                        } else {
                            keyFrame = false;
                            length = framesIndex.get(index + 1) - framesIndex.get(index);
                            data = new byte[length];
                            System.arraycopy(buffer, framesIndex.get(index), data, 0, length);
                            index = index + 1;
                        }
                        JCManager.getInstance().mediaDevice.setVideoFileFrame(data, JCManager.getInstance().call.getActiveCallItem() == null ? JCMediaDevice.H264_SVC : JCMediaDevice.H264, 640, 360, 0, 0, keyFrame);
                        try {
                            Thread.sleep(50);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

            });
        }
        if (!mCustomVideoInputThread.isAlive()) {
            mCustomVideoInputThread.start();
        }
    }

    private void stopInputVideoFileFrame() {
        if (mCustomVideoInputThread != null) {
            mCustomVideoInputThread.interrupt();
            mCustomVideoInputThread = null;
        }
    }

    private void startInputCustomAudio() {
        if (mCustomAudioInputThread == null) {
            mCustomAudioInputThread = new Thread(() -> {
                try {
                    String customAudioPath = mContext.getFilesDir().getAbsolutePath() + "/customAudio.pcm";
                    File file = new File(customAudioPath);
                    if (!file.exists()) {
                        saveAssetFile(mContext, "customAudio.pcm", customAudioPath);
                    }
                    ByteBuffer byteBuffer = encodeValue(getByteArrayFromFilePath(mContext.getFilesDir().getAbsolutePath() + "/" + "customAudio.pcm"));
                    int len = byteBuffer.capacity();
                    int packetLen = 32 * 1024;
                    int packetNum = len / packetLen;
                    ByteBuffer[] buffers = new ByteBuffer[packetNum];
                    for (int num = 0; num < packetNum; num++) {
                        byte[] bytes = new byte[packetLen];
                        byteBuffer.get(bytes, 0, packetLen);
                        ByteBuffer buffer = encodeValue(bytes);
                        buffers[num] = buffer;
                    }
                    int num = 0;
                    while ((JCManager.getInstance().call != null && JCManager.getInstance().call.getActiveCallItem() != null) ||
                            (JCManager.getInstance().mediaChannel != null && JCManager.getInstance().mediaChannel.getState() == JCMediaChannel.STATE_JOINED)) {
                        JCManager.getInstance().mediaDevice.inputCustomAudioData(16000, 1, buffers[num], 0, 0, 0);
                        num = (++num) % packetNum;
                        try {
                            Thread.sleep(1000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }
        if (!mCustomAudioInputThread.isAlive()) {
            mCustomAudioInputThread.start();
        }
    }

    private void stopInputCustomAudio() {
        if (mCustomAudioInputThread != null) {
            mCustomAudioInputThread.interrupt();
            mCustomAudioInputThread = null;
        }
    }

    @Override
    public void onAudioInputFrame(String inputId, int sampleRateHz, int channels, ByteBuffer data, int playDelayMS, int recDelayMS, int clockDrift) {

    }

    @Override
    public void onAudioOutputFrame(String outputId, int sampleRateHz, int channels, ByteBuffer data) {

    }

    @Override
    public void onVideoCaptureFrame(String captureId, int face, int imageAngle, int captureOrient, int[] widthHeight, ByteBuffer data) {

    }

    @Override
    public void onVideoRenderFrame(String renderId, int sourceType, int angle, int mirror, int width, int height, ByteBuffer data, int timeStampMs) {

    }

    private static final class CustomAudioManagerHolder {
        private static final CustomAudioManager INSTANCE = new CustomAudioManager();
    }
}
