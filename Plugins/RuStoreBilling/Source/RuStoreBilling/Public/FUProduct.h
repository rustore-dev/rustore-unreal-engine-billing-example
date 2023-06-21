#pragma once

#include "CoreMinimal.h"
#include "EUProductType.h"
#include "EUProductStatus.h"
#include "FUProductSubscription.h"
#include "FUProduct.generated.h"

USTRUCT(BlueprintType)
struct FUProduct
{
    GENERATED_USTRUCT_BODY()

    FUProduct()
    {
        productId = "";
        productType = EUProductType::CONSUMABLE;
        productStatus = EUProductStatus::INACTIVE;
        priceLabel = "";
        price = 0;
        currency = "";
        language = "";
        title = "";
        description = "";
        imageUrl = "";
        promoImageUrl = "";
    }

    UPROPERTY(BlueprintReadOnly)
    FString productId;

    UPROPERTY(BlueprintReadOnly)
    EUProductType productType;

    UPROPERTY(BlueprintReadOnly)
    EUProductStatus productStatus;

    UPROPERTY(BlueprintReadOnly)
    FString priceLabel;

    UPROPERTY(BlueprintReadOnly)
    int price;

    UPROPERTY(BlueprintReadOnly)
    FString currency;

    UPROPERTY(BlueprintReadOnly)
    FString language;

    UPROPERTY(BlueprintReadOnly)
    FString title;

    UPROPERTY(BlueprintReadOnly)
    FString description;

    UPROPERTY(BlueprintReadOnly)
    FString imageUrl;

    UPROPERTY(BlueprintReadOnly)
    FString promoImageUrl;

    UPROPERTY(BlueprintReadWrite)
    FUProductSubscription subscription;
};
