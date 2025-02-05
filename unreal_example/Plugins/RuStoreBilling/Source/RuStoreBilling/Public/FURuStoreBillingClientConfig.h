// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreBillingClientConfig.generated.h"

/*!
@brief Параметры инициализации платежного клиента.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreBillingClientConfig
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Конструктор.
	*/
	FURuStoreBillingClientConfig()
	{
		consoleApplicationId = "";
		deeplinkScheme = "";
		allowNativeErrorHandling = false;
		enableLogs = false;
	}

	/*!
	@brief Идентификатор приложения из консоли RuStore.
	*/
	UPROPERTY(BlueprintReadWrite)
	FString consoleApplicationId;
	
	/*!
	@brief
		URL-адрес для использования deeplink.
		В качестве названия может быть использовано любое уникальное имя (например: yourappscheme).
	*/
	UPROPERTY(BlueprintReadWrite)
	FString deeplinkScheme;
	
	/*!
	@brief Разрешить обработку ошибок в нативном SDK.
	*/
	UPROPERTY(BlueprintReadWrite)
	bool allowNativeErrorHandling;
	
	/*!
	@brief Включить ведение журнала событий.
	*/
	UPROPERTY(BlueprintReadWrite)
	bool enableLogs;
};
