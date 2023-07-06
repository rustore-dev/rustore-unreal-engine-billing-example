// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreInvoiceResult.h"
#include "URuStorePaymentResultBase.h"
#include "URuStoreInvoiceResult.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API URuStoreInvoiceResult : public URuStorePaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FURuStoreInvoiceResult value;
};
