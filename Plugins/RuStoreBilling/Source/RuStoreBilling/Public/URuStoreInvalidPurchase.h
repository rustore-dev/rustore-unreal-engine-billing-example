// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreInvalidPurchase.h"
#include "URuStorePaymentResultBase.h"
#include "URuStoreInvalidPurchase.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreInvalidPurchase : public URuStorePaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreInvalidPurchase value;
};
