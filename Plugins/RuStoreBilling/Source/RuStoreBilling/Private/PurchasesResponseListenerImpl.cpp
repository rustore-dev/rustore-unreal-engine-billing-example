#include "PurchasesResponseListenerImpl.h"

FUPurchasesResponse* PurchasesResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FUPurchasesResponse();

    DataConverter::InitResponseWithCode(responseObject, response);

    auto purchases = responseObject->GetAJObject("purchases", "Ljava/util/List;");
    if (purchases != nullptr)
    {
        auto size = purchases->CallInt("size");
        for (int i = 0; i < size; i++)
        {
            auto p = purchases->CallAJObject("get", i);
            if (p != nullptr)
            {
                auto item = DataConverter::ConvertPurchase(p);
                response->purchases.Add(*item);

                delete p;
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
        auto castobj = reinterpret_cast<ResponseListener<FUPurchasesResponse>*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_PurchasesResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto castobj = reinterpret_cast<ResponseListener<FUPurchasesResponse>*>(pointer);
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();
        castobj->OnSuccess(obj);
    }
}
#endif
