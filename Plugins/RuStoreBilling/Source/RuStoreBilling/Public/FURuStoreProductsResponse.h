// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "FURuStoreResponseWithCode.h"
#include "FURuStoreProduct.h"
#include "FURuStoreProductsResponse.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreProductsResponse : public FURuStoreResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FURuStoreProduct> products;
};
