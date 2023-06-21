#pragma once

#include "CoreMinimal.h"
#include "FUInvalidInvoice.h"
#include "UPaymentResultBase.h"
#include "UInvalidInvoice.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API UInvalidInvoice : public UPaymentResultBase
{
    GENERATED_BODY()
        
public:
    UPROPERTY(BlueprintReadOnly)
    FUInvalidInvoice value;

    /*UInvalidInvoice()
    {
        invoiceId = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;*/
};
