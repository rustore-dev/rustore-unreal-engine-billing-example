// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreFailure.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreFailure : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

public:
    FURuStoreFailure()
    {
        purchaseId = "";
        invoiceId = "";
        orderId = "";
        quantity = -1;
        productId = "";
        errorCode = -1;
        sandbox = false;
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
    int errorCode;

    UPROPERTY(BlueprintReadOnly)
    bool sandbox;

    virtual FString GetTypeName() override { return "FURuStoreFailure"; }
};
