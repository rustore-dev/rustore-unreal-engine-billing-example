// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGetPurchasesNode.h"

using namespace RuStoreSDK;

UGetPurchasesNode::UGetPurchasesNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UGetPurchasesNode* UGetPurchasesNode::GetPurchasesAsync(URuStoreBillingClient* target)
{
    auto node = NewObject<UGetPurchasesNode>(GetTransientPackage());

    target->GetPurchases(
        [node](long requestId, TSharedPtr<FURuStorePurchasesResponse, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStorePurchasesResponse(), *error);
        }
    );

    return node;
}
