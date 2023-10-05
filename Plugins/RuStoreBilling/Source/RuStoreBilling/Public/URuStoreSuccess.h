// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreSuccess.h"
#include "URuStorePaymentResultClass.h"
#include "URuStoreSuccess.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreSuccess : public URuStorePaymentResultClass
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreSuccess value;
};
