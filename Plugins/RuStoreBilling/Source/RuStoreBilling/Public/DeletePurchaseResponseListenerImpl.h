// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FURuStoreError.h"
#include "SimpleResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API DeletePurchaseResponseListenerImpl : public SimpleResponseListener
    {
    public:
        DeletePurchaseResponseListenerImpl(
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListener("ru/rustore/unitysdk/billingclient/wrappers/DeletePurchaseResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/DeletePurchaseListener", onSuccess, onFailure, onFinish)
        {
        }
    };
}
