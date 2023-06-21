#pragma once

#include "CoreMinimal.h"
#include "JavaMethodSignature.h"
#include "JavaTypeConverter.h"

#if PLATFORM_ANDROID

#include <../../../Launch/Public/Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>

#endif

class RUSTORECORE_API AndroidJavaObject : public IAndroidClasses
{
private:
    FString className = "";
    FString ExtractName();
    bool isAttachThread = false;
    bool isGlobalRef = true;

#if PLATFORM_ANDROID
    JNIEnv* env = nullptr;
    jclass javaClass = nullptr;
    jobject javaObject = nullptr;

    static JavaVM* CurrentJavaVM()
    {
        JavaVM* CurrentJavaVM = nullptr;
        FAndroidApplication::GetJavaEnv()->GetJavaVM(&CurrentJavaVM);
        return CurrentJavaVM;
    }
#endif

public:
    AndroidJavaObject(FString className, bool asGlobalRef = true);
    AndroidJavaObject(FString className, long cppPointer, bool asGlobalRef = true);
#if PLATFORM_ANDROID
    AndroidJavaObject(jthrowable throwable);
    AndroidJavaObject(jobject javaObject);
    AndroidJavaObject(jobject javaObject, FString asInterface);
    AndroidJavaObject(jclass javaClass, jobject javaObject);

    jobject GetJObject();
#endif

    virtual ~AndroidJavaObject();

    FString GetName() override;

    static AndroidJavaObject* GetStaticAJObject(FString fieldName, FString className);

    template<typename T>
    T* Get(FString fieldName);
    int GetInt(FString fieldName);
    FString GetFString(FString fieldName);
    int GetEnum(FString fieldName, FString signature);
    AndroidJavaObject* GetAJObject(FString fieldName, FString signature = "");

    void SetInterfaceName(FString asInterface);
    bool AttachCurrentThread();
    AndroidJavaObject* UpdateToGlobalRef();

    FString CallJavaClassFString(FString methodName);

    template<typename... Args>
    void CallVoid(FString methodName, Args... args)
    {
#if PLATFORM_ANDROID
        FString methodSignature = JavaMethodSignature::MakeVoid(args...);
        jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
        FJavaWrapper::CallVoidMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif
    }

    template<typename... Args>
    int CallInt(FString methodName, Args... args)
    {
        int result = 0;
#if PLATFORM_ANDROID
        FString methodSignature = JavaMethodSignature::MakeInt(args...);
        jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
        result = (int)env->CallIntMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif
        return result;
    }

    template<typename... Args>
    int CallLong(FString methodName, Args... args)
    {
        long result = 0;
#if PLATFORM_ANDROID
        FString methodSignature = JavaMethodSignature::MakeLong(args...);
        jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);
        result = (long)env->CallLongMethod(javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
#endif
        return result;
    }

    template<typename... Args>
    FString CallFString(FString methodName, Args... args)
    {
        FString result = "";
#if PLATFORM_ANDROID
        FString methodSignature = JavaMethodSignature::MakeFString(args...);
        jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

        jstring strResult = (jstring)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
        const char* str = env->GetStringUTFChars(strResult, 0);
        result = FJavaHelper::FStringFromParam(env, strResult);
#endif
        return result;
    }

    template<typename... Args>
    AndroidJavaObject* CallAJClass(FString methodName, Args... args)
    {
        AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
        FString methodSignature = JavaMethodSignature::MakeAJClass(args...);
        jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

        jobject localRef = FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
        result = new AndroidJavaObject(localRef);
        result->UpdateToGlobalRef();
#endif
        return result;
    }

    template<typename... Args>
    AndroidJavaObject* CallAJObject(FString methodName, Args... args)
    {
        AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
        FString methodSignature = JavaMethodSignature::MakeAJObject(args...);
        jmethodID javaMethodID = FJavaWrapper::FindMethod(env, javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature), false);

        jobject localRef = (jobject)FJavaWrapper::CallObjectMethod(env, javaObject, javaMethodID, JavaTypeConverter::SetValue(env, args)...);
        result = new AndroidJavaObject(localRef);
        result->UpdateToGlobalRef();
#endif
        return result;
    }
};
