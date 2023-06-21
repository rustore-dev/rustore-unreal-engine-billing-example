#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "FUProduct.h"
#include "FUPurchase.h"
#include "FURequestMeta.h"
#include "FUResponseWithCode.h"
#include "AndroidJavaClass.h"

class DataConverter
{
public:
    static FURequestMeta* ConvertRequestMeta(AndroidJavaObject* obj);
    static FUProduct* ConvertProduct(AndroidJavaObject* obj);
    static FUDigitalShopGeneralError* ConvertFUDigitalShopGeneralError(AndroidJavaObject* obj);
    static FUProductSubscription* ConvertFUProductSubscription(AndroidJavaObject* obj);
    static FUSubscriptionPeriod* ConvertFUSubscriptionPeriod(AndroidJavaObject* obj);
    static FUPurchase* ConvertPurchase(AndroidJavaObject* obj);
    static void InitResponseWithCode(AndroidJavaObject* obj, FUResponseWithCode* response);
};
