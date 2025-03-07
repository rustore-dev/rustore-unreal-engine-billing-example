// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreBillingClient.h"
#include "UGetAuthorizationStatusNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAuthorizationStatusPin, FURuStoreUserAuthorizationStatus, response, FURuStoreError, error);

UCLASS()
class RUSTOREBILLING_API UGetAuthorizationStatusNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FGetAuthorizationStatusPin Success;

    UPROPERTY(BlueprintAssignable)
    FGetAuthorizationStatusPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Billing Client")
    static UGetAuthorizationStatusNode* GetAuthorizationStatusAsync(URuStoreBillingClient* target);
};
