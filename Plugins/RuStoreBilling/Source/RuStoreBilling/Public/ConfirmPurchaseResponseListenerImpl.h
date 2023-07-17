// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FURuStoreError.h"
#include "SimpleResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API ConfirmPurchaseResponseListenerImpl : public SimpleResponseListener
    {
    public:
        ConfirmPurchaseResponseListenerImpl(
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListener("com/Plugins/RuStoreBilling/ConfirmPurchaseResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/ConfirmPurchaseListener", onSuccess, onFailure, onFinish)
        {
        }
    };
}
