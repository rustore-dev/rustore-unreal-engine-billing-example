// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UDeletePurchaseNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeletePurchasePin, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UDeletePurchaseNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FDeletePurchasePin Success;

    UPROPERTY(BlueprintAssignable)
    FDeletePurchasePin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UDeletePurchaseNode* DeletePurchaseAsync(URuStoreBillingClient* target, FString purchaseId);
};
