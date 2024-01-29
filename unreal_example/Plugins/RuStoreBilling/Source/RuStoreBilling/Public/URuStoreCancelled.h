// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreCancelled.h"
#include "URuStorePaymentResultClass.h"
#include "URuStoreCancelled.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreCancelled : public URuStorePaymentResultClass
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreCancelled value;
};
