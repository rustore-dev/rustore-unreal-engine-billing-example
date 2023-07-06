// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    virtual ~FURuStorePaymentResult() {}

    virtual FString GetTypeName() { return "FURuStorePaymentResult"; }
};
