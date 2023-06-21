#pragma once

#include "CoreMinimal.h"
#include "FUPaymentResult.h"
#include "FUPurchaseResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FUPurchaseResult : public FUPaymentResult
{
    GENERATED_USTRUCT_BODY()

    FUPurchaseResult()
    {
        finishCode = EUPaymentFinishCode::RESULT_UNKNOWN;
        orderId = "";
        purchaseId = "";
        productId = "";
        subscriptionToken = "";
    }

    virtual ~FUPurchaseResult() {}

    UPROPERTY(BlueprintReadOnly)
    EUPaymentFinishCode finishCode;

    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;

    virtual FString GetTypeName() override { return "FUPurchaseResult"; }
};
