#pragma once

#include "CoreMinimal.h"
#include "EUProductStatus.generated.h"

UENUM(BlueprintType)
enum class EUProductStatus : uint8
{
    ACTIVE UMETA(DisplayName = "ACTIVE"),
    INACTIVE UMETA(DisplayName = "INACTIVE")
};
