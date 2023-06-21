#pragma once

#include "CoreMinimal.h"
#include "FUInvoiceResult.h"
#include "UPaymentResultBase.h"
#include "UInvoiceResult.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API UInvoiceResult : public UPaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FUInvoiceResult value;

    /*UInvoiceResult()
    {
        invoiceId = "";
        finishCode = EUPaymentFinishCode::RESULT_UNKNOWN;
    }

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    UPROPERTY(BlueprintReadOnly)
    EUPaymentFinishCode finishCode;*/
};
