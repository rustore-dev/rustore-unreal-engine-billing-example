// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreFailure.h"
#include "URuStorePaymentResultClass.h"
#include "URuStoreFailure.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreFailure : public URuStorePaymentResultClass
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreFailure value;
};
