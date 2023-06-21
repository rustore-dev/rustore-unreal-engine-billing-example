#pragma once

#include "CoreMinimal.h"
#include "FUInvalidPaymentState.h"
#include "UPaymentResultBase.h"
#include "UInvalidPaymentState.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API UInvalidPaymentState : public UPaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FUInvalidPaymentState value;
};
