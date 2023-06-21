#include "ErrorListener.h"

ErrorListener::ErrorListener(FString className, TFunction<void(FURuStoreError*)> onFailure)
{
    _onFailure = onFailure;

#if PLATFORM_ANDROID
    cppPointer = reinterpret_cast<long>(this);
    auto a = new AndroidJavaObject(className, cppPointer);
    wrapperJavaObject = a->GetJObject();
#endif
}

AndroidJavaObject* ErrorListener::GetJListener(FString className)
{
    AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
    result = new AndroidJavaObject(wrapperJavaObject, className);
#endif
    return result;
}

FURuStoreError* ErrorListener::ConvertError(AndroidJavaObject* errorObject)
{
    auto error = new FURuStoreError();

    error->name = errorObject->CallJavaClassFString("getSimpleName");
    error->description = errorObject->CallFString("getMessage");

    return error;
}

void ErrorListener::OnFailure(AndroidJavaObject* errorObject)
{
    FURuStoreError* error = ConvertError(errorObject);
    delete errorObject;

    CallbackHandler::AddCallback([this, error]() {
        _onFailure(error);
    });
}
