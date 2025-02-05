// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductType.h"
#include "EURuStorePurchaseState.h"
#include "FURuStorePurchase.generated.h"

/*!
@brief Информация о покупке.
*/
USTRUCT(BlueprintType)
struct FURuStorePurchase
{
    GENERATED_USTRUCT_BODY()
    
    /*!
    @brief Конструктор.
    */
    FURuStorePurchase()
    {
        purchaseId = "";
        productId = "";
        invoiceId = "";
        language = "";
        purchaseTime = FDateTime(0);
        orderId = "";
        amountLabel = "";
        amount = -1;
        currency = "";
        quantity = -1;
        purchaseState = EURuStorePurchaseState::UNKNOWN;
        productType = EURuStoreProductType::UNKNOWN;
        developerPayload = "";
        subscriptionToken = "";
    }

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
    @brief Язык, указанный с помощью BCP 47 кодирования.
    */
    UPROPERTY(BlueprintReadOnly)
    FString language;

    /*!
    @brief Время покупки.
    */
    UPROPERTY(BlueprintReadOnly)
    FDateTime purchaseTime;

    /*!
    @brief Время покупки в виде строки в формате %D.%M.%Y %H:%M:%S.
    */
    UPROPERTY(BlueprintReadOnly)
    FString purchaseTimeLabel;

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
    @brief Отформатированная цена покупки, включая валютный знак.
    */
    UPROPERTY(BlueprintReadOnly)
    FString amountLabel;

    /*!
    @brief Цена в минимальных единицах валюты (например в копейках).
    */
    UPROPERTY(BlueprintReadOnly)
    int amount;

    /*!
    @brief Код валюты ISO 4217.
    */
    UPROPERTY(BlueprintReadOnly)
    FString currency;

    /*!
    @brief Количество продукта.
    */
    UPROPERTY(BlueprintReadOnly)
    int quantity;

    /*!
    @brief Состояние покупки.
    */
    UPROPERTY(BlueprintReadOnly)
    EURuStorePurchaseState purchaseState;

    /*!
    @brief Тип продукта.
    */
    UPROPERTY(BlueprintReadOnly)
    EURuStoreProductType productType;

    /*!
    @brief Строка с дополнительной информацией о заказе, которую вы можете установить при инициализации процесса покупки.
    */
    UPROPERTY(BlueprintReadOnly)
    FString developerPayload;

    /*!
    @brief Токен для валидации покупки на сервере.
    */
    UPROPERTY(BlueprintReadOnly)
    FString subscriptionToken;
};
