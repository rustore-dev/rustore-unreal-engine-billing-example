// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreResponseWithCode.h"
#include "FURuStorePurchase.h"
#include "FURuStoreRequestMeta.h"
#include "FURuStorePurchaseInfoResponse.generated.h"

USTRUCT(BlueprintType)
struct FURuStorePurchaseInfoResponse : public FURuStoreResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	FURuStoreRequestMeta meta;

	UPROPERTY(BlueprintReadOnly)
	FURuStorePurchase purchase;
};
