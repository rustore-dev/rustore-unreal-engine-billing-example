package ru.rustore.unitysdk.billingclient.wrappers;

import ru.rustore.sdk.billingclient.model.user.UserAuthorizationStatus;
import ru.rustore.unitysdk.billingclient.callbacks.UserAuthorizationStatusListener;
import ru.rustore.unitysdk.core.IRuStoreListener;

public class UserAuthorizationStatusWrapper implements IRuStoreListener, UserAuthorizationStatusListener {
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, UserAuthorizationStatus response);

    public UserAuthorizationStatusWrapper(long cppPointer) {
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
    public void OnSuccess(UserAuthorizationStatus response) {
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
