// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreSuccess.generated.h"

/*!
@brief Результат успешного завершения покупки цифрового товара.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreSuccess : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

    /*!
    @brief Конструктор.
    */
    FURuStoreSuccess()
    {
        orderId = "";
        purchaseId = "";
        productId = "";
        invoiceId = "";
        subscriptionToken = "";
        sandbox = false;
    }

    /*!
    @brief
        Уникальный идентификатор оплаты, сформированный приложением (опциональный параметр).
        Если вы укажете этот параметр в вашей системе, вы получите его в ответе при работе с API.
        Если не укажете, он будет сгенерирован автоматически (uuid).
        Максимальная длина 150 символов.
    */
    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    /*!
    @brief Идентификатор покупки.
    */
    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    /*!
    @brief Идентификатор продукта, который был присвоен продукту в консоли RuStore.
    */
    UPROPERTY(BlueprintReadOnly)
    FString productId;

    /*!
    @brief Идентификатор счёта.
    */
    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    /*!
    @brief Токен для валидации покупки на сервере.
    */
    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;

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
    virtual FString GetTypeName() override { return "FURuStoreSuccess"; }
};
