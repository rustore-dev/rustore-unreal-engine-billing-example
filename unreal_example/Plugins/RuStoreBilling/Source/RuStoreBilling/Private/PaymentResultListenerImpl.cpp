// Copyright Epic Games, Inc. All Rights Reserved.

#include "PaymentResultListenerImpl.h"
#include "FURuStoreSuccess.h"
#include "FURuStoreCancelled.h"
#include "FURuStoreFailure.h"
#include "FURuStoreInvalidPaymentState.h"

using namespace RuStoreSDK;

FURuStorePaymentResult* PaymentResultListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    FString resultType = "";

    AndroidJavaObject* javaClass = responseObject->CallAJClass("getClass");

    FString str = javaClass->CallFString("getName");
    TArray<FString> _className;
    str.ParseIntoArray(_className, TEXT("$"), true);
    if (_className.Num() > 0) resultType = _className.Last();

    delete javaClass;

    if (resultType == "Success")
    {
        auto result = new FURuStoreSuccess();

        result->orderId = responseObject->GetFString("orderId");
        result->purchaseId = responseObject->GetFString("purchaseId");
        result->productId = responseObject->GetFString("productId");
        result->invoiceId = responseObject->GetFString("invoiceId");
        result->subscriptionToken = responseObject->GetFString("subscriptionToken");
        result->sandbox = responseObject->GetBool("sandbox");

        return result;
    }
    else if (resultType == "Cancelled")
    {
        auto result = new FURuStoreCancelled();
        result->purchaseId = responseObject->GetFString("purchaseId");
        result->sandbox = responseObject->GetBool("sandbox");

        return result;
    }
    else if (resultType == "Failure")
    {
        auto result = new FURuStoreFailure();

        result->purchaseId = responseObject->GetFString("purchaseId");
        result->invoiceId = responseObject->GetFString("invoiceId");
        result->orderId = responseObject->GetFString("orderId");
        result->sandbox = responseObject->GetBool("sandbox");

        auto jQuantity = responseObject->GetAJObject("quantity", "Ljava/lang/Integer;");
        if (jQuantity != nullptr)
        {
            result->quantity = jQuantity->CallInt("intValue");
            delete jQuantity;
        }

        result->productId = responseObject->GetFString("productId");

        auto jErrorCode = responseObject->GetAJObject("errorCode", "Ljava/lang/Integer;");
        if (jErrorCode != nullptr)
        {
            result->errorCode = jErrorCode->CallInt("intValue");
            delete jErrorCode;
        }

        return result;
    }

    return new FURuStoreInvalidPaymentState();
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PaymentResultListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PaymentResultListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_PaymentResultListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PaymentResultListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
