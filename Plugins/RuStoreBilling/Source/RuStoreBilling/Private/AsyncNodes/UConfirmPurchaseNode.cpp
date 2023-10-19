// Copyright Epic Games, Inc. All Rights Reserved.

#include "UConfirmPurchaseNode.h"

using namespace RuStoreSDK;

UConfirmPurchaseNode::UConfirmPurchaseNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UConfirmPurchaseNode* UConfirmPurchaseNode::ConfirmPurchaseAsync(URuStoreBillingClient* target, FString purchaseId)
{
    auto node = NewObject<UConfirmPurchaseNode>(GetTransientPackage());

    target->ConfirmPurchase(
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
