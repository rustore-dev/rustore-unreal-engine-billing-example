// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGetPurchaseInfoNode.h"

using namespace RuStoreSDK;

UGetPurchaseInfoNode::UGetPurchaseInfoNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UGetPurchaseInfoNode* UGetPurchaseInfoNode::GetPurchaseInfoAsync(URuStoreBillingClient* target, FString purchaseId)
{
    auto node = NewObject<UGetPurchaseInfoNode>(GetTransientPackage());

    target->GetPurchaseInfo(
        purchaseId,
        [node](long requestId, TSharedPtr<FURuStorePurchase, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStorePurchase(), *error);
        }
    );

    return node;
}
