// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductType.h"
#include "EURuStoreProductStatus.h"
#include "FURuStoreProductSubscription.h"
#include "FURuStoreProduct.generated.h"

/*!
@brief Информация о продукте.
*/
USTRUCT(BlueprintType)
struct FURuStoreProduct
{
    GENERATED_USTRUCT_BODY()

    /*!
    @brief Конструктор.
    */
    FURuStoreProduct()
    {
        productId = "";
        productType = EURuStoreProductType::UNKNOWN;
        productStatus = EURuStoreProductStatus::INACTIVE;
        priceLabel = "";
        price = -1;
        currency = "";
        language = "";
        title = "";
        description = "";
        imageUrl = "";
        promoImageUrl = "";
    }

    /*!
    @brief Идентификатор продукта, который был присвоен продукту в консоли RuStore.
    */
    UPROPERTY(BlueprintReadOnly)
    FString productId;

    /*!
    @brief Тип продукта.
    */
    UPROPERTY(BlueprintReadOnly)
    EURuStoreProductType productType;

    /*!
    @brief Отформатированная цена товара, включая валютный знак на языке language.
    */
    UPROPERTY(BlueprintReadOnly)
    EURuStoreProductStatus productStatus;

    /*!
    @brief Статус продукта.
    */
    UPROPERTY(BlueprintReadOnly)
    FString priceLabel;

    /*!
    @brief Цена в минимальных единицах (например в копейках).
    */
    UPROPERTY(BlueprintReadOnly)
    int price;

    /*!
    @brief Код валюты ISO 4217.
    */
    UPROPERTY(BlueprintReadOnly)
    FString currency;

    /*!
    @brief Язык, указанный с помощью BCP 47 кодирования.
    */
    UPROPERTY(BlueprintReadOnly)
    FString language;

    /*!
    @brief Название продукта на языке language.
    */
    UPROPERTY(BlueprintReadOnly)
    FString title;

    /*!
    @brief Описание на языке language.
    */
    UPROPERTY(BlueprintReadOnly)
    FString description;

    /*!
    @brief Ссылка на картинку.
    */
    UPROPERTY(BlueprintReadOnly)
    FString imageUrl;

    /*!
    @brief Ссылка на промокартинку.
    */
    UPROPERTY(BlueprintReadOnly)
    FString promoImageUrl;

    /*!
    @brief Описание подписки, возвращается только для продуктов с типом EURUStoreProductType::SUBSCRIPTION.
    */
    UPROPERTY(BlueprintReadWrite)
    FURuStoreProductSubscription subscription;
};
