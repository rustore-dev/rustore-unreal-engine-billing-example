package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.billingclient.callbacks.PurchasesResponseListener;
import ru.rustore.sdk.billingclient.model.purchase.response.PurchasesResponse;

import android.util.Log;

public class PurchasesResponseListenerWrapper implements IResponseListenerWrapper, PurchasesResponseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, PurchasesResponse response);

    public PurchasesResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "PurchasesResponse: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(PurchasesResponse response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "PurchasesResponse: Success message");
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
