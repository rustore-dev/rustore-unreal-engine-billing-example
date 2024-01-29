// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UCheckPurchasesAvailabilityNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPurchasesAvailabilityPin, FURuStoreFeatureAvailabilityResult, response, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UCheckPurchasesAvailabilityNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FCheckPurchasesAvailabilityPin Success;

    UPROPERTY(BlueprintAssignable)
    FCheckPurchasesAvailabilityPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UCheckPurchasesAvailabilityNode* CheckPurchasesAvailabilityAsync(URuStoreBillingClient* target);
};
