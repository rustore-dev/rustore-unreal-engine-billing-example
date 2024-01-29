// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGetProductsNode.h"

using namespace RuStoreSDK;

UGetProductsNode::UGetProductsNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UGetProductsNode* UGetProductsNode::GetProductsAsync(URuStoreBillingClient* target, TArray<FString> productIds)
{
    auto node = NewObject<UGetProductsNode>(GetTransientPackage());
    
    target->GetProducts(
        productIds,
        [node](long requestId, TSharedPtr<FURuStoreProductsResponse, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStoreProductsResponse(), *error);
        }
    );

    return node;
}
