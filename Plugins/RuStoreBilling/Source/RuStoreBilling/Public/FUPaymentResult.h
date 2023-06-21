#pragma once

#include "CoreMinimal.h"
#include "FUPaymentResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FUPaymentResult
{
    GENERATED_USTRUCT_BODY()

    virtual ~FUPaymentResult() {}

    virtual FString GetTypeName() { return "FUPaymentResult"; }
};
