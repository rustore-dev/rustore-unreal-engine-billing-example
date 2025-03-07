// Copyright Epic Games, Inc. All Rights Reserved.

#include "UCheckPurchasesAvailabilityNode.h"

using namespace RuStoreSDK;

UCheckPurchasesAvailabilityNode::UCheckPurchasesAvailabilityNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UCheckPurchasesAvailabilityNode* UCheckPurchasesAvailabilityNode::CheckPurchasesAvailabilityAsync(URuStoreBillingClient* target)
{
    auto node = NewObject<UCheckPurchasesAvailabilityNode>(GetTransientPackage());
    
    target->CheckPurchasesAvailability(
        [node](long requestId, TSharedPtr<FURuStorePurchaseAvailabilityResult, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStorePurchaseAvailabilityResult(), *error);
        }
    );

    return node;
}
