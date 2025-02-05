// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreSubscriptionPeriod.h"
#include "FURuStoreProductSubscription.generated.h"

/*!
@brief Информация о подписке.
*/
USTRUCT(BlueprintType)
struct FURuStoreProductSubscription
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Конструктор.
	*/
	FURuStoreProductSubscription()
	{
		introductoryPrice = "";
		introductoryPriceAmount = "";
	}

	/*!
	@brief Период подписки.
	*/
	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod subscriptionPeriod;

	/*!
	@brief Пробный период подписки.
	*/
	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod freeTrialPeriod;

	/*!
	@brief Льготный период подписки.
	*/
	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod gracePeriod;

	/*!
	@brief Отформатированная вступительная цена подписки, включая знак валюты, на языке FURuStoreProduct::language.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString introductoryPrice;

	/*!
	@brief Вступительная цена в минимальных единицах валюты (напрмер в копейках).
	*/
	UPROPERTY(BlueprintReadOnly)
	FString introductoryPriceAmount;

	/*!
	@brief Расчётный период вступительной цены.
	*/
	UPROPERTY(BlueprintReadOnly)
	FURuStoreSubscriptionPeriod introductoryPricePeriod;
};
