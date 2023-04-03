package com.michaellazebny.jyphoon.jc.api

import com.michaellazebny.jyphoon.jc.CallType
import com.michaellazebny.jyphoon.jc.JyphoonApi

sealed class GroupCall : JyphoonApi {
    override fun call(confId: String, password: String, video: Boolean, type: CallType): Boolean {
        return false
    }
}