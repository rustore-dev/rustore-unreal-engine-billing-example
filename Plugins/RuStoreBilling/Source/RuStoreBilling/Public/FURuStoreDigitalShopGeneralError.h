// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreDigitalShopGeneralError.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreDigitalShopGeneralError
{
    GENERATED_USTRUCT_BODY()

    FURuStoreDigitalShopGeneralError()
    {
        name = "";
        code = 0;
        description = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString name;

    UPROPERTY(BlueprintReadOnly)
    int code;

    UPROPERTY(BlueprintReadOnly)
    FString description;
};
