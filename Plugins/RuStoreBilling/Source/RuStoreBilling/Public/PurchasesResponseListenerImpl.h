#pragma once

#include "ResponseListener.h"
#include "FUPurchasesResponse.h"
#include "DataConverter.h"

class RUSTOREBILLING_API PurchasesResponseListenerImpl : public ResponseListener<FUPurchasesResponse>
{
public:
    PurchasesResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUPurchasesResponse*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUPurchasesResponse>("com/Plugins/RuStoreBilling/PurchasesResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PurchasesResponseListener", onFailure, onSuccess, onFinish)
    {
    }

protected:
    FUPurchasesResponse* ConvertResponse(AndroidJavaObject* responseObject) override;
};
