// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConfirmPurchaseResponseListenerImpl.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_ConfirmPurchaseResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<ConfirmPurchaseResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_ConfirmPurchaseResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<ConfirmPurchaseResponseListenerImpl*>(pointer);
        castobj->OnSuccess();
    }
}
#endif
