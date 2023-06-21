#pragma once

#include "CoreMinimal.h"
#include "FUPaymentResult.h"
#include "FUInvalidPurchase.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FUInvalidPurchase : public FUPaymentResult
{
    GENERATED_USTRUCT_BODY()

public:
    FUInvalidPurchase()
    {
        purchaseId = "";
        invoiceId = "";
        orderId = "";
        quantity = 0;
        productId = "";
        errorCode = 0;
    }

    virtual ~FUInvalidPurchase() {}

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
    int errorCode;

    virtual FString GetTypeName() override { return "FUInvalidPurchase"; }
};
