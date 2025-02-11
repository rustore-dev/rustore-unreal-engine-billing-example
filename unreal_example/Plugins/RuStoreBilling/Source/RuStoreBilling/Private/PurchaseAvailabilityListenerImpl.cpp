// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurchaseAvailabilityListenerImpl.h"

using namespace RuStoreSDK;

PurchaseAvailabilityListenerImpl::~PurchaseAvailabilityListenerImpl()
{
}

FURuStorePurchaseAvailabilityResult* PurchaseAvailabilityListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    FString resultType = "";

    AndroidJavaObject* javaClassObject = responseObject->CallAJClass("getClass");

    FString str = javaClassObject->CallFString("getName");
    TArray<FString> _className;
    str.ParseIntoArray(_className, TEXT("$"), true);
    if (_className.Num() > 0) resultType = _className.Last();

    delete javaClassObject;

    auto response = new FURuStorePurchaseAvailabilityResult();

    if (resultType == "Unavailable")
    {
        response->isAvailable = false;

        auto causeObject = responseObject->GetAJObject("cause", "Lru/rustore/sdk/core/exception/RuStoreException;");

        response->cause.name = causeObject->CallJavaClassFString("getSimpleName");
        response->cause.description = causeObject->CallFString("getMessage");
    }
    else
    {
        if (resultType == "Available")
        {
            response->isAvailable = true;
        }
        else
        {
            response->isAvailable = false;
            response->cause.name = "Error";
            response->cause.description = "Unknown response type";
        }
    }

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PurchaseAvailabilityListenerWrapper_NativeOnFailure(JNIEnv* env, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchaseAvailabilityListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PurchaseAvailabilityListenerWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchaseAvailabilityListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
