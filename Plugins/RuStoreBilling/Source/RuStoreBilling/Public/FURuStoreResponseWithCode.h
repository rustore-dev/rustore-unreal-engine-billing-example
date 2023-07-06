// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreDigitalShopGeneralError.h"
#include "FURuStoreResponseWithCode.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreResponseWithCode
{
    GENERATED_USTRUCT_BODY()

    FURuStoreResponseWithCode()
    {
        code = 0;
        errorMessage = "";
        errorDescription = "";
    }

    UPROPERTY(BlueprintReadOnly)
    int code;

    UPROPERTY(BlueprintReadOnly)
    FString errorMessage;

    UPROPERTY(BlueprintReadOnly)
    FString errorDescription;

    UPROPERTY(BlueprintReadOnly)
    TArray<FURuStoreDigitalShopGeneralError> errors;
};
