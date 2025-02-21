// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreUserAuthorizationStatus.generated.h"

/*!
@brief Статус авторизации у пользователя.
*/
USTRUCT(BlueprintType)
struct FURuStoreUserAuthorizationStatus
{
    GENERATED_USTRUCT_BODY()

    /*!
    @brief Конструктор.
    */
    FURuStoreUserAuthorizationStatus()
    {
        authorized = false;
    }

    /*!
    @brief
        Значение статуса авторизации у пользователя.
        Если true, то пользователь авторизован в RuStore.
        Если false, то пользователь не авторизован.
        В случае использования SDK вне RuStore результат true также может вернуться,
        если в процессе оплаты пользователь авторизовался через VK ID и с момента авторизации прошло менее 15 минут.
    */
    UPROPERTY(BlueprintReadOnly)
    bool authorized;
};
