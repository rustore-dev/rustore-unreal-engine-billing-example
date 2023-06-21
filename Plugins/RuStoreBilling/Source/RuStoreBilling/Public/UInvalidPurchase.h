#pragma once

#include "CoreMinimal.h"
#include "FUInvalidPurchase.h"
#include "UPaymentResultBase.h"
#include "UInvalidPurchase.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API UInvalidPurchase : public UPaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FUInvalidPurchase value;

    /*UInvalidPurchase()
    {
        purchaseId = "";
        invoiceId = "";
        orderId = "";
        quantity = 0;
        productId = "";
        errorCode = 0;
    }

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    UPROPERTY(BlueprintReadOnly)
    int quantity;

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    int errorCode;*/
};
