// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "URuStoreCore.h"
#include "DataConverter.h"
#include "ResponseListener.h"

namespace RuStoreSDK
{
	class RUSTOREBILLING_API UserAuthorizationStatusListenerImpl : public ResponseListener<FURuStoreUserAuthorizationStatus>
	{
	protected:
		FURuStoreUserAuthorizationStatus* ConvertResponse(AndroidJavaObject* responseObject) override;

	public:
		UserAuthorizationStatusListenerImpl(
			TFunction<void(long requestId, TSharedPtr<FURuStoreUserAuthorizationStatus, ESPMode::ThreadSafe>)> onSuccess,
			TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
			TFunction<void(RuStoreListener*)> onFinish
		) : ResponseListener<FURuStoreUserAuthorizationStatus>("ru/rustore/unitysdk/billingclient/wrappers/UserAuthorizationStatusWrapper", "ru/rustore/unitysdk/billingclient/callbacks/UserAuthorizationStatusListener", onSuccess, onFailure, onFinish)
		{
		}

		virtual ~UserAuthorizationStatusListenerImpl();
	};
}
