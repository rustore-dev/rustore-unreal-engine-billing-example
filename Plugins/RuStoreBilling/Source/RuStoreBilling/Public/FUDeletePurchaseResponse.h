#pragma once

#include "CoreMinimal.h"
#include "FUResponseWithCode.h"
#include "FUDeletePurchaseResponse.generated.h"

USTRUCT(BlueprintType)
struct FUDeletePurchaseResponse : public FUResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	FUDeletePurchaseResponse()
	{
	}
};
