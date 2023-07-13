// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreResponseWithCode.h"
#include "FURuStorePurchase.h"
#include "FURuStorePurchasesResponse.generated.h"

USTRUCT(BlueprintType)
struct FURuStorePurchasesResponse : public FURuStoreResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FURuStorePurchase> purchases;
};