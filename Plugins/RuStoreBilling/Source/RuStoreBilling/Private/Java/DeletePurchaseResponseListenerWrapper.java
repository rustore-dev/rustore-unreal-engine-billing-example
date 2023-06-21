package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.billingclient.callbacks.DeletePurchaseListener;
import ru.rustore.sdk.billingclient.model.purchase.response.DeletePurchaseResponse;

import android.util.Log;

public class DeletePurchaseResponseListenerWrapper implements IResponseListenerWrapper, DeletePurchaseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, DeletePurchaseResponse response);

    public DeletePurchaseResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "DeletePurchase: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(DeletePurchaseResponse response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "DeletePurchase: Success message");
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
