// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConfirmPurchaseResponseListenerImpl.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_ConfirmPurchaseResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<ConfirmPurchaseResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_ConfirmPurchaseResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<ConfirmPurchaseResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
