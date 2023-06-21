package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.billingclient.callbacks.PurchaseInfoResponseListener;
import ru.rustore.sdk.billingclient.model.purchase.response.PurchaseInfoResponse;

import android.util.Log;

public class PurchaseInfoResponseListenerWrapper implements IResponseListenerWrapper, PurchaseInfoResponseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, PurchaseInfoResponse response);

    public PurchaseInfoResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "PurchaseInfoResponse: Error message");
                NativeOnFailure(cppPointer, throwable);  
            }
		}
    }

    @Override
    public void OnSuccess(PurchaseInfoResponse response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "PurchaseInfoResponse: Succes message");
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
