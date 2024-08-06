// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreSuccess.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreSuccess : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    FURuStoreSuccess()
    {
        orderId = "";
        purchaseId = "";
        productId = "";
        invoiceId = "";
        subscriptionToken = "";
        sandbox = false;
    }

    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;

    UPROPERTY(BlueprintReadOnly)
    bool sandbox;

    virtual FString GetTypeName() override { return "FURuStoreSuccess"; }
};
