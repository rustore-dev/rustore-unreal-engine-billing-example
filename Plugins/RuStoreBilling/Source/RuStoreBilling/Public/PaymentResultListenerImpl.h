#pragma once

#include "ResponseListener.h"
#include "FUPaymentResult.h"
#include "DataConverter.h"

class RUSTOREBILLING_API PaymentResultListenerImpl : public ResponseListener<FUPaymentResult>
{
public:
    PaymentResultListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUPaymentResult*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUPaymentResult>("com/Plugins/RuStoreBilling/PaymentResultListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PaymentResultListener", onFailure, onSuccess, onFinish)
    {
    }

protected:
    FUPaymentResult* ConvertResponse(AndroidJavaObject* responseObject) override;
};
