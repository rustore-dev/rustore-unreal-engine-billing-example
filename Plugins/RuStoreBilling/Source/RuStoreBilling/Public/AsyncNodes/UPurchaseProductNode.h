// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UPurchaseProductNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPurchaseProductPin, URuStorePaymentResultClass*, response, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UPurchaseProductNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FPurchaseProductPin Success;

    UPROPERTY(BlueprintAssignable)
    FPurchaseProductPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UPurchaseProductNode* PurchaseProductAsync(URuStoreBillingClient* target, FString productId, FString orderId, int quantity, FString developerPayload);
};
