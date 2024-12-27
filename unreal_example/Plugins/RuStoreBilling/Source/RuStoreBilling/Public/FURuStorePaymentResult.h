// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.generated.h"

/*!
@brief Родительский класс результатов покупки.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    /*!
    @brief Деструктор.
    */
    virtual ~FURuStorePaymentResult() {}

    /*!
    @brief Получить имя типа.
    */
    virtual FString GetTypeName() { return "FURuStorePaymentResult"; }
};
