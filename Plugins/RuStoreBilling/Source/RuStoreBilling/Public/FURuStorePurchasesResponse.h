// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePurchase.h"
#include "FURuStorePurchasesResponse.generated.h"

USTRUCT(BlueprintType)
struct FURuStorePurchasesResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FURuStorePurchase> purchases;
};
