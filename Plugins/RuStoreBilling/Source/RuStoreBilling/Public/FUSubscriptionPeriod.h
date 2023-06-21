#pragma once

#include "CoreMinimal.h"
#include "FUSubscriptionPeriod.generated.h"

USTRUCT(BlueprintType)
struct FUSubscriptionPeriod
{
    GENERATED_USTRUCT_BODY()

    FUSubscriptionPeriod()
    {
        years = 1970;
        months = 1;
        days = 1;
    }

    UPROPERTY(BlueprintReadOnly)
    int years;

    UPROPERTY(BlueprintReadOnly)
    int months;

    UPROPERTY(BlueprintReadOnly)
    int days;
};
