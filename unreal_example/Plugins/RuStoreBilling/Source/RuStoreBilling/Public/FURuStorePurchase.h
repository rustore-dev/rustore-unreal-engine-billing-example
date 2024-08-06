// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductType.h"
#include "EURuStorePurchaseState.h"
#include "FURuStorePurchase.generated.h"

USTRUCT(BlueprintType)
struct FURuStorePurchase
{
    GENERATED_USTRUCT_BODY()

    FURuStorePurchase()
    {
        purchaseId = "";
        productId = "";
        invoiceId = "";
        language = "";
        purchaseTime = FDateTime(0);
        orderId = "";
        amountLabel = "";
        amount = 0;
        currency = "";
        quantity = 0;
        purchaseState = EURuStorePurchaseState::CANCELLED;
        developerPayload = "";
        subscriptionToken = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    UPROPERTY(BlueprintReadOnly)
    FString language;

    UPROPERTY(BlueprintReadOnly)
    FDateTime purchaseTime;

    UPROPERTY(BlueprintReadOnly)
    FString purchaseTimeLabel;

    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    UPROPERTY(BlueprintReadOnly)
    FString amountLabel;

    UPROPERTY(BlueprintReadOnly)
    int amount;

    UPROPERTY(BlueprintReadOnly)
    FString currency;

    UPROPERTY(BlueprintReadOnly)
    int quantity;

    UPROPERTY(BlueprintReadOnly)
    EURuStorePurchaseState purchaseState;

    UPROPERTY(BlueprintReadOnly)
    EURuStoreProductType productType;

    UPROPERTY(BlueprintReadOnly)
    FString developerPayload;

    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;
};
