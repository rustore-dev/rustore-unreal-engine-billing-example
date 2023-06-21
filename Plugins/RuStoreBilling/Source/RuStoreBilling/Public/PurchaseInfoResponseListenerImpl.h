#pragma once

#include "ResponseListener.h"
#include "FUPurchaseInfoResponse.h"
#include "DataConverter.h"

class PurchaseInfoResponseListenerImpl : public ResponseListener<FUPurchaseInfoResponse>
{
public:
    PurchaseInfoResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUPurchaseInfoResponse*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUPurchaseInfoResponse>("com/Plugins/RuStoreBilling/PurchaseInfoResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PurchaseInfoResponseListener", onFailure, onSuccess, onFinish)
    {
    }

protected:
    FUPurchaseInfoResponse* ConvertResponse(AndroidJavaObject* responseObject) override;
};
