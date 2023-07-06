// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStorePaymentFinishCode.generated.h"

UENUM(BlueprintType)
enum class EURuStorePaymentFinishCode : uint8
{
    SUCCESSFUL_PAYMENT UMETA(DisplayName = "SUCCESSFUL_PAYMENT"),
    CLOSED_BY_USER UMETA(DisplayName = "CLOSED_BY_USER"),
    UNHANDLED_FORM_ERROR UMETA(DisplayName = "UNHANDLED_FORM_ERROR"),
    PAYMENT_TIMEOUT UMETA(DisplayName = "PAYMENT_TIMEOUT"),
    DECLINED_BY_SERVER UMETA(DisplayName = "DECLINED_BY_SERVER"),
    RESULT_UNKNOWN UMETA(DisplayName = "RESULT_UNKNOWN")
};
