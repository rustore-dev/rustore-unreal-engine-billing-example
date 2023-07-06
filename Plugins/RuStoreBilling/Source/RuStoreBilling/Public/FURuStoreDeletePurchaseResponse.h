// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreResponseWithCode.h"
#include "FURuStoreDeletePurchaseResponse.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreDeletePurchaseResponse : public FURuStoreResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	FURuStoreDeletePurchaseResponse()
	{
	}
};
