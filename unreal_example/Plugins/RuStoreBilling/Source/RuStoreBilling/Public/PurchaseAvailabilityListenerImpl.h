// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "URuStoreCore.h"
#include "FURuStorePurchaseAvailabilityResult.h"
#include "ResponseListener.h"

namespace RuStoreSDK
{
	class RUSTOREBILLING_API PurchaseAvailabilityListenerImpl : public ResponseListener<FURuStorePurchaseAvailabilityResult>
	{
	protected:
		FURuStorePurchaseAvailabilityResult* ConvertResponse(AndroidJavaObject* responseObject) override;

	public:
		PurchaseAvailabilityListenerImpl(
			TFunction<void(long requestId, TSharedPtr<FURuStorePurchaseAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess,
			TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
			TFunction<void(RuStoreListener*)> onFinish
		) : ResponseListener<FURuStorePurchaseAvailabilityResult>("ru/rustore/unitysdk/billingclient/wrappers/PurchaseAvailabilityListenerWrapper", "ru/rustore/unitysdk/billingclient/callbacks/PurchaseAvailabilityListener", onSuccess, onFailure, onFinish)
		{
		}

		virtual ~PurchaseAvailabilityListenerImpl();
	};
}
