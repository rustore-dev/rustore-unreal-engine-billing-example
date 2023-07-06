// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStorePaymentFinishCode.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreInvoiceResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreInvoiceResult : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

public:
    FURuStoreInvoiceResult()
    {
        invoiceId = "";
        finishCode = EURuStorePaymentFinishCode::RESULT_UNKNOWN;
    }

    virtual ~FURuStoreInvoiceResult() {}

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    UPROPERTY(BlueprintReadOnly)
    EURuStorePaymentFinishCode finishCode;

    virtual FString GetTypeName() override { return "FURuStoreInvoiceResult"; }
};
