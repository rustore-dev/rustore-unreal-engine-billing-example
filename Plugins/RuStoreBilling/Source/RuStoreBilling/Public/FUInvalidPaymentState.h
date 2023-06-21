#pragma once

#include "CoreMinimal.h"
#include "FUPaymentResult.h"
#include "FUInvalidPaymentState.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FUInvalidPaymentState : public FUPaymentResult
{
    GENERATED_USTRUCT_BODY()

    virtual ~FUInvalidPaymentState() {}

    virtual FString GetTypeName() override { return "FUInvalidPaymentState"; }
};
