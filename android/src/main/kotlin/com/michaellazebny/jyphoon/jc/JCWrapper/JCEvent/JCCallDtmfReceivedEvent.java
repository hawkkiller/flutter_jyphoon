package com.michaellazebny.jyphoon.jc.jcWrapper.JCEvent;

import com.juphoon.cloud.JCCall;
import com.juphoon.cloud.JCCallItem;

/**
 * @author juphoon
 * @since 2020/7/13
 */
public class JCCallDtmfReceivedEvent extends JCEvent {

    public JCCallItem callItem;
    public @JCCall.DtmfValue
    int value;

    public JCCallDtmfReceivedEvent(JCCallItem callItem, @JCCall.DtmfValue int value) {
        super(EventType.CALL_DTMF_RECEIVED);
        this.callItem = callItem;
        this.value = value;
    }
}
