#pragma once

#include "ResponseListener.h"
#include "FUProductsResponse.h"
#include "DataConverter.h"

class RUSTOREBILLING_API ProductsResponseListenerImpl : public ResponseListener<FUProductsResponse>
{
public:
    ProductsResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUProductsResponse*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUProductsResponse>("com/Plugins/RuStoreBilling/ProductsResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/ProductsResponseListener", onFailure, onSuccess, onFinish)
    {
    }

protected:
    FUProductsResponse* ConvertResponse(AndroidJavaObject* responseObject) override;
};
