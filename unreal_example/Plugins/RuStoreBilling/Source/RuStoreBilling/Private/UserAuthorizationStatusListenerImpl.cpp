// Copyright Epic Games, Inc. All Rights Reserved.

#include "UserAuthorizationStatusListenerImpl.h"

using namespace RuStoreSDK;

UserAuthorizationStatusListenerImpl::~UserAuthorizationStatusListenerImpl()
{
}

FURuStoreUserAuthorizationStatus* UserAuthorizationStatusListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    return DataConverter::ConvertFURuStoreUserAuthorizationStatus(responseObject);
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_UserAuthorizationStatusWrapper_NativeOnFailure(JNIEnv* env, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<UserAuthorizationStatusListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_billingclient_wrappers_UserAuthorizationStatusWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<UserAuthorizationStatusListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
