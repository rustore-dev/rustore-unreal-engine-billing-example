// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStoreDeletePurchaseResponse.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API DeletePurchaseResponseListenerImpl : public ResponseListener<FURuStoreDeletePurchaseResponse>
    {
    public:
        DeletePurchaseResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStoreDeletePurchaseResponse, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStoreDeletePurchaseResponse>("com/Plugins/RuStoreBilling/DeletePurchaseResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/DeletePurchaseListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStoreDeletePurchaseResponse* ConvertResponse(AndroidJavaObject* responseObject) override
        {
            auto response = new FURuStoreDeletePurchaseResponse();
            DataConverter::InitResponseWithCode(responseObject, response);

            return response;
        }
    };
}
