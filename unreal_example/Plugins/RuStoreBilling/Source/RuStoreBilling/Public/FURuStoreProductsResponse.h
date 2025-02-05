// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "FURuStoreProduct.h"
#include "FURuStoreProductsResponse.generated.h"

/*!
@brief Информация о продуктах.
*/
USTRUCT(BlueprintType)
struct FURuStoreProductsResponse
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Список продуктов.
	*/
	UPROPERTY(BlueprintReadWrite)
	TArray<FURuStoreProduct> products;
};
