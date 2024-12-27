// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductStatus.generated.h"

/*!
@brief Статус продукта.
*/
UENUM(BlueprintType)
enum class EURuStoreProductStatus : uint8
{
    /*!
    @brief Продукт доступен.
    */
    ACTIVE UMETA(DisplayName = "ACTIVE"),
    
    /*!
    @brief Продукт недоступен.
    */
    INACTIVE UMETA(DisplayName = "INACTIVE")
};
