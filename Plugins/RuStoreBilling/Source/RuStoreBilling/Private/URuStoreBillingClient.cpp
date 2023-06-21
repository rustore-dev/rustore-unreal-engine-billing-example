#include "URuStoreBillingClient.h"
#include "URuStoreCore.h"
#include "FeatureAvailabilityListenerImpl.h"
#include "ProductsResponseListenerImpl.h"
#include "PurchasesResponseListenerImpl.h"
#include "PaymentResultListenerImpl.h"
#include "ConfirmPurchaseResponseListenerImpl.h"
#include "DeletePurchaseResponseListenerImpl.h"
#include "PurchaseInfoResponseListenerImpl.h"

#include "UInvalidInvoice.h"
#include "UInvalidPaymentState.h"
#include "UInvalidPurchase.h"
#include "UInvoiceResult.h"
#include "UPurchaseResult.h"

using namespace std;

URuStoreBillingClient* URuStoreBillingClient::_instance = nullptr;
bool URuStoreBillingClient::_isInstanceInitialized = false;

bool URuStoreBillingClient::getIsInitialized() { return isInitialized; }

URuStoreBillingClient* URuStoreBillingClient::Instance()
{
    if (!_isInstanceInitialized)
    {
        _isInstanceInitialized = true;
        _instance = NewObject<URuStoreBillingClient>(GetTransientPackage());
    }

    return _instance;
}

void URuStoreBillingClient::SetAllowNativeErrorHandling(bool value)
{
    if (isInitialized)
    {
        _allowNativeErrorHandling = value;
        _clientWrapper->CallVoid("setErrorHandling", value);
    }
}

URuStoreBillingClient::URuStoreBillingClient()
{
}

URuStoreBillingClient::~URuStoreBillingClient()
{
}

bool URuStoreBillingClient::Init(FURuStoreBillingClientConfig config)
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (isInitialized) return false;

    _instance->AddToRoot();

    URuStoreCore::Instance()->Init();

    auto clientJavaClass = make_shared<AndroidJavaClass>("ru/rustore/unitysdk/billingclient/RuStoreUnityBillingClient");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("init", config.consoleApplicationId, config.deeplinkScheme, config.allowNativeErrorHandling, config.enableLogs);

    SetAllowNativeErrorHandling(config.allowNativeErrorHandling);
    isInitialized = true;

    return isInitialized;
}

void URuStoreBillingClient::Dispose()
{
    if (isInitialized)
    {
        isInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }

    URuStoreCore::LogInfo("rustore_debug", "URuStoreBillingClient Dispose");
}

void URuStoreBillingClient::BeginDestroy()
{
    Super::BeginDestroy();

    URuStoreCore::LogInfo("rustore_debug", "URuStoreBillingClient begin destroy");

    Dispose();
    if (_isInstanceInitialized) _isInstanceInitialized = false;
}

long URuStoreBillingClient::CheckPurchasesAvailability(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUFeatureAvailabilityResult*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new FeatureAvailabilityListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid(TEXT("checkPurchasesAvailability"), listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::GetProducts(TArray<FString> productIds, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUProductsResponse*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new ProductsResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid(TEXT("getProducts"), productIds, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::GetPurchases(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUPurchasesResponse*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new PurchasesResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid(TEXT("getPurchases"), listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUPaymentResult*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new PaymentResultListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("purchaseProduct", productId, orderId, quantity, developerPayload, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::ConfirmPurchase(FString purchaseId, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUConfirmPurchaseResponse*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new ConfirmPurchaseResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("confirmPurchase", purchaseId, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::DeletePurchase(FString purchaseId, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUDeletePurchaseResponse*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new DeletePurchaseResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("deletePurchase", purchaseId, listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreBillingClient::GetPurchaseInfo(FString purchaseId, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUPurchaseInfoResponse*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new PurchaseInfoResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("getPurchaseInfo", purchaseId, listener->GetJWrapper());

    return listener->GetId();
}


void URuStoreBillingClient::CheckPurchasesAvailability(int64& requestId)
{
    requestId = CheckPurchasesAvailability(
        [this](long requestId, FURuStoreError* error) {
            OnCheckPurchasesAvailabilityError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUFeatureAvailabilityResult* response) {
            OnCheckPurchasesAvailabilityResponse.Broadcast(requestId, *response);
        }
    );
}

void URuStoreBillingClient::GetProducts(TArray<FString> productIds, int64& requestId)
{
    requestId = GetProducts(
        productIds,
        [this](long requestId, FURuStoreError* error) {
            OnGetProductsError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUProductsResponse* response) {
            OnGetProductsResponse.Broadcast(requestId, *response);
        }
    );
}

void URuStoreBillingClient::GetPurchases(int64& requestId)
{
    requestId = GetPurchases(
        [this](long requestId, FURuStoreError* error) {
            OnGetPurchasesError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUPurchasesResponse* response) {
            OnGetPurchasesResponse.Broadcast(requestId, *response);
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
        [this](long requestId, FURuStoreError* error) {
            OnPurchaseProductError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUPaymentResult* response) {

            FString responseType = response->GetTypeName();
            if (responseType == "FUInvalidInvoice")
            {
                auto object = NewObject<UInvalidInvoice>(GetTransientPackage());
                object->value = *(FUInvalidInvoice*)response;
                OnPurchaseProductResponse.Broadcast(requestId, object);
            }
            else
            {
                if (responseType == "FUInvalidPaymentState")
                {
                    auto object = NewObject<UInvalidPaymentState>(GetTransientPackage());
                    object->value = *(FUInvalidPaymentState*)response;
                    OnPurchaseProductResponse.Broadcast(requestId, object);
                }
                else
                {
                    if (responseType == "FUInvalidPurchase")
                    {
                        auto object = NewObject<UInvalidPurchase>(GetTransientPackage());
                        object->value = *(FUInvalidPurchase*)response;
                        OnPurchaseProductResponse.Broadcast(requestId, object);
                    }
                    else
                    {
                        if (responseType == "FUInvoiceResult")
                        {
                            auto object = NewObject<UInvoiceResult>(GetTransientPackage());
                            object->value = *(FUInvoiceResult*)response;
                            OnPurchaseProductResponse.Broadcast(requestId, object);
                        }
                        else
                        {
                            if (responseType == "FUPurchaseResult")
                            {
                                auto object = NewObject<UPurchaseResult>(GetTransientPackage());
                                object->value = *(FUPurchaseResult*)response;
                                OnPurchaseProductResponse.Broadcast(requestId, object);
                            }
                        }
                    }
                }
            }
        }
    );
}

void URuStoreBillingClient::ConfirmPurchase(FString purchaseId, int64& requestId)
{
    requestId = ConfirmPurchase(
        purchaseId,
        [this](long requestId, FURuStoreError* error) {
            OnConfirmPurchaseError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUConfirmPurchaseResponse* response) {
            OnConfirmPurchaseResponse.Broadcast(requestId, *response);
        }
    );
}

void URuStoreBillingClient::DeletePurchase(FString purchaseId, int64& requestId)
{
    requestId = DeletePurchase(
        purchaseId,
        [this](long requestId, FURuStoreError* error) {
            OnDeletePurchaseError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUDeletePurchaseResponse* response) {
            OnDeletePurchaseResponse.Broadcast(requestId, *response);
        }
    );
}

void URuStoreBillingClient::GetPurchaseInfo(FString purchaseId, int64& requestId)
{
    requestId = GetPurchaseInfo(
        purchaseId,
        [this](long requestId, FURuStoreError* error) {
            OnPurchaseInfoError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUPurchaseInfoResponse* response) {
            OnPurchaseInfoResponse.Broadcast(requestId, *response);
        }
    );
}
