#pragma once

#include "CoreMinimal.h"
#include "EUProductType.generated.h"

UENUM(BlueprintType)
enum class EUProductType : uint8
{
    NON_CONSUMABLE UMETA(DisplayName = "NON_CONSUMABLE"),
    CONSUMABLE UMETA(DisplayName = "CONSUMABLE"),
    SUBSCRIPTION UMETA(DisplayName = "SUBSCRIPTION")
};
