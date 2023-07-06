// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IRuStoreListener;
import ru.rustore.unitysdk.billingclient.callbacks.PaymentResultListener;
import ru.rustore.sdk.billingclient.model.purchase.PaymentResult;

public class PaymentResultListenerWrapper implements IRuStoreListener, PaymentResultListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, PaymentResult response);

    public PaymentResultListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(PaymentResult response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnSuccess(cppPointer, response);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
