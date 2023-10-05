// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreSubscriptionPeriod.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreSubscriptionPeriod
{
    GENERATED_USTRUCT_BODY()

    FURuStoreSubscriptionPeriod()
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
