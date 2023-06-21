#pragma once

#include "CoreMinimal.h"
#include "EUPaymentFinishCode.h"
#include "FUPaymentResult.h"
#include "FUInvoiceResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FUInvoiceResult : public FUPaymentResult
{
    GENERATED_USTRUCT_BODY()

public:
    FUInvoiceResult()
    {
        invoiceId = "";
        finishCode = EUPaymentFinishCode::RESULT_UNKNOWN;
    }

    virtual ~FUInvoiceResult() {}

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    UPROPERTY(BlueprintReadOnly)
    EUPaymentFinishCode finishCode;

    virtual FString GetTypeName() override { return "FUInvoiceResult"; }
};
