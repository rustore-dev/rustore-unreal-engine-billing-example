// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurchaseInfoResponseListenerImpl.h"

using namespace RuStoreSDK;

FURuStorePurchaseInfoResponse* PurchaseInfoResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FURuStorePurchaseInfoResponse();

    DataConverter::InitResponseWithCode(responseObject, response);

    auto meta = responseObject->GetAJObject("meta", "Lru/rustore/sdk/billingclient/model/common/RequestMeta;");
    if (meta != nullptr)
    {
        response->meta = *DataConverter::ConvertRequestMeta(meta);
    }

    auto purchase = responseObject->GetAJObject("purchase", "Lru/rustore/sdk/billingclient/model/purchase/Purchase;");
    if (purchase != nullptr)
    {
        response->purchase = *DataConverter::ConvertPurchase(purchase);
    }

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PurchaseInfoResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchaseInfoResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PurchaseInfoResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchaseInfoResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
