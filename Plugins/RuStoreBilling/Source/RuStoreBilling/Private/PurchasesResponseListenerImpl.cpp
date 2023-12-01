// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurchasesResponseListenerImpl.h"

using namespace RuStoreSDK;

FURuStorePurchasesResponse* PurchasesResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FURuStorePurchasesResponse();

    auto size = responseObject->CallInt("size");
    for (int i = 0; i < size; i++)
    {
        auto purchase = responseObject->CallAJObject("get", i);
        if (purchase != nullptr)
        {
            auto item = DataConverter::ConvertPurchase(purchase);
            response->purchases.Add(*item);

            delete purchase;
        }
    }

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PurchasesResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchasesResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PurchasesResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchasesResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
