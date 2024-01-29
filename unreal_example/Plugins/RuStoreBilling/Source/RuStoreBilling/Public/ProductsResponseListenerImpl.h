// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStoreProductsResponse.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API ProductsResponseListenerImpl : public ResponseListener<FURuStoreProductsResponse>
    {
    public:
        ProductsResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStoreProductsResponse, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStoreProductsResponse>("ru/rustore/unitysdk/billingclient/wrappers/ProductsResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/ProductsResponseListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStoreProductsResponse* ConvertResponse(AndroidJavaObject* responseObject) override;
    };
}
