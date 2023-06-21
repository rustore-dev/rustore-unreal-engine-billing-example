#pragma once

#include "CoreMinimal.h"
#include "FUSubscriptionPeriod.h"
#include "FUProductSubscription.generated.h"

USTRUCT(BlueprintType)
struct FUProductSubscription
{
	GENERATED_USTRUCT_BODY()

	FUProductSubscription()
	{
		introductoryPrice = "";
		introductoryPriceAmount = "";
	}

	UPROPERTY(BlueprintReadOnly)
	FUSubscriptionPeriod subscriptionPeriod;

	UPROPERTY(BlueprintReadOnly)
	FUSubscriptionPeriod freeTrialPeriod;

	UPROPERTY(BlueprintReadOnly)
	FUSubscriptionPeriod gracePeriod;

	UPROPERTY(BlueprintReadOnly)
	FString introductoryPrice;

	UPROPERTY(BlueprintReadOnly)
	FString introductoryPriceAmount;

	UPROPERTY(BlueprintReadOnly)
	FUSubscriptionPeriod introductoryPricePeriod;
};
