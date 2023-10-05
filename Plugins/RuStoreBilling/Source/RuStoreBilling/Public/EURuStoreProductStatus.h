// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductStatus.generated.h"

UENUM(BlueprintType)
enum class EURuStoreProductStatus : uint8
{
    ACTIVE UMETA(DisplayName = "ACTIVE"),
    INACTIVE UMETA(DisplayName = "INACTIVE")
};
