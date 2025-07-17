## История изменений

### Release 9.1.0
- Версия SDK billing 9.1.0.

### Release 9.0.1
- Версия SDK billing 9.0.1.

### Release 8.0.0
- Версия SDK billing 8.0.0.
- Метод `CheckPurchasesAvailability` в классе `URuStoreBillingClient` помечен как устаревший.
- Метод `CheckPurchasesAvailability` в событии `onSuccess` возвращает объект `FURuStorePurchaseAvailabilityResult`.
- Метод `SetAllowNativeErrorHandling` в классе `URuStoreBillingClient` помечен как устаревший.
- Поле `allowNativeErrorHandling` в структуре `FURuStoreBillingClientConfig` помечено как устаревшее.
- Добавлен метод `GetAuthorizationStatus`.

### Release 7.0.0
- Версия SDK billing 7.0.0.
- В класс `URuStoreBillingClient` добавлен метод `isRuStoreInstalled`.

### Release 6.1.0
- Версия SDK billing 6.1.0.

### Release 6.0
- Версия SDK billing 6.+.
- Добавлено поле sandbox у моделей результата покупки FURuStorePaymentResult.
- Убрано поле description у модели FURuStorePurchase.

### Release 5.0
- Версия SDK billing 5.+.
- Новый статус покупок PAUSED для подписок.

### Release 3.1
- Версия SDK billing 3.1.0.
- Добавлен функционал песочницы платежей (sandbox).
- Внутренние обновление SDK.

### Release 3.0
- Версия SDK billing 3.0.0.
- Обновлена функционал по новой цветовой гамме тёмной темы.
- Багфиксы.

### Release 0.3
- Версия SDK billing 2.1.1.
- Версия SDK core 0.1.10.

### Release 0.2
- Версия SDK billing 1.1.1.
- Версия SDK core 0.1.8.
