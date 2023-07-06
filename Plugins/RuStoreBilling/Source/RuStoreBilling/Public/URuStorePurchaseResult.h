// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePurchaseResult.h"
#include "URuStorePaymentResultBase.h"
#include "URuStorePurchaseResult.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStorePurchaseResult : public URuStorePaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStorePurchaseResult value;
};
