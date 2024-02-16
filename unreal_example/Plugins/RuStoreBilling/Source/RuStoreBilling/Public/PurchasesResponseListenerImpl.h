// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStorePurchasesResponse.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API PurchasesResponseListenerImpl : public ResponseListener<FURuStorePurchasesResponse>
    {
    public:
        PurchasesResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStorePurchasesResponse, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStorePurchasesResponse>("ru/rustore/unitysdk/billingclient/wrappers/PurchasesResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PurchasesResponseListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStorePurchasesResponse* ConvertResponse(AndroidJavaObject* responseObject) override;
    };
}
