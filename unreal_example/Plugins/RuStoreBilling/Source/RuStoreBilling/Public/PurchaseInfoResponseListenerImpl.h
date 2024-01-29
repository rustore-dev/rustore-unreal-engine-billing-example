// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStorePurchase.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API PurchaseInfoResponseListenerImpl : public ResponseListener<FURuStorePurchase>
    {
    public:
        PurchaseInfoResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStorePurchase, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStorePurchase>("ru/rustore/unitysdk/billingclient/wrappers/PurchaseInfoResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PurchaseInfoResponseListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStorePurchase* ConvertResponse(AndroidJavaObject* responseObject) override;
    };
}
