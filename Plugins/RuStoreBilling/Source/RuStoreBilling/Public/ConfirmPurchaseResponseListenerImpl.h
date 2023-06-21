#pragma once

#include "ResponseListener.h"
#include "FUConfirmPurchaseResponse.h"
#include "DataConverter.h"

class RUSTOREBILLING_API ConfirmPurchaseResponseListenerImpl : public ResponseListener<FUConfirmPurchaseResponse>
{
public:
    ConfirmPurchaseResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUConfirmPurchaseResponse*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUConfirmPurchaseResponse>("com/Plugins/RuStoreBilling/ConfirmPurchaseResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/ConfirmPurchaseListener", onFailure, onSuccess, onFinish)
    {
    }

protected:
    FUConfirmPurchaseResponse* ConvertResponse(AndroidJavaObject* responseObject) override
    {
        auto response = new FUConfirmPurchaseResponse();
        DataConverter::InitResponseWithCode(responseObject, response);

        return response;
    }
};
