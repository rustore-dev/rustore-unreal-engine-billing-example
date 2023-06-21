/***
Add this settings to Edit > Project Settings > Android > Advanced APK Packaging > Extra Settings for <activity section> (\n to separate lines)

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
#include "UObject/Interface.h"
#include "UObject/ScriptMacros.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include <functional>
#include <map>
#include <memory>

#include "AndroidJavaObject.h"
#include "FUConfirmPurchaseResponse.h"
#include "FUDeletePurchaseResponse.h"
#include "FUFeatureAvailabilityResult.h"
#include "FUProductsResponse.h"
#include "FUPurchaseInfoResponse.h"
#include "FUPurchasesResponse.h"
#include "FURuStoreBillingClientConfig.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "FUPaymentResult.h"
#include "UPaymentResultBase.h"
#include "URuStoreBillingClient.generated.h"

using namespace std;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPurchasesAvailabilityErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckPurchasesAvailabilityResponseDelegate, int64, requestId, FUFeatureAvailabilityResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetProductsErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetProductsResponseDelegate, int64, requestId, FUProductsResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetPurchasesErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetPurchasesResponseDelegate, int64, requestId, FUPurchasesResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPurchaseProductErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUPurchaseProductResponseDelegate, int64, requestId, UPaymentResultBase*, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConfirmPurchaseErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConfirmPurchaseResponseDelegate, int64, requestId, FUConfirmPurchaseResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeletePurchaseErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeletePurchaseResponseDelegate, int64, requestId, FUDeletePurchaseResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetPurchaseInfoErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetPurchaseInfoResponseDelegate, int64, requestId, FUPurchaseInfoResponse, response);

UCLASS(Blueprintable)
class RUSTOREBILLING_API URuStoreBillingClient : public UObject, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreBillingClient* _instance;
    static bool _isInstanceInitialized;

    bool _allowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;

    bool isInitialized = false;

public:
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool getIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    static URuStoreBillingClient* Instance();
    
    void SetAllowNativeErrorHandling(bool value);

    URuStoreBillingClient();
    ~URuStoreBillingClient();

    void BeginDestroy();

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool Init(FURuStoreBillingClientConfig config);

    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void Dispose();

    long CheckPurchasesAvailability(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUFeatureAvailabilityResult*)> onSuccess);
    long GetProducts(TArray<FString> productIds, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUProductsResponse*)> onSuccess);
    long GetPurchases(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUPurchasesResponse*)> onSuccess);
    long PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUPaymentResult*)> onSuccess);
    long ConfirmPurchase(FString purchaseId, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUConfirmPurchaseResponse*)> onSuccess);
    long DeletePurchase(FString purchaseId, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUDeletePurchaseResponse*)> onSuccess);
    long GetPurchaseInfo(FString purchaseId, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUPurchaseInfoResponse*)> onSuccess);


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void CheckPurchasesAvailability(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FCheckPurchasesAvailabilityErrorDelegate OnCheckPurchasesAvailabilityError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FCheckPurchasesAvailabilityResponseDelegate OnCheckPurchasesAvailabilityResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void GetProducts(TArray<FString> productIds, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FGetProductsErrorDelegate OnGetProductsError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FGetProductsResponseDelegate OnGetProductsResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void GetPurchases(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FGetPurchasesErrorDelegate OnGetPurchasesError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FGetPurchasesResponseDelegate OnGetPurchasesResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FPurchaseProductErrorDelegate OnPurchaseProductError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FUPurchaseProductResponseDelegate OnPurchaseProductResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void ConfirmPurchase(FString purchaseId, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FConfirmPurchaseErrorDelegate OnConfirmPurchaseError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FConfirmPurchaseResponseDelegate OnConfirmPurchaseResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void DeletePurchase(FString purchaseId, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FDeletePurchaseErrorDelegate OnDeletePurchaseError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FDeletePurchaseResponseDelegate OnDeletePurchaseResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void GetPurchaseInfo(FString purchaseId, int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FGetPurchaseInfoErrorDelegate OnPurchaseInfoError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Billing Client")
    FGetPurchaseInfoResponseDelegate OnPurchaseInfoResponse;
};
