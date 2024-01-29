// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreCancelled.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreCancelled : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    FURuStoreCancelled()
    {
        purchaseId = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    virtual FString GetTypeName() override { return "FURuStoreCancelled"; }
};
