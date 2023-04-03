package com.michaellazebny.jyphoon.jc.jcWrapper.JCEvent;

public class JCEvent {

    public enum EventType {
        Exit,
        LOGIN,
        LOGOUT,
        CLIENT_STATE_CHANGE,
        ONLINE_MESSAGE_RECEIVE,
        CALL_ADD,
        CALL_UPDATE,
        CALL_REMOVE,
        CALL_MESSAGE_RECEIVED,
        CALL_UI,
        CALL_DTMF_RECEIVED,
        CONFERENCE_JOIN,
        CONFERENCE_LEAVE,
        CONFERENCE_STOP,
        CONFERENCE_QUERY,
        CONFERENCE_PARTP_JOIN,
        CONFERENCE_PARTP_LEAVE,
        CONFERENCE_PARTP_UPDATE,
        CONFERENCE_PROP_CHANGE,
        CONFERENCE_MESSAGE_RECEIVED,
        MESSAGE,
        STORAGE,
        GROUP_LIST,
        GROUP_INFO,
        ACCOUNT_QUERY_USER_STATUS,
        PUSH_TOKEN,
        JCLOG,
        CAMERA_UPDATE
    }

    private EventType mEventType;

    public JCEvent(EventType eventType) {
        this.mEventType = eventType;
    }

    public EventType getEventType() {
        return mEventType;
    }

}

