package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.billingclient.callbacks.PaymentResultListener;
import ru.rustore.sdk.billingclient.model.purchase.PaymentResult;

import android.util.Log;

public class PaymentResultListenerWrapper implements IResponseListenerWrapper, PaymentResultListener
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
                Log.e("rustore", "PaymentResult: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(PaymentResult response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "PaymentResult: Success message");
                NativeOnSuccess(cppPointer, response);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            Log.e("rustore", "FeatureAvailabilityResult: Dispose pointer");
            cppPointer = 0;
        }
    }
}
