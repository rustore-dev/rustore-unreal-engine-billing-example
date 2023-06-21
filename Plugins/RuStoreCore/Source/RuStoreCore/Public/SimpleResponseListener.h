#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"
#include "FURuStoreError.h"
#include "CallbackHandler.h"

class RUSTORECORE_API SimpleResponseListener
{
private:
    long cppPointer;
#if PLATFORM_ANDROID
    jobject wrapperJavaObject;
#endif

    TFunction<void(FURuStoreError*)> _onFailure;
    TFunction<void()> _onSuccess;

protected:
    SimpleResponseListener(FString className, TFunction<void(FURuStoreError*)> onFailure, TFunction<void()> onSuccess);
    virtual ~SimpleResponseListener();

    AndroidJavaObject* GetJListener(FString className);
    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject);

public:
    void OnFailure(AndroidJavaObject* errorObject);
    void OnSuccess();
};
