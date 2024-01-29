// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreInvalidPaymentState.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreInvalidPaymentState : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    virtual ~FURuStoreInvalidPaymentState() {}

    virtual FString GetTypeName() override { return "FURuStoreInvalidPaymentState"; }
};
