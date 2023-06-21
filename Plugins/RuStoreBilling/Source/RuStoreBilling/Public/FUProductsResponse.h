#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "FUResponseWithCode.h"
#include "FUProduct.h"
#include "FUProductsResponse.generated.h"

USTRUCT(BlueprintType)
struct FUProductsResponse : public FUResponseWithCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FUProduct> products;
};
