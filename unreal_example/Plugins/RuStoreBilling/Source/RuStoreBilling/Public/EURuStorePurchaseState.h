// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStorePurchaseState.generated.h"

UENUM(BlueprintType)
enum class EURuStorePurchaseState : uint8
{
    CREATED UMETA(DisplayName = "CREATED"),
    INVOICE_CREATED UMETA(DisplayName = "INVOICE_CREATED"),
    CONFIRMED UMETA(DisplayName = "CONFIRMED"),
    PAID UMETA(DisplayName = "PAID UMETA"),
    CANCELLED UMETA(DisplayName = "CANCELLED"),
    CONSUMED UMETA(DisplayName = "CONSUMED"),
    CLOSED UMETA(DisplayName = "CLOSED"),
    TERMINATED UMETA(DisplayName = "TERMINATED")
};
