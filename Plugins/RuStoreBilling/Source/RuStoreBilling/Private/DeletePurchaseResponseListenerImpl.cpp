// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeletePurchaseResponseListenerImpl.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_DeletePurchaseResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<DeletePurchaseResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreBilling_DeletePurchaseResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<DeletePurchaseResponseListenerImpl*>(pointer);
        castobj->OnSuccess();
    }
}
#endif
