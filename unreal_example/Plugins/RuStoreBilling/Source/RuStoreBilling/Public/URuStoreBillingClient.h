// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaObject.h"
#include "EURuStoreTheme.h"
#include "FURuStoreProductsResponse.h"
#include "FURuStorePurchase.h"
#include "FURuStorePurchaseAvailabilityResult.h"
#include "FURuStorePurchasesResponse.h"
#include "FURuStoreBillingClientConfig.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "FURuStorePaymentResult.h"
#include "URuStorePaymentResultClass.h"
#include "URuStoreBillingClient.generated.h"

using namespace RuStoreSDK;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreCheckPurchasesAvailabilityErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreCheckPurchasesAvailabilityResponseDelegate, int64, requestId, FURuStorePurchaseAvailabilityResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetProductsErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetProductsResponseDelegate, int64, requestId, FURuStoreProductsResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchasesErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchasesResponseDelegate, int64, requestId, FURuStorePurchasesResponse, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStorePurchaseProductErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreUPurchaseProductResponseDelegate, int64, requestId, URuStorePaymentResultClass*, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreConfirmPurchaseErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRuStoreConfirmPurchaseResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreDeletePurchaseErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRuStoreDeletePurchaseResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchaseInfoErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetPurchaseInfoResponseDelegate, int64, requestId, FURuStorePurchase, response);

/*!
@brief Класс реализует API для интегрирации платежей в мобильное приложение.
*/
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
    /*!
    @brief Версия плагина.
    */
    static const FString PluginVersion;

    /*!
    @brief Проверка инициализации платежного клиента.
    @return Возвращает true, если синглтон инициализирован, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool GetIsInitialized();

    /*!
    @brief
        Получить экземпляр URuStoreBillingClient.
    @return
        Возвращает указатель на единственный экземпляр URuStoreBillingClient (реализация паттерна Singleton).
        Если экземпляр еще не создан, создает его.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    static URuStoreBillingClient* Instance();
    
    /*!
    @brief Обработка ошибок в нативном SDK.
    @param value true — разрешает обработку ошибок, false — запрещает.
    */
    [[deprecated("This method is deprecated. This method only works for flows with an authorized user in RuStore.")]]
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void SetAllowNativeErrorHandling(bool value);

    /*!
    @brief
        Выполняет инициализацию синглтона URuStoreBillingClient.
        Параметры инициализации задаются объектом типа FURuStoreBillingClientConfig.
    @param config
        Объект класса FURuStoreBillingClientConfig.
        Содержит параметры инициализации платежного клиента.
    @return Возвращает true, если инициализация была успешно выполнена, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool Init(FURuStoreBillingClientConfig config);

    /*!
    @brief Деинициализация синглтона, если дальнейшая работа с объектом больше не планируется.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void Dispose();

    void ConditionalBeginDestroy();

    URuStorePaymentResultClass* ConvertPaymentResult(TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe> value);

    /*!
    @brief
        Проверка доступности платежей.
        Если все условия выполняются, возвращается FURuStorePurchaseAvailabilityResult::isAvailable == true.
        В противном случае возвращается FURuStorePurchaseAvailabilityResult::isAvailable == false.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект FURuStorePurchaseAvailabilityResult с информцаией о доступности оплаты.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    [[deprecated("This method is deprecated. This method only works for flows with an authorized user in RuStore.")]]
    long CheckPurchasesAvailability(TFunction<void(long, TSharedPtr<FURuStorePurchaseAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Получение списка продуктов, добавленных в ваше приложение через RuStore консоль.
    @param productIds
        Список идентификаторов продуктов (задаются при создании продукта в консоли разработчика).
        Список продуктов имеет ограничение в размере 1000 элементов.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект FURuStoreProductsResponse с информцаией о продуктах.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long GetProducts(TArray<FString>& productIds, TFunction<void(long, TSharedPtr<FURuStoreProductsResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Получение списка покупок пользователя.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект типа FURuStorePurchasesResponse с информцаией о покупках.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long GetPurchases(TFunction<void(long, TSharedPtr<FURuStorePurchasesResponse, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Покупка продукта.
    @param productId Идентификатор продукта, который был присвоен продукту в RuStore Консоли (обязательный параметр).
    @param orderId
        Уникальный идентификатор оплаты, сформированный приложением (опциональный параметр).
        Если вы укажете этот параметр в вашей системе, вы получите его в ответе при работе с API.
        Если не укажете, он будет сгенерирован автоматически (uuid).
        Максимальная длина 150 символов.
    @param quantity
        Количество продукта (1 или более).
    @param developerPayload Строка с дополнительной информацией о заказе, которую вы можете установить при инициализации процесса покупки.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект FURuStorePaymentResult с информацией о результате покупки.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long PurchaseProduct(FString productId, FString orderId, int quantity, FString developerPayload, TFunction<void(long, TSharedPtr<FURuStorePaymentResult, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief
        Потребление (подтверждение) покупки.
        Запрос на потребление (подтверждение) покупки должен сопровождаться выдачей товара.
    @param purchaseId Идентификатор покупки.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long ConfirmPurchase(FString purchaseId, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Отмена покупки.
    @param purchaseId Идентификатор покупки.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает объект FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long DeletePurchase(FString purchaseId, TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Получение информации о покупке.
    @param purchaseId Идентификатор покупки.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект типа FURuStorePurchase с информцаией о покупке.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает объект FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long GetPurchaseInfo(FString purchaseId, TFunction<void(long, TSharedPtr<FURuStorePurchase, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief
        SDK поддерживает динамическую смены темы.
        Установить тему интерфейса.
    @param theme Новая тема, заданная значением из перечисления EURuStoreTheme.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    void SetTheme(EURuStoreTheme theme);
    
    /*!
    @brief SDK
        SDK поддерживает динамическую смены темы.
        Получить текущую тему интерфейса.
    @return Текущая тема, заданная значением из перечисления EURuStoreTheme.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    EURuStoreTheme GetTheme();

    /*!
    @brief Проверка установлен ли на устройстве пользователя RuStore.
    @return Возвращает true, если RuStore установлен, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore Billing Client")
    bool IsRuStoreInstalled();

    // 
    [[deprecated("This method is deprecated. This method only works for flows with an authorized user in RuStore.")]]
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
