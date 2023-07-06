// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurchasesResponseListenerImpl.h"

using namespace RuStoreSDK;

FURuStorePurchasesResponse* PurchasesResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FURuStorePurchasesResponse();

    DataConverter::InitResponseWithCode(responseObject, response);

    auto purchases = responseObject->GetAJObject("purchases", "Ljava/util/List;");
    if (purchases != nullptr)
    {
        auto size = purchases->CallInt("size");
        for (int i = 0; i < size; i++)
        {
            auto purchase = purchases->CallAJObject("get", i);
            if (purchase != nullptr)
            {
                auto item = DataConverter::ConvertPurchase(purchase);
                response->purchases.Add(*item);

                delete purchase;
            }
        }

        delete purchases;
    }

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PurchasesResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchasesResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PurchasesResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PurchasesResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
