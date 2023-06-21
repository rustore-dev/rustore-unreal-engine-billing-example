#pragma once

#include "CoreMinimal.h"
#include "EUPurchaseState.h"
#include "FUPurchase.generated.h"

USTRUCT(BlueprintType)
struct FUPurchase
{
    GENERATED_USTRUCT_BODY()

    FUPurchase()
    {
        purchaseId = "";
        productId = "";
        invoiceId = "";
        description = "";
        language = "";
        purchaseTime = FDateTime(0);
        orderId = "";
        amountLabel = "";
        amount = 0;
        currency = "";
        quantity = 0;
        purchaseState = EUPurchaseState::CANCELLED;
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
    FString description;

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
    EUPurchaseState purchaseState;

    UPROPERTY(BlueprintReadOnly)
    FString developerPayload;

    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;
};
