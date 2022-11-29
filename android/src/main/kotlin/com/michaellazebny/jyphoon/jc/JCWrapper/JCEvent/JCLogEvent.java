package com.michaellazebny.jyphoon.jc.JCWrapper.JCEvent;

public class JCLogEvent extends JCEvent {

    public String log;

    public JCLogEvent(String log) {
        super(EventType.JCLOG);
        this.log = log;
    }
}
