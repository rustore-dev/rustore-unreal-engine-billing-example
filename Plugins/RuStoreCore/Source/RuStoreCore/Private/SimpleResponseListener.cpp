#include "SimpleResponseListener.h"

FURuStoreError* SimpleResponseListener::ConvertError(AndroidJavaObject* errorObject)
{
    FURuStoreError* error = new FURuStoreError();

    error->name = errorObject->CallJavaClassFString("getSimpleName");
    error->description = errorObject->CallFString("getMessage");

    return error;
}

SimpleResponseListener::SimpleResponseListener(FString className, TFunction<void(FURuStoreError*)> onFailure, TFunction<void()> onSuccess)
{
    _onFailure = onFailure;
    _onSuccess = onSuccess;

#if PLATFORM_ANDROID
    cppPointer = (long)this;
    auto obj = new AndroidJavaObject(className, cppPointer);
    wrapperJavaObject = obj->GetJObject();
#endif
}

SimpleResponseListener::~SimpleResponseListener()
{
}

AndroidJavaObject* SimpleResponseListener::GetJListener(FString className)
{
    AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
    result = new AndroidJavaObject(wrapperJavaObject, className);
#endif
    return result;
}

void SimpleResponseListener::OnFailure(AndroidJavaObject* errorObject)
{
    FURuStoreError* error = ConvertError(errorObject);
    delete errorObject;

    CallbackHandler::AddCallback([this, error]() {
        _onFailure(error);
    });
}

void SimpleResponseListener::OnSuccess()
{
    CallbackHandler::AddCallback([this]() {
        _onSuccess();
    });
}
