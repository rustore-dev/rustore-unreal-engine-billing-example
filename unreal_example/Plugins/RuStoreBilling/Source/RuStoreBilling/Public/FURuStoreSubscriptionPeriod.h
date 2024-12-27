// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreSubscriptionPeriod.generated.h"

/*!
@brief Информация о периоде подписки.
*/
USTRUCT(BlueprintType)
struct FURuStoreSubscriptionPeriod
{
    GENERATED_USTRUCT_BODY()

    /*!
    @brief Конструктор.
    */
    FURuStoreSubscriptionPeriod()
    {
        years = 1970;
        months = 1;
        days = 1;
    }

    /*!
    @brief Количество лет.
    */
    UPROPERTY(BlueprintReadOnly)
    int years;

    /*!
    @brief Количество месяцев.
    */
    UPROPERTY(BlueprintReadOnly)
    int months;

    /*!
    @brief Количество дней.
    */
    UPROPERTY(BlueprintReadOnly)
    int days;
};
