// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreCancelled.generated.h"

/*!
@brief Запрос на покупку отправлен, при этом пользователь закрыл «платёжную шторку» на своём устройстве, и результат оплаты неизвестен.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreCancelled : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    /*!
    @brief Конструктор.
    */
    FURuStoreCancelled()
    {
        purchaseId = "";
        sandbox = false;
    }

    /*!
    @brief Идентификатор покупки.
    */
    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    /*!
    @brief
        Определяет, является ли платёж тестовым.
        Значения могут быть true или false, где true обозначает тестовый платёж, а false – реальный.
    */
    UPROPERTY(BlueprintReadOnly)
    bool sandbox;

    /*!
    @brief Получить имя типа.
    */
    virtual FString GetTypeName() override { return "FURuStoreCancelled"; }
};
