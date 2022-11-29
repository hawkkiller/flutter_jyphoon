package com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent;

/**
 * @author juphoon
 * @since 2020/11/4
 */
public class JCOnlineMessageReceiveEvent extends JCEvent {
    public String userId;
    public String content;

    public JCOnlineMessageReceiveEvent(String userId, String content) {
        super(EventType.ONLINE_MESSAGE_RECEIVE);
        this.userId = userId;
        this.content = content;
    }
}
