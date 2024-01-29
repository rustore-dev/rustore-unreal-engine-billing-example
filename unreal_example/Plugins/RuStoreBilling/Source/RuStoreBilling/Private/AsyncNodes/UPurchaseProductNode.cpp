// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPurchaseProductNode.h"

using namespace RuStoreSDK;

UPurchaseProductNode::UPurchaseProductNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UPurchaseProductNode* UPurchaseProductNode::PurchaseProductAsync(URuStoreBillingClient* target, FString productId, FString orderId, int quantity, FString developerPayload)
{
    auto node = NewObject<UPurchaseProductNode>(GetTransientPackage());
    
    target->PurchaseProduct(
        productId,
        orderId,
        quantity,
        developerPayload,
        [target, node](long requestId, TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe> response) {
            auto classObject = target->ConvertPaymentResult(response);
            if (classObject != nullptr)
            {
                node->Success.Broadcast(classObject, FURuStoreError());
            }
        },
        [target, node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            auto empty = NewObject<URuStorePaymentResultClass>(GetTransientPackage());
            node->Failure.Broadcast(empty, *error);
        }
    );

    return node;
}
