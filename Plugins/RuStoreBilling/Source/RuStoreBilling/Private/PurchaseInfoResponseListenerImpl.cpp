// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurchaseInfoResponseListenerImpl.h"

using namespace RuStoreSDK;

FURuStorePurchase* PurchaseInfoResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    return DataConverter::ConvertPurchase(responseObject);
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PurchaseInfoResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchaseInfoResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PurchaseInfoResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchaseInfoResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
