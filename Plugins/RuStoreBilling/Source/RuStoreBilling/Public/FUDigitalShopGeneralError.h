#pragma once

#include "CoreMinimal.h"
#include "FUDigitalShopGeneralError.generated.h"

USTRUCT(BlueprintType)
struct FUDigitalShopGeneralError
{
    GENERATED_USTRUCT_BODY()

    FUDigitalShopGeneralError()
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
