// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreRequestMeta.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreRequestMeta
{
    GENERATED_USTRUCT_BODY()

    FURuStoreRequestMeta()
    {
        traceId = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString traceId;
};
