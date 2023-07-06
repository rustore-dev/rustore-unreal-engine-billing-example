// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStorePurchaseResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStorePurchaseResult : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    FURuStorePurchaseResult()
    {
        finishCode = EURuStorePaymentFinishCode::RESULT_UNKNOWN;
        orderId = "";
        purchaseId = "";
        productId = "";
        subscriptionToken = "";
    }

    virtual ~FURuStorePurchaseResult() {}

    UPROPERTY(BlueprintReadOnly)
    EURuStorePaymentFinishCode finishCode;

    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;

    virtual FString GetTypeName() override { return "FURuStorePurchaseResult"; }
};
