#pragma once

#include "CoreMinimal.h"
#include "FUResponseWithCode.h"
#include "FUPurchase.h"
#include "FUPurchasesResponse.generated.h"

USTRUCT(BlueprintType)
struct FUPurchasesResponse : public FUResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FUPurchase> purchases;
};
