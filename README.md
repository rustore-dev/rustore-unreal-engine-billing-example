## RuStore Unreal Engine плагин для приема платежей через сторонние приложения

[### Документация разработчика](https://help.rustore.ru/rustore/for_developers/developer-documentation/sdk_payments/unreal)

Плагин RuStoreBilling помогает интегрировать в ваш проект механизм оплаты через сторонние приложения (например SberPay или СБП).

Репозиторий содержит плагины “RuStoreBilling” и “RuStoreCore”, а также демонстрационное приложение с примерами использования и настроек. Поддерживаются версии UE 4.26 и выше.


### Установка плагина в свой проект

1. Скопируйте содержимое папки _“Plugins”_ в папку _“Plugins”_ внутри своего проекта. Перезапустите Unreal Engine, в списке плагинов (Edit → Plugins → Project → Mobile) отметьте плагины “RuStoreBilling” и “RuStoreCore”.

2. В файле _“YourProject.Build.cs”_ в списке PublicDependencyModuleNames подключите модули модули “RuStoreCore” и “RuStoreBilling”.

3. В настройках проекта (Edit → Project Settings → Android) установить параметр Minimum SDK Version на уровень не ниже 24 и параметр Target SDK Version - не ниже 31.


### Сборка примера приложения

1. В файле ресурсов _“Source / RuStoreBillingApp / rustore_billing_values.xml”_ в параметре “rustore_app_id” укажите consoleApplicationId вашего проекта.

2. В настройках проекта (Edit → Project Settings → Platforms → Android) укажите имя пакета “Android Package Name” и параметры подписи “Distribution Signing” вашего приложения в RuStore. Подробная информация о публикации приложений в RuStore доступна на странице [help](https://help.rustore.ru/rustore/for_developers/publishing_and_verifying_apps).

3. Настройте перечень продуктов в списке “ProductIds” в виджете “UI / BillingClientWidgetBlueprint”. Подробная информация о добавлении продуктов доступна на странице ["Как создать платный товар в приложении"](https://help.rustore.ru/rustore/for_developers/Monetization/How-create-paid-product-in-application).


### Техническая поддержка

Дополнительная помощь и инструкции доступны на странице [help.rustore.ru](https://help.rustore.ru/).
