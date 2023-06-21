#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaClass.h"
#include "AndroidJavaObject.h"
#include "FURuStoreError.h"
#include "CallbackHandler.h"

template <typename T>
class SimpleResponseListenerT
{
private:
    long cppPointer;
#if PLATFORM_ANDROID
    jobject wrapperJavaObject;
#endif

    TFunction<void(FURuStoreError*)> _onFailure;
    TFunction<void(T)> _onSuccess;

protected:
    SimpleResponseListenerT(
        FString className,
        TFunction<void(FURuStoreError*)> onFailure,
        TFunction<void(T)> onSuccess
    )
    {
        _onFailure = onFailure;
        _onSuccess = onSuccess;

#if PLATFORM_ANDROID
        cppPointer = reinterpret_cast<long>(this);
        auto obj = new AndroidJavaObject(className, cppPointer);
        wrapperJavaObject = obj->GetJObject();
#endif
    }

    AndroidJavaObject* GetJListener(FString className)
    {
        AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
        result = new AndroidJavaObject(wrapperJavaObject, className);
#endif
        return result;
    }

    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject)
    {
        FURuStoreError* error = new FURuStoreError();

        error->name = errorObject->CallJavaClassFString("getSimpleName");
        error->description = errorObject->CallFString("getMessage");

        return error;
    }

public:
    void OnFailure(AndroidJavaObject* errorObject)
    {
        FURuStoreError* error = ConvertError(errorObject);
        delete errorObject;

        CallbackHandler::AddCallback([this, error]() {
            _onFailure(error);
        });
    }

    void OnSuccess(T response)
    {
        CallbackHandler::AddCallback([this, response]() {
            _onSuccess(response);
        });
    }
};
