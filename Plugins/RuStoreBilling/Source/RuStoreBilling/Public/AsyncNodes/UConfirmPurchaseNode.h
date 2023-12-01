// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UConfirmPurchaseNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConfirmPurchasePin, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UConfirmPurchaseNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FConfirmPurchasePin Success;

    UPROPERTY(BlueprintAssignable)
    FConfirmPurchasePin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UConfirmPurchaseNode* ConfirmPurchaseAsync(URuStoreBillingClient* target, FString purchaseId);
};
