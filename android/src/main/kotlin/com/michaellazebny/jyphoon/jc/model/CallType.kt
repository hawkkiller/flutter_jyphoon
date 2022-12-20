package com.michaellazebny.jyphoon.jc.model

enum class CallType {
    CALL,
    CONFERENCE;

    companion object {
        fun fromInt(value: Int): CallType {
            return when (value) {
                0 -> CALL
                1 -> CONFERENCE
                else -> throw IllegalArgumentException("Unknown CallType value: $value")
            }
        }
    }
}