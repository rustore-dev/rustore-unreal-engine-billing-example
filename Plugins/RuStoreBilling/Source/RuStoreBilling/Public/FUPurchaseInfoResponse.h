#pragma once

#include "CoreMinimal.h"
#include "FUResponseWithCode.h"
#include "FUPurchase.h"
#include "FURequestMeta.h"
#include "FUPurchaseInfoResponse.generated.h"

USTRUCT(BlueprintType)
struct FUPurchaseInfoResponse : public FUResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	FURequestMeta meta;

	UPROPERTY(BlueprintReadOnly)
	FUPurchase purchase;
};
