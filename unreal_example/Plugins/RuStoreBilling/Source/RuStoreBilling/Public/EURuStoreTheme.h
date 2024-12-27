// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreTheme.generated.h"

/*!
@brief Список доступных тем платежного интерфейса.
*/
UENUM(BlueprintType)
enum class EURuStoreTheme : uint8
{
    /*!
    @brief Тёмная тема.
    */
    DARK UMETA(DisplayName = "DARK"),
    
    /*!
    @brief Светлая тема.
    */
    LIGHT UMETA(DisplayName = "LIGHT")
};
