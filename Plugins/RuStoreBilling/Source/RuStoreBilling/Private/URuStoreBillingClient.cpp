// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreBillingClient.h"
#include "URuStoreCore.h"
#include "FeatureAvailabilityListenerImpl.h"
#include "ProductsResponseListenerImpl.h"
#include "PurchasesResponseListenerImpl.h"
#include "PaymentResultListenerImpl.h"
#include "ConfirmPurchaseResponseListenerImpl.h"
#include "DeletePurchaseResponseListenerImpl.h"
#include "PurchaseInfoResponseListenerImpl.h"
#include "URuStoreCancelled.h"
#include "URuStoreFailure.h"
#include "URuStoreInvalidPaymentState.h"
#include "URuStoreSuccess.h"

using namespace RuStoreSDK;

const FString URuStoreBillingClient::PluginVersion = "0.2";
URuStoreBillingClient* URuStoreBillingClient::_instance = nullptr;
bool URuStoreBillingClient::_bIsInstanceInitialized = false;

URuStorePaymentResultClass* URuStoreBillingClient::ConvertPaymentResult(TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe> value)
{
    FString responseType = value->GetTypeName();
    if (responseType == "FURuStoreSuccess")
    {
        auto object = NewObject<URuStoreSuccess>(GetTransientPackage());
        object->value = *StaticCastSharedPtr<FURuStoreSuccess>(value);
        return(object);
    }
    else
    {
        if (responseType == "FURuStoreCancelled")
        {
            auto object = NewObject<URuStoreCancelled>(GetTransientPackage());
            object->value = *StaticCastSharedPtr<FURuStoreCancelled>(value);
            return(object);
        }
        else
        {
            if (responseType == "FURuStoreFailure")
            {
                auto object = NewObject<URuStoreFailure>(GetTransientPackage());
                object->value = *StaticCastSharedPtr<FURuStoreFailure>(value);
                return(object);
            }
            else
            {
                auto object = NewObject<URuStoreInvalidPaymentState>(GetTransientPackage());
                object->value = *StaticCastSharedPtr<FURuStoreInvalidPaymentState>(value);
                return(object);
            }
        }
    }

    return nullptr;
}

bool URuStoreBillingClient::GetIsInitialized()
{
    return bIsInitialized;
}

URuStoreBillingClient* URuStoreBillingClient::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreBillingClient>(GetTransientPackage());
    }

    return _instance;
}

void URuStoreBillingClient::SetAllowNativeErrorHandling(bool value)
{
    if (bIsInitialized)
    {
        _bAllowNativeErrorHandling = value;
        _clientWrapper->CallVoid("setErrorHandling", value);
    }
}

bool URuStoreBillingClient::Init(FURuStoreBillingClientConfig config)
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    URuStoreCore::Instance()->Init();

    auto clientJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/billingclient/RuStoreUnityBillingClient");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("init", config.consoleApplicationId, config.deeplinkScheme, config.allowNativeErrorHandling, config.enableLogs, FString("unreal"));

    SetAllowNativeErrorHandling(config.allowNativeErrorHandling);

    return bIsInitialized = true;
}

void URuStoreBillingClient::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }
}

void URuStoreBillingClient::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

long URuStoreBillingClient::CheckPurchasesAvailability(TFunction<void(long, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new FeatureAvailabilityListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid(TEXT("checkPurchasesAvailability"), listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::GetProducts(TArray<FString>& productIds, TFunction<void(long, TSharedPtr<FURuStoreProductsResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new ProductsResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid(TEXT("getProducts"), productIds, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::GetPurchases(TFunction<void(long, TSharedPtr<FURuStorePurchasesResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new PurchasesResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid(TEXT("getPurchases"), listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, TFunction<void(long, TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new PaymentResultListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("purchaseProduct", productId, orderId, quantity, developerPayload, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::ConfirmPurchase(FString purchaseId, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new ConfirmPurchaseResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("confirmPurchase", purchaseId, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::DeletePurchase(FString purchaseId, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new DeletePurchaseResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("deletePurchase", purchaseId, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::GetPurchaseInfo(FString purchaseId, TFunction<void(long, TSharedPtr<FURuStorePurchase, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new PurchaseInfoResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("getPurchaseInfo", purchaseId, listener->GetJWrapper());

    return listener->GetId();
}


void URuStoreBillingClient::CheckPurchasesAvailability(int64& requestId)
{
    requestId = CheckPurchasesAvailability(
        [this](long requestId, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe> response) {
            OnCheckPurchasesAvailabilityResponse.Broadcast(requestId, *response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnCheckPurchasesAvailabilityError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreBillingClient::GetProducts(TArray<FString> productIds, int64& requestId)
{
    requestId = GetProducts(
        productIds,
        [this](long requestId, TSharedPtr<FURuStoreProductsResponse, ESPMode::ThreadSafe> response) {
            OnGetProductsResponse.Broadcast(requestId, *response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnGetProductsError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreBillingClient::GetPurchases(int64& requestId)
{
    requestId = GetPurchases(
        [this](long requestId, TSharedPtr<FURuStorePurchasesResponse, ESPMode::ThreadSafe> response) {
            OnGetPurchasesResponse.Broadcast(requestId, *response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnGetPurchasesError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreBillingClient::PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, int64& requestId)
{
    requestId = PurchaseProduct(
        productId,
        orderId,
        quantity,
        developerPayload,
        [this](long requestId, TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe> response) {
            auto classObject = ConvertPaymentResult(response);
            if (classObject != nullptr)
            {
                OnPurchaseProductResponse.Broadcast(requestId, classObject);
            }
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnPurchaseProductError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreBillingClient::ConfirmPurchase(FString purchaseId, int64& requestId)
{
    requestId = ConfirmPurchase(
        purchaseId,
        [this](long requestId) {
            OnConfirmPurchaseResponse.Broadcast(requestId);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnConfirmPurchaseError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreBillingClient::DeletePurchase(FString purchaseId, int64& requestId)
{
    requestId = DeletePurchase(
        purchaseId,
        [this](long requestId) {
            OnDeletePurchaseResponse.Broadcast(requestId);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnDeletePurchaseError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreBillingClient::GetPurchaseInfo(FString purchaseId, int64& requestId)
{
    requestId = GetPurchaseInfo(
        purchaseId,
        [this](long requestId, TSharedPtr<FURuStorePurchase, ESPMode::ThreadSafe> response) {
            OnPurchaseInfoResponse.Broadcast(requestId, *response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnPurchaseInfoError.Broadcast(requestId, *error);
        }
    );
}
