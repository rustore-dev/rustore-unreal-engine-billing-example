// Copyright Epic Games, Inc. All Rights Reserved.

/***
Add this settings to Edit > Project Settings > Android > Advanced APK Packaging > Extra Settings for <activity> section (\n to separate lines)

<intent-filter>\n
    <action android:name="android.intent.action.VIEW" />\n
    <category android:name="android.intent.category.DEFAULT" />\n
    <category android:name="android.intent.category.BROWSABLE" />\n
    <data android:scheme="yourappscheme" />\n
</intent-filter>
***/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaObject.h"
#include "FURuStoreConfirmPurchaseResponse.h"
#include "FURuStoreDeletePurchaseResponse.h"
#include "FURuStoreFeatureAvailabilityResult.h"
#include "FURuStoreProductsResponse.h"
#include "FURuStorePurchaseInfoResponse.h"
#include "FURuStorePurchasesResponse.h"
#include "FURuStoreBillingClientConfig.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "FURuStorePaymentResult.h"
#include "URuStorePaymentResultBase.h"
#include "URuStoreBillingClient.generated.h"

using namespace RuStoreSDK;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreCheckPurchasesAvailabilityErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreCheckPurchasesAvailabilityResponseDelegate, int64, requestId, FURuStoreFeatureAvailabilityResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetProductsErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetProductsResponseDelegate, int64, requestId, FURuStoreProductsResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchasesErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchasesResponseDelegate, int64, requestId, FURuStorePurchasesResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStorePurchaseProductErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreUPurchaseProductResponseDelegate, int64, requestId, URuStorePaymentResultBase*, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreConfirmPurchaseErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreConfirmPurchaseResponseDelegate, int64, requestId, FURuStoreConfirmPurchaseResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreDeletePurchaseErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreDeletePurchaseResponseDelegate, int64, requestId, FURuStoreDeletePurchaseResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchaseInfoErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchaseInfoResponseDelegate, int64, requestId, FURuStorePurchaseInfoResponse, response);

UCLASS(Blueprintable)
class RUSTOREBILLING_API URuStoreBillingClient : public UObject, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreBillingClient* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;

public:
    static const FString PluginVersion;

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool getbIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    static URuStoreBillingClient* Instance();
    
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void SetAllowNativeErrorHandling(bool value);

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool Init(FURuStoreBillingClientConfig config);

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void Dispose();

    void ConditionalBeginDestroy();

    long CheckPurchasesAvailability(TFunction<void(long, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long GetProducts(TArray<FString> productIds, TFunction<void(long, TSharedPtr<FURuStoreProductsResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long GetPurchases(TFunction<void(long, TSharedPtr<FURuStorePurchasesResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, TFunction<void(long, TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long ConfirmPurchase(FString purchaseId, TFunction<void(long, TSharedPtr<FURuStoreConfirmPurchaseResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long DeletePurchase(FString purchaseId, TFunction<void(long, TSharedPtr<FURuStoreDeletePurchaseResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long GetPurchaseInfo(FString purchaseId, TFunction<void(long, TSharedPtr<FURuStorePurchaseInfoResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void CheckPurchasesAvailability(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreCheckPurchasesAvailabilityErrorDelegate OnCheckPurchasesAvailabilityError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreCheckPurchasesAvailabilityResponseDelegate OnCheckPurchasesAvailabilityResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void GetProducts(TArray<FString> productIds, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreGetProductsErrorDelegate OnGetProductsError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreGetProductsResponseDelegate OnGetProductsResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void GetPurchases(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreGetPurchasesErrorDelegate OnGetPurchasesError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreGetPurchasesResponseDelegate OnGetPurchasesResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStorePurchaseProductErrorDelegate OnPurchaseProductError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreUPurchaseProductResponseDelegate OnPurchaseProductResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void ConfirmPurchase(FString purchaseId, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreConfirmPurchaseErrorDelegate OnConfirmPurchaseError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreConfirmPurchaseResponseDelegate OnConfirmPurchaseResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void DeletePurchase(FString purchaseId, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreDeletePurchaseErrorDelegate OnDeletePurchaseError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreDeletePurchaseResponseDelegate OnDeletePurchaseResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void GetPurchaseInfo(FString purchaseId, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreGetPurchaseInfoErrorDelegate OnPurchaseInfoError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FRuStoreGetPurchaseInfoResponseDelegate OnPurchaseInfoResponse;
};
