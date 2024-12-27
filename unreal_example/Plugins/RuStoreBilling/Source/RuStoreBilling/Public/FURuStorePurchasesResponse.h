// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePurchase.h"
#include "FURuStorePurchasesResponse.generated.h"

/*!
@brief Информция о покупках пользователя.
*/
USTRUCT(BlueprintType)
struct FURuStorePurchasesResponse
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Список покупок.
	*/
	UPROPERTY(BlueprintReadOnly)
	TArray<FURuStorePurchase> purchases;
};
