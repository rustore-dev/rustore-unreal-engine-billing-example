// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeletePurchaseResponseListenerImpl.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_DeletePurchaseResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<DeletePurchaseResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_DeletePurchaseResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<DeletePurchaseResponseListenerImpl*>(pointer);
        castobj->OnSuccess();
    }
}
#endif
