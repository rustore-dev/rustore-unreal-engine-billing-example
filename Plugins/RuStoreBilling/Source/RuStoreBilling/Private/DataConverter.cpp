// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataConverter.h"

using namespace RuStoreSDK;

FURuStoreProduct* DataConverter::ConvertProduct(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto product = new FURuStoreProduct();

    product->productId = obj->GetFString("productId");

    auto jproductType = obj->GetAJObject("productType", "Lru/rustore/sdk/billingclient/model/product/ProductType;");
    if (jproductType != nullptr)
    {
        int ordinal = jproductType->CallInt("ordinal");
        product->productType = static_cast<EURuStoreProductType>(ordinal);

        delete jproductType;
    }
        
    auto jproductStatus = obj->GetAJObject("productStatus", "Lru/rustore/sdk/billingclient/model/product/ProductStatus;");
    if (jproductStatus != nullptr)
    {
        int ordinal = jproductStatus->CallInt("ordinal");
        product->productStatus = static_cast<EURuStoreProductStatus>(ordinal);

        delete jproductStatus;
    }

    product->priceLabel = obj->GetFString("priceLabel");

    auto jprice = obj->GetAJObject("price", "Ljava/lang/Integer;");
    if (jprice != nullptr)
    {
        product->price = jprice->CallInt("intValue");
            
        delete jprice;
    }

    product->currency = obj->GetFString("currency");
    product->language = obj->GetFString("language");
    product->title = obj->GetFString("title");
    product->description = obj->GetFString("description");

    auto jimageUrl = obj->GetAJObject("imageUrl", "Landroid/net/Uri;");
    if (jimageUrl != nullptr)
    {
        product->imageUrl = jimageUrl->CallFString("toString");

        delete jimageUrl;
    }

    auto jpromoImageUrl = obj->GetAJObject("promoImageUrl", "Landroid/net/Uri;");
    if (jpromoImageUrl != nullptr)
    {
        product->promoImageUrl = jpromoImageUrl->CallFString("toString");

        delete jpromoImageUrl;
    }

    auto jsubscription = obj->GetAJObject("subscription", "Lru/rustore/sdk/billingclient/model/product/ProductSubscription;");
    if (jsubscription != nullptr)
    {
        product->subscription = *ConvertFURuStoreProductSubscription(jsubscription);

        delete jsubscription;
    }
        
    return product;
}

FURuStoreDigitalShopGeneralError* DataConverter::ConvertFURuStoreDigitalShopGeneralError(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto error = new FURuStoreDigitalShopGeneralError();
    error->name = obj->GetFString("name");

    auto codeObj = obj->GetAJObject("code");
    if (codeObj != nullptr)
    {
        error->code = codeObj->CallInt("intValue");
    }
    delete codeObj;

    error->description = obj->GetFString("description");

    return error;
}

FURuStoreProductSubscription* DataConverter::ConvertFURuStoreProductSubscription(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto subscription = new FURuStoreProductSubscription();

    auto jsubscriptionPeriod = obj->GetAJObject("subscriptionPeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jsubscriptionPeriod != nullptr)
    {
        subscription->subscriptionPeriod = *ConvertFURuStoreSubscriptionPeriod(jsubscriptionPeriod);
        delete jsubscriptionPeriod;
    }

    auto jfreeTrialPeriod = obj->GetAJObject("freeTrialPeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jfreeTrialPeriod != nullptr)
    {
        subscription->freeTrialPeriod = *ConvertFURuStoreSubscriptionPeriod(jfreeTrialPeriod);
        delete jfreeTrialPeriod;
    }

    auto jgracePeriod = obj->GetAJObject("gracePeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jgracePeriod != nullptr)
    {
        subscription->gracePeriod = *ConvertFURuStoreSubscriptionPeriod(jgracePeriod);
        delete jgracePeriod;
    }

    subscription->introductoryPrice = obj->GetFString("introductoryPrice");
    subscription->introductoryPriceAmount = obj->GetFString("introductoryPriceAmount");

    auto jintroductoryPricePeriod = obj->GetAJObject("introductoryPricePeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jintroductoryPricePeriod != nullptr)
    {
        subscription->introductoryPricePeriod = *ConvertFURuStoreSubscriptionPeriod(jintroductoryPricePeriod);
        delete jintroductoryPricePeriod;
    }

    return subscription;
}

FURuStoreSubscriptionPeriod* DataConverter::ConvertFURuStoreSubscriptionPeriod(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto subscriptionPeriod = new FURuStoreSubscriptionPeriod();

    subscriptionPeriod->years = obj->GetInt("years");
    subscriptionPeriod->months = obj->GetInt("months");
    subscriptionPeriod->days = obj->GetInt("days");
        
    return subscriptionPeriod;
}

FURuStorePurchase* DataConverter::ConvertPurchase(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto purchase = new FURuStorePurchase();
    purchase->purchaseId = obj->GetFString("purchaseId");
    purchase->productId = obj->GetFString("productId");
    purchase->invoiceId = obj->GetFString("invoiceId");
    purchase->description = obj->GetFString("description");
    purchase->language = obj->GetFString("language");

    auto jpurchaseTime = obj->GetAJObject("purchaseTime", "Ljava/util/Date;");
    if (jpurchaseTime != nullptr)
    {
        FString dateString = jpurchaseTime->CallFString("toString");

        auto javaClass = new AndroidJavaClass("com/Plugins/RuStoreCore/RuStoreCoreUtils");
        FString iso8601 = javaClass->CallStaticFString("ConvertToISO8601", jpurchaseTime);

        if (FDateTime::ParseIso8601(*iso8601, purchase->purchaseTime))
        {
            purchase->purchaseTimeLabel = purchase->purchaseTime.ToString(TEXT("%D.%M.%Y %H:%M:%S"));
        }
        else
        {
            purchase->purchaseTimeLabel = dateString;
        }


        delete jpurchaseTime;
    }

    purchase->orderId = obj->GetFString("orderId");
    purchase->amountLabel = obj->GetFString("amountLabel");

    auto jamount = obj->GetAJObject("amount", "Ljava/lang/Integer;");
    if (jamount != nullptr)
    {
        purchase->amount = jamount->CallInt("intValue");

        delete jamount;
    }

    purchase->currency = obj->GetFString("currency");

    auto jquantity = obj->GetAJObject("quantity", "Ljava/lang/Integer;");
    if (jquantity != nullptr)
    {
        purchase->quantity = jquantity->CallInt("intValue");

        delete jquantity;
    }
        
    auto jpurchaseState = obj->GetAJObject("purchaseState", "Lru/rustore/sdk/billingclient/model/purchase/PurchaseState;");
    if (jpurchaseState != nullptr)
    {
        int ordinal = jpurchaseState->CallInt("ordinal");
        purchase->purchaseState = static_cast<EURuStorePurchaseState>(ordinal);

        delete jpurchaseState;
    }

    purchase->developerPayload = obj->GetFString("developerPayload");
    purchase->subscriptionToken = obj->GetFString("subscriptionToken");

    return purchase;
}

void DataConverter::InitResponseWithCode(AndroidJavaObject* obj, FURuStoreResponseWithCode* response)
{
    response->code = obj->GetInt("code");
    response->errorMessage = obj->GetFString("errorMessage");
    response->errorDescription = obj->GetFString("errorDescription");

    auto errors = obj->GetAJObject("errors", "Ljava/util/List;");
    if (errors != nullptr)
    {
        auto size = errors->CallInt("size");
        for (int i = 0; i < size; i++)
        {
            auto e = errors->CallAJObject("get", i);
            if (e != nullptr)
            {
                auto item = ConvertFURuStoreDigitalShopGeneralError(e);
                response->errors.Add(*item);
            }
            delete e;
        }

        delete errors;
    }
}
