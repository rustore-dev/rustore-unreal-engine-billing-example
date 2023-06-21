#pragma once

#include "ResponseListener.h"
#include "FUDeletePurchaseResponse.h"
#include "DataConverter.h"

class RUSTOREBILLING_API DeletePurchaseResponseListenerImpl : public ResponseListener<FUDeletePurchaseResponse>
{
public:
    DeletePurchaseResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUDeletePurchaseResponse*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUDeletePurchaseResponse>("com/Plugins/RuStoreBilling/DeletePurchaseResponseListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/DeletePurchaseListener", onFailure, onSuccess, onFinish)
    {
    }

protected:
    FUDeletePurchaseResponse* ConvertResponse(AndroidJavaObject* responseObject) override
    {
        auto response = new FUDeletePurchaseResponse();
        DataConverter::InitResponseWithCode(responseObject, response);

        return response;
    }
};
