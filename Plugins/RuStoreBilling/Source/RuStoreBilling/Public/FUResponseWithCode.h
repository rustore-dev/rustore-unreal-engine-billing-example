#pragma once

#include "CoreMinimal.h"
#include "FUDigitalShopGeneralError.h"
#include "FUResponseWithCode.generated.h"

USTRUCT(BlueprintType)
struct FUResponseWithCode
{
    GENERATED_USTRUCT_BODY()

    FUResponseWithCode()
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
    TArray<FUDigitalShopGeneralError> errors;
};
