// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStoreConfirmPurchaseResponse.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API ConfirmPurchaseResponseListenerImpl : public ResponseListener<FURuStoreConfirmPurchaseResponse>
    {
    public:
        ConfirmPurchaseResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStoreConfirmPurchaseResponse, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStoreConfirmPurchaseResponse>("com/Plugins/RuStoreBilling/ConfirmPurchaseResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/ConfirmPurchaseListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStoreConfirmPurchaseResponse* ConvertResponse(AndroidJavaObject* responseObject) override
        {
            auto response = new FURuStoreConfirmPurchaseResponse();
            DataConverter::InitResponseWithCode(responseObject, response);

            return response;
        }
    };
}
