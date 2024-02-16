// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UGetPurchasesNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetPurchasesPin, FURuStorePurchasesResponse, response, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UGetPurchasesNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FGetPurchasesPin Success;

    UPROPERTY(BlueprintAssignable)
    FGetPurchasesPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UGetPurchasesNode* GetPurchasesAsync(URuStoreBillingClient* target);
};
