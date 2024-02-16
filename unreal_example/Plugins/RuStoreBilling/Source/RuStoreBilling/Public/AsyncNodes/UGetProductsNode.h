// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UGetProductsNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetProductsPin, FURuStoreProductsResponse, response, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UGetProductsNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FGetProductsPin Success;

    UPROPERTY(BlueprintAssignable)
    FGetProductsPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UGetProductsNode* GetProductsAsync(URuStoreBillingClient* target, TArray<FString> productIds);
};
