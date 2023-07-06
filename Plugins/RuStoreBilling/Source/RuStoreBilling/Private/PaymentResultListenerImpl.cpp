// Copyright Epic Games, Inc. All Rights Reserved.

#include "PaymentResultListenerImpl.h"
#include "EURuStorePaymentFinishCode.h"
#include "FURuStoreInvoiceResult.h"
#include "FURuStoreInvalidInvoice.h"
#include "FURuStorePurchaseResult.h"
#include "FURuStoreInvalidPurchase.h"
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

    if (resultType == "InvoiceResult")
    {
        auto result = new FURuStoreInvoiceResult();
        result->invoiceId = responseObject->GetFString("invoiceId");

        auto jPaymentFinishCode = responseObject->GetAJObject("finishCode", "Lru/rustore/sdk/billingclient/model/purchase/PaymentFinishCode;");
        if (jPaymentFinishCode != nullptr)
        {
            int ordinal = jPaymentFinishCode->CallInt("ordinal");
            result->finishCode = static_cast<EURuStorePaymentFinishCode>(ordinal);

            delete jPaymentFinishCode;
        }

        return result;
    }
    else if (resultType == "InvalidInvoice")
    {
        auto result = new FURuStoreInvalidInvoice();
        result->invoiceId = responseObject->GetFString("invoiceId");

        return result;
    }
    else if (resultType == "PurchaseResult")
    {
        auto result = new FURuStorePurchaseResult();

        auto jPaymentFinishCode = responseObject->GetAJObject("finishCode", "Lru/rustore/sdk/billingclient/model/purchase/PaymentFinishCode;");
        if (jPaymentFinishCode != nullptr)
        {
            int ordinal = jPaymentFinishCode->CallInt("ordinal");
            result->finishCode = static_cast<EURuStorePaymentFinishCode>(ordinal);

            delete jPaymentFinishCode;
        }

        result->orderId = responseObject->GetFString("orderId");
        result->purchaseId = responseObject->GetFString("purchaseId");
        result->productId = responseObject->GetFString("productId");
        result->subscriptionToken = responseObject->GetFString("subscriptionToken");

        return result;
    }
    else if (resultType == "InvalidPurchase")
    {
        auto result = new FURuStoreInvalidPurchase();
        result->purchaseId = responseObject->GetFString("purchaseId");
        result->invoiceId = responseObject->GetFString("invoiceId");
        result->orderId = responseObject->GetFString("orderId");

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
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PaymentResultListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PaymentResultListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PaymentResultListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<PaymentResultListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
