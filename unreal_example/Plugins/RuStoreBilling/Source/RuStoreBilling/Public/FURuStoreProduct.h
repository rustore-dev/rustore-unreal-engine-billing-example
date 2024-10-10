// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreProductType.h"
#include "EURuStoreProductStatus.h"
#include "FURuStoreProductSubscription.h"
#include "FURuStoreProduct.generated.h"

USTRUCT(BlueprintType)
struct FURuStoreProduct
{
    GENERATED_USTRUCT_BODY()

    FURuStoreProduct()
    {
        productId = "";
        productType = EURuStoreProductType::UNKNOWN;
        productStatus = EURuStoreProductStatus::INACTIVE;
        priceLabel = "";
        price = -1;
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
    EURuStoreProductType productType;

    UPROPERTY(BlueprintReadOnly)
    EURuStoreProductStatus productStatus;

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
    FURuStoreProductSubscription subscription;
};
