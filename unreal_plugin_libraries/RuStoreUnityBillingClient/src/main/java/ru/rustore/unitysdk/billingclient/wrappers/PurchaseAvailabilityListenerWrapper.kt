package ru.rustore.unitysdk.billingclient.wrappers

import ru.rustore.sdk.billingclient.model.purchase.PurchaseAvailabilityResult
import ru.rustore.unitysdk.billingclient.callbacks.PurchaseAvailabilityListener
import ru.rustore.unitysdk.core.IRuStoreListener

class PurchaseAvailabilityListenerWrapper(cppPointer: Long) : IRuStoreListener, PurchaseAvailabilityListener {

    private val mutex = Any()
    private var cppPointer: Long = 0
    private external fun NativeOnFailure(pointer: Long, throwable: Throwable)
    private external fun NativeOnSuccess(pointer: Long, response: PurchaseAvailabilityResult)

    init {
        this.cppPointer = cppPointer
    }

    override fun OnFailure(throwable: Throwable) {
        synchronized(mutex) {
            if (cppPointer != 0L) {
                NativeOnFailure(cppPointer, throwable)
            }
        }
    }

    override fun OnSuccess(response: PurchaseAvailabilityResult) {
        synchronized(mutex) {
            if (cppPointer != 0L) {
                NativeOnSuccess(cppPointer, response)
            }
        }
    }

    override fun DisposeCppPointer() {
        synchronized(mutex) { cppPointer = 0 }
    }
}
