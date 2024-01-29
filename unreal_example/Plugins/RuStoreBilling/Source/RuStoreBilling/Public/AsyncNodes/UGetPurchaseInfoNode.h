// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UGetPurchaseInfoNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetPurchaseInfoPin, FURuStorePurchase, response, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UGetPurchaseInfoNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FGetPurchaseInfoPin Success;

    UPROPERTY(BlueprintAssignable)
    FGetPurchaseInfoPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UGetPurchaseInfoNode* GetPurchaseInfoAsync(URuStoreBillingClient* target, FString purchaseId);
};
