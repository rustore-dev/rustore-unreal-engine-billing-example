package com.Plugins.RuStoreBilling;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.billingclient.callbacks.ProductsResponseListener;
import ru.rustore.sdk.billingclient.model.product.ProductsResponse;

import android.util.Log;

public class ProductsResponseListenerWrapper implements IResponseListenerWrapper, ProductsResponseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, ProductsResponse response);

    public ProductsResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "ProductsResponse: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(ProductsResponse response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "ProductsResponse: Success message");
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
