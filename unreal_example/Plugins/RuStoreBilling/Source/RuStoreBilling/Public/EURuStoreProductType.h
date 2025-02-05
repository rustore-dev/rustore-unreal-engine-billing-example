// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductType.generated.h"

/*!
@brief Тип продукта.
*/
UENUM(BlueprintType)
enum class EURuStoreProductType : uint8
{
    /*!
    @brief Непотребляемый продукт (может быть приобретен один раз).
    */
    NON_CONSUMABLE UMETA(DisplayName = "NON_CONSUMABLE"),
    
    /*!
    @brief Потребляемый продукт.
    */
    CONSUMABLE UMETA(DisplayName = "CONSUMABLE"),
    
    /*!
    @brief Подписка.
    */
    SUBSCRIPTION UMETA(DisplayName = "SUBSCRIPTION"),
    
    /*!
    @brief Значение не определено.
    */
    UNKNOWN UMETA(DisplayName = "UNKNOWN")
};
