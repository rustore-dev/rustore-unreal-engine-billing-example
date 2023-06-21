#pragma once

#include "CoreMinimal.h"
#include "FUPaymentResult.h"
#include "FUInvalidInvoice.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FUInvalidInvoice : public FUPaymentResult
{
    GENERATED_USTRUCT_BODY()

    FUInvalidInvoice()
    {
        invoiceId = "";
    }

    virtual ~FUInvalidInvoice() {}

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    virtual FString GetTypeName() override { return "FUInvalidInvoice"; }
};
