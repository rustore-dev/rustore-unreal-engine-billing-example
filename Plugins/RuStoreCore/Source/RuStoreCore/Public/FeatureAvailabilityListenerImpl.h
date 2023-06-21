#pragma once

#include "CoreMinimal.h"

#include "AndroidJavaObject.h"
#include "URuStoreCore.h"
#include "FURuStoreError.h"
#include "FUFeatureAvailabilityResult.h"
#include "ResponseListener.h"

using namespace std;

class RUSTORECORE_API FeatureAvailabilityListenerImpl : public ResponseListener<FUFeatureAvailabilityResult>
{
private:
	weak_ptr<FeatureAvailabilityListenerImpl> weakPtr;

public:
	FeatureAvailabilityListenerImpl(
		TFunction<void(long requestId, FURuStoreError*)> onFailure,
		TFunction<void(long requestId, FUFeatureAvailabilityResult*)> onSuccess,
		TFunction<void(RuStoreListener*)> onFinish
	) : ResponseListener<FUFeatureAvailabilityResult>("com/Plugins/RuStoreCore/FeatureAvailabilityListenerWrapper", "ru/rustore/unitysdk/core/callbacks/FeatureAvailabilityListener", onFailure, onSuccess, onFinish)
    {
	}

	virtual ~FeatureAvailabilityListenerImpl();

protected:
	FUFeatureAvailabilityResult* ConvertResponse(AndroidJavaObject* responseObject) override;
};
