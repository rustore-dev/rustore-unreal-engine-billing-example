// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "FURuStoreProduct.h"
#include "FURuStorePurchase.h"
#include "FURuStoreUserAuthorizationStatus.h"
#include "AndroidJavaClass.h"

namespace RuStoreSDK
{
    class DataConverter
    {
    public:
        static FURuStoreProduct* ConvertProduct(AndroidJavaObject* obj);
        static FURuStoreProductSubscription* ConvertFURuStoreProductSubscription(AndroidJavaObject* obj);
        static FURuStoreSubscriptionPeriod* ConvertFURuStoreSubscriptionPeriod(AndroidJavaObject* obj);
        static FURuStorePurchase* ConvertPurchase(AndroidJavaObject* obj);
        static FURuStoreUserAuthorizationStatus* ConvertFURuStoreUserAuthorizationStatus(AndroidJavaObject* obj);
    };
}
