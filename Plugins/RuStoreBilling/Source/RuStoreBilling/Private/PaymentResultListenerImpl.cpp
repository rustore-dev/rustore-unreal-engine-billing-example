#include "PaymentResultListenerImpl.h"
#include "EUPaymentFinishCode.h"
#include "FUInvoiceResult.h"
#include "FUInvalidInvoice.h"
#include "FUPurchaseResult.h"
#include "FUInvalidPurchase.h"
#include "FUInvalidPaymentState.h"

FUPaymentResult* PaymentResultListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    FString resultType = "";

    AndroidJavaObject* javaClass = responseObject->CallAJClass("getClass");

    FString str = javaClass->CallFString("getName");
    TArray<FString> _className;
    str.ParseIntoArray(_className, TEXT("$"), true);
    if (_className.Num() > 0) resultType = _className.Last();

    FString tag = "rustore";
    FString msg = str;
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*msg));
#endif

    delete javaClass;

    if (resultType == "InvoiceResult")
    {
        auto result = new FUInvoiceResult();
        result->invoiceId = responseObject->GetFString("invoiceId");

        auto jpaymentFinishCode = responseObject->GetAJObject("finishCode", "Lru/rustore/sdk/billingclient/model/purchase/PaymentFinishCode;");
        if (jpaymentFinishCode != nullptr)
        {
            int ordinal = jpaymentFinishCode->CallInt("ordinal");
            result->finishCode = static_cast<EUPaymentFinishCode>(ordinal);

            delete jpaymentFinishCode;
        }

        return result;
    }
    else if (resultType == "InvalidInvoice")
    {
        auto result = new FUInvalidInvoice();
        result->invoiceId = responseObject->GetFString("invoiceId");

        return result;
    }
    else if (resultType == "PurchaseResult")
    {
        auto result = new FUPurchaseResult();

        auto jpaymentFinishCode = responseObject->GetAJObject("finishCode", "Lru/rustore/sdk/billingclient/model/purchase/PaymentFinishCode;");
        if (jpaymentFinishCode != nullptr)
        {
            int ordinal = jpaymentFinishCode->CallInt("ordinal");
            result->finishCode = static_cast<EUPaymentFinishCode>(ordinal);

            delete jpaymentFinishCode;
        }

        result->orderId = responseObject->GetFString("orderId");
        result->purchaseId = responseObject->GetFString("purchaseId");
        result->productId = responseObject->GetFString("productId");
        result->subscriptionToken = responseObject->GetFString("subscriptionToken");

        return result;
    }
    else if (resultType == "InvalidPurchase")
    {
        auto result = new FUInvalidPurchase();
        result->purchaseId = responseObject->GetFString("purchaseId");
        result->invoiceId = responseObject->GetFString("invoiceId");
        result->orderId = responseObject->GetFString("orderId");

        auto jquantity = responseObject->GetAJObject("quantity", "Ljava/lang/Integer;");
        if (jquantity != nullptr)
        {
            result->quantity = jquantity->CallInt("intValue");
            delete jquantity;
        }

        result->productId = responseObject->GetFString("productId");

        auto jerrorCode = responseObject->GetAJObject("errorCode", "Ljava/lang/Integer;");
        if (jerrorCode != nullptr)
        {
            result->errorCode = jerrorCode->CallInt("intValue");
            delete jerrorCode;
        }

        return result;
    }

    return new FUInvalidPaymentState();
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PaymentResultListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto castobj = reinterpret_cast<PaymentResultListenerImpl*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PaymentResultListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto castobj = reinterpret_cast<PaymentResultListenerImpl*>(pointer);
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();
        castobj->OnSuccess(obj);
    }
}
#endif
