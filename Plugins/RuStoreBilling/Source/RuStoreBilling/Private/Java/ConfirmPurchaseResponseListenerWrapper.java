package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.billingclient.callbacks.ConfirmPurchaseListener;
import ru.rustore.sdk.billingclient.model.purchase.response.ConfirmPurchaseResponse;

import android.util.Log;

public class ConfirmPurchaseResponseListenerWrapper implements IResponseListenerWrapper, ConfirmPurchaseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, ConfirmPurchaseResponse response);

    public ConfirmPurchaseResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "ConfirmPurchaseResponse: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(ConfirmPurchaseResponse response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "ConfirmPurchaseResponse: Success message");
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
