// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStorePurchaseInfoResponse.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API PurchaseInfoResponseListenerImpl : public ResponseListener<FURuStorePurchaseInfoResponse>
    {
    public:
        PurchaseInfoResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStorePurchaseInfoResponse, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStorePurchaseInfoResponse>("com/Plugins/RuStoreBilling/PurchaseInfoResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PurchaseInfoResponseListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStorePurchaseInfoResponse* ConvertResponse(AndroidJavaObject* responseObject) override;
    };
}
