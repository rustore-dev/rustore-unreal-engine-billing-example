#pragma once

#include "CoreMinimal.h"
#include "FURuStoreBillingClientConfig.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreBillingClientConfig
{
	GENERATED_USTRUCT_BODY()

	FURuStoreBillingClientConfig()
	{
		consoleApplicationId = "";
		deeplinkScheme = "";
		allowNativeErrorHandling = false;
		enableLogs = false;
	}

	UPROPERTY(BlueprintReadWrite)
	FString consoleApplicationId;
	
	UPROPERTY(BlueprintReadWrite)
	FString deeplinkScheme;
	
	UPROPERTY(BlueprintReadWrite)
	bool allowNativeErrorHandling;
	
	UPROPERTY(BlueprintReadWrite)
	bool enableLogs;
};
