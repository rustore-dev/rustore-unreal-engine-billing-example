#pragma once

#include "CoreMinimal.h"
#include "FURequestMeta.generated.h"

USTRUCT(BlueprintType)
struct FURequestMeta
{
    GENERATED_USTRUCT_BODY()

    FURequestMeta()
    {
        traceId = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString traceId;
};
