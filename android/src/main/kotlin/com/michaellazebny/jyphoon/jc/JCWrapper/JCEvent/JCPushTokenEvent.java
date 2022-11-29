package com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent;

public class JCPushTokenEvent extends JCEvent {

    public boolean result;
    public int pushType;
    public String token;

    public JCPushTokenEvent(boolean result, int pushType, String token) {
        super(EventType.PUSH_TOKEN);
        this.result = result;
        this.pushType = pushType;
        this.token = token;
    }
}
