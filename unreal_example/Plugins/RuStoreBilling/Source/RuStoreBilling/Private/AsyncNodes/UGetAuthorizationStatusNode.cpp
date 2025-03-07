// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGetAuthorizationStatusNode.h"

using namespace RuStoreSDK;

UGetAuthorizationStatusNode::UGetAuthorizationStatusNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UGetAuthorizationStatusNode* UGetAuthorizationStatusNode::GetAuthorizationStatusAsync(URuStoreBillingClient* target)
{
    auto node = NewObject<UGetAuthorizationStatusNode>(GetTransientPackage());
    
    target->GetAuthorizationStatus(
        [node](long requestId, TSharedPtr<FURuStoreUserAuthorizationStatus, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStoreUserAuthorizationStatus(), *error);
        }
    );

    return node;
}
