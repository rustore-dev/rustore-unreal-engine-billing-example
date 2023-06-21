#include "ProductsResponseListenerImpl.h"

FUProductsResponse* ProductsResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FUProductsResponse();

    DataConverter::InitResponseWithCode(responseObject, response);

    auto products = responseObject->GetAJObject("products", "Ljava/util/List;");
    if (products != nullptr)
    {
        auto size = products->CallInt("size");
        for (int i = 0; i < size; i++)
        {
            auto p = products->CallAJObject("get", i);
            if (p != nullptr)
            {
                auto item = DataConverter::ConvertProduct(p);
                response->products.Add(*item);

                delete p;
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
        auto castobj = reinterpret_cast<ResponseListener<FUProductsResponse>*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_ProductsResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto castobj = reinterpret_cast<ResponseListener<FUProductsResponse>*>(pointer);
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();
        castobj->OnSuccess(obj);
    }
}
#endif
