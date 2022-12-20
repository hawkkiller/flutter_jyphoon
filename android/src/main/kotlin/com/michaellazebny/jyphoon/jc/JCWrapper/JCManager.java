package com.michaellazebny.jyphoon.jc.JCWrapper;

import android.content.Context;
import android.content.Intent;
import android.os.Build;

import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCAccountQueryStatusEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCCallDtmfReceivedEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCCallMessageEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCConfMessageEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCConfQueryEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCConfStopEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCJoinEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCLogEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCLoginEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCMessageEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCOnlineMessageReceiveEvent;
import com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent.JCStorageEvent;
import com.michaellazebny.jyphoon.jc.Tools.SPUtils;
import com.juphoon.cloud.JCAccount;
import com.juphoon.cloud.JCAccountCallback;
import com.juphoon.cloud.JCAccountContact;
import com.juphoon.cloud.JCAccountItem;
import com.juphoon.cloud.JCCall;
import com.juphoon.cloud.JCCallCallback;
import com.juphoon.cloud.JCCallItem;
import com.juphoon.cloud.JCClient;
import com.juphoon.cloud.JCClientCallback;
import com.juphoon.cloud.JCGroup;
import com.juphoon.cloud.JCGroupCallback;
import com.juphoon.cloud.JCGroupItem;
import com.juphoon.cloud.JCGroupMember;
import com.juphoon.cloud.JCMediaChannel;
import com.juphoon.cloud.JCMediaChannelCallback;
import com.juphoon.cloud.JCMediaChannelParticipant;
import com.juphoon.cloud.JCMediaChannelQueryInfo;
import com.juphoon.cloud.JCMediaDevice;
import com.juphoon.cloud.JCMediaDeviceCallback;
import com.juphoon.cloud.JCMediaDeviceVideoCanvas;
import com.juphoon.cloud.JCMessageChannel;
import com.juphoon.cloud.JCMessageChannelCallback;
import com.juphoon.cloud.JCMessageChannelConversation;
import com.juphoon.cloud.JCMessageChannelItem;
import com.juphoon.cloud.JCNet;
import com.juphoon.cloud.JCNetCallback;
import com.juphoon.cloud.JCPush;
import com.juphoon.cloud.JCStorage;
import com.juphoon.cloud.JCStorageCallback;
import com.juphoon.cloud.JCStorageItem;

import org.greenrobot.eventbus.EventBus;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * 本类主要是对Juphoon Cloud SDK 的简单封装
 */
public class JCManager implements JCClientCallback, JCCallCallback, JCMediaChannelCallback, JCMediaDeviceCallback,
        JCStorageCallback, JCGroupCallback, JCMessageChannelCallback, JCAccountCallback, JCNetCallback {


    public static JCManager getInstance() {
        return JCManagerHolder.INSTANCE;
    }

    private Context mContext;
    public JCClient client;
    public JCCall call;
    public JCMediaDevice mediaDevice;
    public JCMediaChannel mediaChannel;
    public JCMessageChannel messageChannel;
    public JCStorage storage;
    public JCGroup group;
    public JCPush push;
    public JCAccount account;
    public static String sAppkey;

    private List<String> mLogs;

    public boolean initialize(Context context) {
        if (isInited()) {
            return true;
        }
        mContext = context;

        JCClient.CreateParam createParam = new JCClient.CreateParam(context);
        createParam.sdkLogLevel = (int) SPUtils.get(context, "SdkLogLevel", JCClient.LOG_LEVEL_INFO);
        createParam.sdkInfoDir = (String) SPUtils.get(context, "SdkInfoDir", createParam.sdkInfoDir);
        createParam.sdkLogDir = (String) SPUtils.get(context, "SdkLogDir", createParam.sdkLogDir);
        createParam.isExtCamera = (boolean) SPUtils.get(context, "DeviceType", createParam.isExtCamera);
        client = JCClient.create(context, sAppkey, this, createParam);
        if (client.getState() == JCClient.STATE_NOT_INIT) {
            return false;
        }
        mediaDevice = JCMediaDevice.create(client, this);
        mediaChannel = JCMediaChannel.create(client, mediaDevice, this);
        call = JCCall.create(client, mediaDevice, this);
        messageChannel = JCMessageChannel.create(client, this);
        storage = JCStorage.create(client, this);
        push = JCPush.create(client);
        group = JCGroup.create(client, this);
        account = JCAccount.create(this);
        JCNet.getInstance().addCallback(this);

        mLogs = new ArrayList<>();
        CustomAudioManager.getInstance().init(mContext);

        addLog("*initialize");

        return true;
    }

    public void uninitialize() {
        CustomAudioManager.getInstance().destroy();
        if (client != null) {
            addLog("*uninitialize");
            JCNet.getInstance().removeCallback(this);
            JCPush.destroy();
            JCStorage.destroy();
            JCMessageChannel.destroy();
            JCCall.destroy();
            JCMediaChannel.destroy();
            JCMediaDevice.destroy();
            JCClient.destroy();
            JCAccount.destroy();
            push = null;
            storage = null;
            messageChannel = null;
            call = null;
            mediaChannel = null;
            mediaDevice = null;
            client = null;
            account = null;
        }
    }

    public boolean isInited() {
        return client != null;
    }

    public String getNowLogs() {
        StringBuilder builder = new StringBuilder();
        for (String log : mLogs) {
            builder.append(log).append("\n");
        }
        return builder.toString();
    }

    private void addLog(String log) {
        if (mLogs.size() >= 100) {
            mLogs.remove(0);
        }
        mLogs.add(log);
        EventBus.getDefault().post(new JCLogEvent(log));
    }

    @Override
    public void onLogin(boolean result, @JCClient.ClientReason int reason) {
        EventBus.getDefault().post(new JCLoginEvent(result, reason));
        addLog(String.format(Locale.getDefault(), "*onLogin result=%b reason=%d", result, reason));
    }

    @Override
    public void onLogout(@JCClient.ClientReason int reason) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.LOGOUT));
        addLog(String.format(Locale.getDefault(), "*onLogout reason=%d", reason));
    }

    @Override
    public void onClientStateChange(@JCClient.ClientState int state, @JCClient.ClientState int oldState) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CLIENT_STATE_CHANGE));
        addLog(String.format(Locale.getDefault(), "*onClientStateChange state=%d oldState=%d", state, oldState));
    }

    @Override
    public void onOnlineMessageSendResult(int operationId, boolean result) {
        addLog(String.format(Locale.getDefault(), "*onOnlineMessageSendResult operationId = %d result = %b", operationId, result));
    }

    @Override
    public void onOnlineMessageReceive(String userId, String content) {
        EventBus.getDefault().post(new JCOnlineMessageReceiveEvent(userId, content));
        addLog(String.format(Locale.getDefault(), "*onOnlineMessageReceive userId: %s content: %s", userId, content));
    }

    @Override
    public void onCallItemAdd(JCCallItem item) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_ADD));
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_UI));
        addLog(String.format(Locale.getDefault(), "*onCallItemAdd %s", item.getUserId()));
    }

    @Override
    public void onCallItemRemove(JCCallItem item, @JCCall.CallReason int reason, String description) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_REMOVE));
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_UI));
        addLog(String.format(Locale.getDefault(), "*onCallItemRemove %s reason:%d description:%s", item.getUserId(), reason, description == null ? "" : description));
        dealForgroundService();
    }

    @Override
    public void onCallItemUpdate(JCCallItem item, JCCallItem.ChangeParam changeParam) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_UPDATE));
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_UI));
        addLog(String.format(Locale.getDefault(), "*onCallItemUpdate %s", item.getUserId()));
        dealForgroundService();
    }

    @Override
    public void onMessageReceive(String type, String content, JCCallItem callItem) {
        EventBus.getDefault().post(new JCCallMessageEvent(type, content, callItem));
        addLog(String.format(Locale.getDefault(), "*onMessageReceive %s type:%s content:%s", callItem.getUserId(), type, content));
    }

    @Override
    public void onMessageReceive(String type, String content, String fromUserId) {
        EventBus.getDefault().post(new JCConfMessageEvent(type, content, fromUserId));
        addLog(String.format(Locale.getDefault(), "*onMessageReceive type:%s content:%s fromUserId:%s", type, content, fromUserId));
    }

    @Override
    public void onMissedCallItem(JCCallItem jcCallItem) {
        addLog(String.format(Locale.getDefault(), "*onMissedCallItem %s", jcCallItem.getUserId()));
    }

    @Override
    public void onDtmfReceived(JCCallItem jcCallItem, @JCCall.DtmfValue int value) {
        EventBus.getDefault().post(new JCCallDtmfReceivedEvent(jcCallItem, value));
        addLog(String.format(Locale.getDefault(), "*onDtmfReceived %s value:%d", jcCallItem.getUserId(), value));
    }

    @Override
    public void onMediaChannelStateChange(@JCMediaChannel.MediaChannelState int state, @JCMediaChannel.MediaChannelState int oldState) {
        addLog(String.format(Locale.getDefault(), "*onMediaChannelStateChange state:%d oldState=%d", state, oldState));
    }

    @Override
    public void onMediaChannelPropertyChange(JCMediaChannel.PropChangeParam propChangeParam) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_PROP_CHANGE));
        addLog("onMediaChannelPropertyChange");
    }

    @Override
    public void onJoin(boolean result, @JCMediaChannel.MediaChannelReason int reason, String channelId) {
        EventBus.getDefault().post(new JCJoinEvent(result, reason, channelId));
        addLog(String.format(Locale.getDefault(), "*onJoin result:%b reason:%d channelId:%s", result, reason, channelId == null ? "" : channelId));
        dealForgroundService();
    }

    @Override
    public void onLeave(@JCMediaChannel.MediaChannelReason int reason, String channelId) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_LEAVE));
        addLog(String.format(Locale.getDefault(), "*onLeave reason:%d channelId:%s", reason, channelId));
        dealForgroundService();
    }

    @Override
    public void onStop(boolean result, @JCMediaChannel.MediaChannelReason int reason) {
        JCConfStopEvent event = new JCConfStopEvent(result, reason);
        EventBus.getDefault().post(event);
        addLog(String.format(Locale.getDefault(), "*onStop reason:%d", reason));
    }

    @Override
    public void onQuery(int operationId, boolean result, @JCMediaChannel.MediaChannelReason int reason, JCMediaChannelQueryInfo queryInfo) {
        EventBus.getDefault().post(new JCConfQueryEvent(operationId, result, reason, queryInfo));
        addLog(String.format(Locale.getDefault(), "*onQuery operationId:%d result:%b reason:%d", operationId, result, reason));
    }

    @Override
    public void onParticipantJoin(JCMediaChannelParticipant participant) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_PARTP_JOIN));
        addLog(String.format(Locale.getDefault(), "*onParticipantJoin %s", participant.getUserId()));
    }

    @Override
    public void onParticipantLeft(JCMediaChannelParticipant participant) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_PARTP_LEAVE));
        addLog(String.format(Locale.getDefault(), "*onParticipantLeft %s", participant.getUserId()));
    }

    @Override
    public void onParticipantUpdate(JCMediaChannelParticipant participant, JCMediaChannelParticipant.ChangeParam changeParam) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_PARTP_UPDATE));
        addLog(String.format(Locale.getDefault(), "*onParticipantUpdate %s", participant.getUserId()));
    }


    @Override
    public void onInviteSipUserResult(int operationId, boolean result, int reason) {
        addLog(String.format(Locale.getDefault(), "*onInviteSipUserResult operationId:%d result:%b reason:%d", operationId, result, reason));
    }

    @Override
    public void onParticipantVolumeChange(JCMediaChannelParticipant jcMediaChannelParticipant) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_PARTP_UPDATE));
        addLog(String.format(Locale.getDefault(), "*onParticipantVolumeChange %s", jcMediaChannelParticipant.getUserId()));
    }

    @Override
    public void onCameraUpdate() {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CAMERA_UPDATE));
        addLog("*onCameraUpdate");
    }

    @Override
    public void onAudioOutputTypeChange(int audioRouteType) {
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CALL_UI));
        EventBus.getDefault().post(new JCEvent(JCEvent.EventType.CONFERENCE_PROP_CHANGE));
        addLog(String.format(Locale.getDefault(), "*onAudioOutputTypeChange %d", audioRouteType));
    }

    @Override
    public void onRenderReceived(JCMediaDeviceVideoCanvas jcMediaDeviceVideoCanvas) {
        addLog(String.format(Locale.getDefault(), "*onRenderReceived videoSource:%s", jcMediaDeviceVideoCanvas.getVideoSource()));
    }

    @Override
    public void onRenderStart(JCMediaDeviceVideoCanvas jcMediaDeviceVideoCanvas) {
        addLog(String.format(Locale.getDefault(), "*onRenderStart videoSource:%s", jcMediaDeviceVideoCanvas.getVideoSource()));
    }

    @Override
    public void onVideoError(JCMediaDeviceVideoCanvas jcMediaDeviceVideoCanvas) {
        addLog(String.format(Locale.getDefault(), "*onVideoError videoSource:%s", jcMediaDeviceVideoCanvas.getVideoSource()));
    }

    @Override
    public void onNeedKeyFrame() {
        addLog("onNeedKeyFrame");
    }

    @Override
    public void onMessageSendUpdate(JCMessageChannelItem jcMessageChannelItem) {
        EventBus.getDefault().post(new JCMessageEvent(true, jcMessageChannelItem));
    }

    @Override
    public void onMessageRecv(JCMessageChannelItem jcMessageChannelItem) {
        EventBus.getDefault().post(new JCMessageEvent(false, jcMessageChannelItem));
    }

    @Override
    public void onFileUpdate(JCStorageItem jcStorageItem) {
        EventBus.getDefault().post(new JCStorageEvent(jcStorageItem));
    }

    @Override
    public void onFileResult(JCStorageItem jcStorageItem) {
        EventBus.getDefault().post(new JCStorageEvent(jcStorageItem));
    }

    @Override
    public void onQueryServerUidResult(int operationId, boolean result, Map<String, String> resultMap) {

    }

    @Override
    public void onQueryUserIdResult(int operationId, boolean result, Map<String, String> resultMap) {

    }

    @Override
    public void onRefreshContacts(int operationId, boolean result, List<JCAccountContact> contacts, long updateTime, boolean fullUpdate) {

    }

    @Override
    public void onDealContact(int operationId, boolean result, int reason) {

    }

    @Override
    public void onContactsChange(List<JCAccountContact> contactList) {

    }

    @Override
    public void onSetContactDnd(int operationId, boolean result, int reason) {

    }

    @Override
    public void onFetchGroups(int operationId, boolean result, int reason, List<JCGroupItem> groups, long updateTime, long baseTime, boolean fullUpdated) {

    }

    @Override
    public void onFetchGroupInfo(int operationId, boolean result, int reason, JCGroupItem groupItem, List<JCGroupMember> members, long updateTime, long baseTime, boolean fullUpdated) {

    }

    @Override
    public void onGroupListChange(List<JCGroupItem> groupList, long updateTime, long baseTime) {

    }

    @Override
    public void onGroupInfoChange(String groupId, List<JCGroupMember> memberList, long updateTime, long baseTime) {

    }

    @Override
    public void onCreateGroup(int operationId, boolean result, int reason, JCGroupItem groupItem, long updateTime, long baseTime) {

    }

    @Override
    public void onLeave(int operationId, boolean result, int reason, String groupId, long updateTime, long baseTime) {

    }

    @Override
    public void onDealMembers(int operationId, boolean result, int reason, String groupId) {

    }

    @Override
    public void onUpdateGroupComment(int operationId, boolean result, int reason, String groupId) {

    }

    @Override
    public void onSetGroupDnd(int operationId, boolean result, int reason, String groupId) {

    }

    @Override
    public void onMessageListRecv(List<JCMessageChannelItem> messageList) {

    }

    @Override
    public void onRefreshConversation(int operationId, boolean result, List<JCMessageChannelConversation> jcMessageChannelConversationList, int reason, long updateTime, String refreshServerUid) {

    }

    @Override
    public void onFetchMessageResult(int operationId, boolean result, int reason) {

    }

    @Override
    public void onMarkReadResult(int operationId, boolean result, int reason) {

    }

    @Override
    public void onMarkRecvResult(int operationId, boolean result, int reason) {

    }

    @Override
    public void onReceiveMarkRead(String uid, long serverMessageId) {

    }

    @Override
    public void onReceiveMarkRecv(String uid, long serverMessageId) {

    }

    @Override
    public void onDrawBackMessageResult(int operationId, boolean result, int reason) {

    }

    @Override
    public void onUpdateGroup(int operationId, boolean result, @JCGroup.Reason int reason, String groupId) {
    }

    @Override
    public void onDissolve(int operationId, boolean result, @JCGroup.Reason int reason, String groupId) {
    }

    @Override
    public void onQueryUserStatusResult(int i, boolean result, List<JCAccountItem> list) {
        JCAccountQueryStatusEvent event = new JCAccountQueryStatusEvent(result, list);
        EventBus.getDefault().post(event);
    }

    @Override
    public void onNetChange(int newNetType, int oldNetType) {
        addLog(String.format(Locale.getDefault(), "*onNetChange %d->%d", oldNetType, newNetType));
    }

    private void dealForgroundService() {
        boolean hasTalkingCall = false;
        for (JCCallItem item : call.getCallItems()) {
            if (item.getState() == JCCall.STATE_TALKING) {
                hasTalkingCall = true;
                break;
            }
        }
        if (!hasTalkingCall && mediaChannel.getState() != JCMediaChannel.STATE_JOINED) {
            if (ForegroundService.serviceIsLive) {
                mContext.stopService(new Intent(mContext, ForegroundService.class));
            }
        } else {
            if (!ForegroundService.serviceIsLive) {
                Intent intent = new Intent(mContext, ForegroundService.class);
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                    mContext.startForegroundService(intent);
                } else {
                    mContext.startService(intent);
                }
            }
        }
    }

    private static final class JCManagerHolder {
        private static final JCManager INSTANCE = new JCManager();
    }
}
