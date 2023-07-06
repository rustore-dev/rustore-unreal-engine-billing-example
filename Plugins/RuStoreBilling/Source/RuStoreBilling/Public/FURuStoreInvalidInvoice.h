// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreInvalidInvoice.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreInvalidInvoice : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    FURuStoreInvalidInvoice()
    {
        invoiceId = "";
    }

    virtual ~FURuStoreInvalidInvoice() {}

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    virtual FString GetTypeName() override { return "FURuStoreInvalidInvoice"; }
};
