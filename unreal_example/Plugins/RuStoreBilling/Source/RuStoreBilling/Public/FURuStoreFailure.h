// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStorePaymentResult.h"
#include "FURuStoreFailure.generated.h"

/*!
@brief При отправке запроса на оплату или получения статуса оплаты возникла проблема, невозможно установить статус покупки.
*/
USTRUCT(BlueprintType)
struct RUSTOREBILLING_API FURuStoreFailure : public FURuStorePaymentResult
{
    GENERATED_USTRUCT_BODY()

public:
    /*!
    @brief Конструктор.
    */
    FURuStoreFailure()
    {
        purchaseId = "";
        invoiceId = "";
        orderId = "";
        quantity = -1;
        productId = "";
        errorCode = -1;
        sandbox = false;
    }

    /*!
    @brief Идентификатор покупки.
    */
    UPROPERTY(BlueprintReadOnly)
    FString purchaseId;

    /*!
    @brief Идентификатор счёта.
    */
    UPROPERTY(BlueprintReadOnly)
    FString invoiceId;

    /*!
    @brief
        Уникальный идентификатор оплаты, сформированный приложением (необязательный параметр).
        Если вы укажете этот параметр в вашей системе, вы получите его в ответе при работе с API.
        Если не укажете, он будет сгенерирован автоматически (uuid).
        Максимальная длина 150 символов.
    */
    UPROPERTY(BlueprintReadOnly)
    FString orderId;

    /*!
    @brief Количество продукта (необязательный параметр).
    */
    UPROPERTY(BlueprintReadOnly)
    int quantity;

    /*!
    @brief Идентификатор продукта, который был присвоен продукту в консоли RuStore.
    */
    UPROPERTY(BlueprintReadOnly)
    FString productId;

    /*!
    @brief Код ошибки.
    */
    UPROPERTY(BlueprintReadOnly)
    int errorCode;

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
    virtual FString GetTypeName() override { return "FURuStoreFailure"; }
};
