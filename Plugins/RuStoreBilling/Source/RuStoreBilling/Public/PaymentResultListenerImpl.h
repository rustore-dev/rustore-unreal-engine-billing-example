// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ResponseListener.h"
#include "FURuStorePaymentResult.h"
#include "DataConverter.h"

namespace RuStoreSDK
{
    class RUSTOREBILLING_API PaymentResultListenerImpl : public ResponseListener<FURuStorePaymentResult>
    {
    public:
        PaymentResultListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStorePaymentResult>("ru/rustore/unitysdk/billingclient/wrappers/PaymentResultListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PaymentResultListener", onSuccess, onFailure, onFinish)
        {
        }

    protected:
        FURuStorePaymentResult* ConvertResponse(AndroidJavaObject* responseObject) override;
    };
}
