// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreInvalidPaymentState.h"
#include "URuStorePaymentResultBase.h"
#include "URuStoreInvalidPaymentState.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreInvalidPaymentState : public URuStorePaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreInvalidPaymentState value;
};
