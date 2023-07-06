// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreInvalidPurchase.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreInvalidPurchase : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

public:
    FURuStoreInvalidPurchase()
    {
        purchaseId = "";
        invoiceId = "";
        orderId = "";
        quantity = 0;
        productId = "";
        errorCode = 0;
    }

    virtual ~FURuStoreInvalidPurchase() {}

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

    virtual FString GetTypeName() override { return "FURuStoreInvalidPurchase"; }
};
