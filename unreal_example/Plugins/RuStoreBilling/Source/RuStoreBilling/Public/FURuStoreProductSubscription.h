// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreSubscriptionPeriod.h"
#include "FURuStoreProductSubscription.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreProductSubscription
{
	GENERATED_USTRUCT_BODY()

	FURuStoreProductSubscription()
	{
		introductoryPrice = "";
		introductoryPriceAmount = "";
	}

	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod subscriptionPeriod;

	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod freeTrialPeriod;

	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod gracePeriod;

	UPROPERTY(BlueprintReadOnly)
	FString introductoryPrice;

	UPROPERTY(BlueprintReadOnly)
	FString introductoryPriceAmount;

	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod introductoryPricePeriod;
};
