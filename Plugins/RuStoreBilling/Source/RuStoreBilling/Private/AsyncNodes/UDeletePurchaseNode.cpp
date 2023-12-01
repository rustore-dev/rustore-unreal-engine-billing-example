// Copyright Epic Games, Inc. All Rights Reserved.

#include "UDeletePurchaseNode.h"

using namespace RuStoreSDK;

UDeletePurchaseNode::UDeletePurchaseNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UDeletePurchaseNode* UDeletePurchaseNode::DeletePurchaseAsync(URuStoreBillingClient* target, FString purchaseId)
{
    auto node = NewObject<UDeletePurchaseNode>(GetTransientPackage());

    target->DeletePurchase(
        purchaseId,
        [node](long requestId) {
            node->Success.Broadcast(FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(*error);
        }
    );

    return node;
}
