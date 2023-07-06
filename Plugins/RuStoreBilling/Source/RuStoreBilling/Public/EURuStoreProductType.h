// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductType.generated.h"

UENUM(BlueprintType)
enum class EURuStoreProductType : uint8
{
    NON_CONSUMABLE UMETA(DisplayName = "NON_CONSUMABLE"),
    CONSUMABLE UMETA(DisplayName = "CONSUMABLE"),
    SUBSCRIPTION UMETA(DisplayName = "SUBSCRIPTION")
};
