// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.h"
#include "FURuStorePurchaseAvailabilityResult.generated.h"

/*!
@brief Проверка доступности функционала платежей.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStorePurchaseAvailabilityResult
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Конструктор.
	*/
	FURuStorePurchaseAvailabilityResult()
	{
		isAvailable = false;
	}

	/*!
	@brief
		Информация о доступности платежей.
		Если все условия выполняются, возвращается FURuStorePurchaseAvailabilityResult::isAvailable == true.
		В противном случае возвращается FURuStorePurchaseAvailabilityResult::isAvailable == false.
	*/
	UPROPERTY(BlueprintReadWrite)
	bool isAvailable;
	
	/*!
	@brief Информация об ошибке.
	*/
	UPROPERTY(BlueprintReadWrite)
	FURuStoreError cause;
};
