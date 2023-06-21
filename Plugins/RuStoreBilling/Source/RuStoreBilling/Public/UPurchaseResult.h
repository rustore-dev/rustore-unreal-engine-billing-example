#pragma once

#include "CoreMinimal.h"
#include "FUPurchaseResult.h"
#include "UPaymentResultBase.h"
#include "UPurchaseResult.generated.h"

UCLASS(BlueprintType)
class RUSTOREBILLING_API UPurchaseResult : public UPaymentResultBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    FUPurchaseResult value;

/*    UPurchaseResult()
    {
        finishCode = EUPaymentFinishCode::RESULT_UNKNOWN;
        orderId = "";
        purchaseId = "";
        productId = "";
        subscriptionToken = "";
    }

    UPROPERTY(BlueprintReadOnly)
    EUPaymentFinishCode finishCode;

    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;*/
};
