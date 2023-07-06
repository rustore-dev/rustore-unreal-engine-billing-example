// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProductsResponseListenerImpl.h"

using namespace RuStoreSDK;

FURuStoreProductsResponse* ProductsResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FURuStoreProductsResponse();

    DataConverter::InitResponseWithCode(responseObject, response);

    auto products = responseObject->GetAJObject("products", "Ljava/util/List;");
    if (products != nullptr)
    {
        auto size = products->CallInt("size");
        for (int i = 0; i < size; i++)
        {
            auto product = products->CallAJObject("get", i);
            if (product != nullptr)
            {
                auto item = DataConverter::ConvertProduct(product);
                response->products.Add(*item);

                delete product;
            }
        }

        delete products;
    }

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_ProductsResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<ProductsResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_ProductsResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<ProductsResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
