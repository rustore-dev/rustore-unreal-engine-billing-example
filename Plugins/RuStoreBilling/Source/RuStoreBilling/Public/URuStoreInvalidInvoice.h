// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreInvalidInvoice.h"
#include "URuStorePaymentResultBase.h"
#include "URuStoreInvalidInvoice.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreInvalidInvoice : public URuStorePaymentResultBase
{
    GENERATED_BODY()
        
public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreInvalidInvoice value;
};
