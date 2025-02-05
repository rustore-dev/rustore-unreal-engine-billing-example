// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreInvalidPaymentState.generated.h"

/*!
@brief
    Ошибка работы SDK платежей.
    Может возникнуть, в случае некорректного обратного deeplink.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreInvalidPaymentState : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()
    
    /*!
    @brief Деструктор.
    */
    virtual ~FURuStoreInvalidPaymentState() {}

    /*!
    @brief Получить имя типа.
    */
    virtual FString GetTypeName() override { return "FURuStoreInvalidPaymentState"; }
};
