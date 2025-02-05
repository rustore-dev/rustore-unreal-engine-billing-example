// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStorePurchaseState.generated.h"

/*!
@brief Состояние покупки.
*/
UENUM(BlueprintType)
enum class EURuStorePurchaseState : uint8
{
    /*!
    @brief Покупка создана.
    */
    CREATED UMETA(DisplayName = "CREATED"),

    /*!
    @brief Создан счёт на оплату, покупка ожидает оплаты.
    */
    INVOICE_CREATED UMETA(DisplayName = "INVOICE_CREATED"),
    
    /*!
    @brief Платеж за непотребляемый товар успешно совершен
    */
    CONFIRMED UMETA(DisplayName = "CONFIRMED"),
    
    /*!
    @brief
        Покупка ожидает подтверждения от разработчика.
        Только покупки потребляемого товара — промежуточный статус, средства на счёте покупателя зарезервированы.
    */
    PAID UMETA(DisplayName = "PAID UMETA"),
    
    /*!
    @brief
        Покупка отменена — оплата не была произведена или был совершен возврат средств покупателю.
        Для подписок после возврата средств покупка не переходит в CANCELLED.
    */
    CANCELLED UMETA(DisplayName = "CANCELLED"),
    
    /*!
    @brief Платеж за потребляемый товар успешно совершен.
    */
    CONSUMED UMETA(DisplayName = "CONSUMED"),
    
    /*!
    @brief Для подписок — подписка перешла в HOLD период или закрылась.
    */
    CLOSED UMETA(DisplayName = "CLOSED"),
    
    /*!
    @brief Для подписок — подписка перешла в HOLD период.
    */
    PAUSED UMETA(DisplayName = "PAUSED"),
    
    /*!
    @brief Подписка закрылась.
    */
    TERMINATED UMETA(DisplayName = "TERMINATED"),
    
    /*!
    @brief Значение не определено.
    */
    UNKNOWN UMETA(DisplayName = "UNKNOWN")
};
