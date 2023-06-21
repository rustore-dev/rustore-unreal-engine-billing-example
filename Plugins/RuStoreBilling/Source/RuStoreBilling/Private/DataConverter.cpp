#pragma once

#include "DataConverter.h"

FURequestMeta* DataConverter::ConvertRequestMeta(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto requestMeta = new FURequestMeta();
    requestMeta->traceId = obj->GetFString("traceId");

    return requestMeta;
}

FUProduct* DataConverter::ConvertProduct(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto product = new FUProduct();

    product->productId = obj->GetFString("productId");

    auto jproductType = obj->GetAJObject("productType", "Lru/rustore/sdk/billingclient/model/product/ProductType;");
    if (jproductType != nullptr)
    {
        int ordinal = jproductType->CallInt("ordinal");
        product->productType = static_cast<EUProductType>(ordinal);

        delete jproductType;
    }
        
    auto jproductStatus = obj->GetAJObject("productStatus", "Lru/rustore/sdk/billingclient/model/product/ProductStatus;");
    if (jproductStatus != nullptr)
    {
        int ordinal = jproductStatus->CallInt("ordinal");
        product->productStatus = static_cast<EUProductStatus>(ordinal);

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
        product->subscription = *ConvertFUProductSubscription(jsubscription);

        delete jsubscription;
    }
        
    return product;
}

FUDigitalShopGeneralError* DataConverter::ConvertFUDigitalShopGeneralError(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto error = new FUDigitalShopGeneralError();
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

FUProductSubscription* DataConverter::ConvertFUProductSubscription(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto subscription = new FUProductSubscription();

    auto jsubscriptionPeriod = obj->GetAJObject("subscriptionPeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jsubscriptionPeriod != nullptr)
    {
        subscription->subscriptionPeriod = *ConvertFUSubscriptionPeriod(jsubscriptionPeriod);
        delete jsubscriptionPeriod;
    }

    auto jfreeTrialPeriod = obj->GetAJObject("freeTrialPeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jfreeTrialPeriod != nullptr)
    {
        subscription->freeTrialPeriod = *ConvertFUSubscriptionPeriod(jfreeTrialPeriod);
        delete jfreeTrialPeriod;
    }

    auto jgracePeriod = obj->GetAJObject("gracePeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jgracePeriod != nullptr)
    {
        subscription->gracePeriod = *ConvertFUSubscriptionPeriod(jgracePeriod);
        delete jgracePeriod;
    }

    subscription->introductoryPrice = obj->GetFString("introductoryPrice");
    subscription->introductoryPriceAmount = obj->GetFString("introductoryPriceAmount");

    auto jintroductoryPricePeriod = obj->GetAJObject("introductoryPricePeriod", "Lru/rustore/sdk/billingclient/model/product/SubscriptionPeriod;");
    if (jintroductoryPricePeriod != nullptr)
    {
        subscription->introductoryPricePeriod = *ConvertFUSubscriptionPeriod(jintroductoryPricePeriod);
        delete jintroductoryPricePeriod;
    }

    return subscription;
}

FUSubscriptionPeriod* DataConverter::ConvertFUSubscriptionPeriod(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto subscriptionPeriod = new FUSubscriptionPeriod();

    subscriptionPeriod->years = obj->GetInt("years");
    subscriptionPeriod->months = obj->GetInt("months");
    subscriptionPeriod->days = obj->GetInt("days");
        
    return subscriptionPeriod;
}

FUPurchase* DataConverter::ConvertPurchase(AndroidJavaObject* obj)
{
    if (obj == nullptr) return nullptr;

    auto purchase = new FUPurchase();
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
        purchase->purchaseState = static_cast<EUPurchaseState>(ordinal);

        delete jpurchaseState;
    }

    purchase->developerPayload = obj->GetFString("developerPayload");
    purchase->subscriptionToken = obj->GetFString("subscriptionToken");

    return purchase;
}

void DataConverter::InitResponseWithCode(AndroidJavaObject* obj, FUResponseWithCode* response)
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
                auto item = ConvertFUDigitalShopGeneralError(e);
                response->errors.Add(*item);
            }
            delete e;
        }

        delete errors;
    }
}
