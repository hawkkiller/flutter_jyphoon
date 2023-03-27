package com.michaellazebny.jyphoon.jc.views

import android.content.res.Resources
import android.util.TypedValue

class ViewHelper {
    companion object {
         fun convertDpToPixel(dp: Double) : Float {
            return TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dp.toFloat(),
                Resources.getSystem().displayMetrics)
         }
    }
}