// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "FURuStoreProduct.h"
#include "FURuStorePurchase.h"
#include "FURuStoreRequestMeta.h"
#include "FURuStoreResponseWithCode.h"
#include "AndroidJavaClass.h"

namespace RuStoreSDK
{
    class DataConverter
    {
    public:
        static FURuStoreRequestMeta* ConvertRequestMeta(AndroidJavaObject* obj);
        static FURuStoreProduct* ConvertProduct(AndroidJavaObject* obj);
        static FURuStoreDigitalShopGeneralError* ConvertFURuStoreDigitalShopGeneralError(AndroidJavaObject* obj);
        static FURuStoreProductSubscription* ConvertFURuStoreProductSubscription(AndroidJavaObject* obj);
        static FURuStoreSubscriptionPeriod* ConvertFURuStoreSubscriptionPeriod(AndroidJavaObject* obj);
        static FURuStorePurchase* ConvertPurchase(AndroidJavaObject* obj);
        static void InitResponseWithCode(AndroidJavaObject* obj, FURuStoreResponseWithCode* response);
    };
}
