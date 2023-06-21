#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaClass.h"
#include "AndroidJavaObject.h"
#include "FURuStoreError.h"
#include "CallbackHandler.h"

class RUSTORECORE_API ErrorListener
{
private:
    long cppPointer;
#if PLATFORM_ANDROID
    jobject wrapperJavaObject;
#endif

    TFunction<void(FURuStoreError*)> _onFailure;

protected:
    ErrorListener(FString className, TFunction<void(FURuStoreError*)> onFailure);

    AndroidJavaObject* GetJListener(FString className);
    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject);

public:
    void OnFailure(AndroidJavaObject* errorObject);
};
