## RuStore Unreal Engine плагин для приема платежей через сторонние приложения

### [🔗 Документация разработчика][10]

Плагин RuStoreBilling помогает интегрировать в ваш проект механизм оплаты через сторонние приложения (например SberPay или СБП).

Репозиторий содержит плагины “RuStoreBilling” и “RuStoreCore”, а также демонстрационное приложение с примерами использования и настроек. Поддерживаются версии UE 4.26 и выше.


### Установка плагина в свой проект

1. Скопируйте содержимое папки _“Plugins”_ в папку _“Plugins”_ внутри своего проекта. Перезапустите Unreal Engine, в списке плагинов (Edit → Plugins → Project → Mobile) отметьте плагины “RuStoreBilling” и “RuStoreCore”.

2. В файле _“YourProject.Build.cs”_ в списке PublicDependencyModuleNames подключите модули модули “RuStoreCore” и “RuStoreBilling”.

3. В настройках проекта (Edit → Project Settings → Android) установить параметр Minimum SDK Version на уровень не ниже 24 и параметр Target SDK Version - не ниже 31.


### Сборка примера приложения

Вы можете ознакомиться с демонстрационным приложением содержащим представление работы всех методов sdk:
- [README](unreal_example/README.md)
- [unreal_example](https://gitflic.ru/project/rustore/rustore-unreal-engine-billing-example/file?file=unreal_example)


### Пересборка плагина

Если вам необходимо изменить код библиотек плагинов, вы можете внести изменения и пересобрать подключаемые .aar файлы.

1. Откройте в вашей IDE проект Android из папки _“unreal_plugin_libraries”_.

2. Внесите необходимые изменения.

3. Выполните сборку проекта командой gradle assemble.

При успешном выполнении сборки в папках _“unreal_example / Plugins / RuStoreBilling / Source / RuStoreBilling / ThirdParty / Android / libs”_ и _“unreal_example / Plugins / RuStoreCore / Source / RuStoreCore / ThirdParty / Android / libs”_ будут обновлены файлы:
- RuStoreUnityBillingClient.aar
- RuStoreUnityCore.aar


### История изменений

[CHANGELOG](CHANGELOG.md)


### Условия распространения

Данное программное обеспечение, включая исходные коды, бинарные библиотеки и другие файлы распространяется под лицензией MIT. Информация о лицензировании доступна в документе [MIT-LICENSE](MIT-LICENSE.txt).


### Техническая поддержка

Дополнительная помощь и инструкции доступны на странице [rustore.ru/help/](https://www.rustore.ru/help/) и по электронной почте [support@rustore.ru](mailto:support@rustore.ru).

[10]: https://www.rustore.ru/help/sdk/payments/unreal/6-1-0
