#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID

#include <../../../Launch/Public/Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>
#include <jni.h>
#include <android/log.h>

#include <iostream>
#include <string>
#include <vector>

#endif

#include "IAndroidClasses.h"
//#include "AndroidJavaClass.h"
#include "AndroidJavaObject.h"
#include "JavaActivity.h"
#include "JavaApplication.h"

//class AndroidJavaClass;
class AndroidJavaObject;
class JavaActivity;
class JavaApplication;

class RUSTORECORE_API JavaMethodSignature
{
public:
    template <typename T>
    static FString getName(T);
    static FString getName(IAndroidClasses* obj);
    static FString getName(AndroidJavaObject* obj);
    static FString getName(JavaActivity* obj);
    static FString getName(JavaApplication* obj);
    static FString getName(void);
    static FString getName(bool);
    static FString getName(unsigned char);
    static FString getName(char);
    static FString getName(short);
    static FString getName(int);
    static FString getName(long);
    static FString getName(float);
    static FString getName(double);
    static FString getName(FString&);
    static FString getName(TArray<FString>&);

    template <typename T> static FString jtypeName;
#if PLATFORM_ANDROID
    template <> static FString jtypeName<void>;
    template <> static FString jtypeName<int>;
    template <> static FString jtypeName<long>;
    template <> static FString jtypeName<FString>;
    template <> static FString jtypeName<IAndroidClasses*>;
    //template <> static FString jtypeName<AndroidJavaClass*>;
    template <> static FString jtypeName<AndroidJavaObject*>;
#endif

    template <typename... Args>
    static FString Constuct(Args... args)
    {
        FString body = "";
        for (const auto& arg : TArray<FString>{ args... })
        {
            body += arg;
        }

        return FString::Printf(TEXT("(%s)"), *body);
    }

    template <typename T, typename... Args>
    static FString Make(Args... args)
    {
        return Constuct(getName(args)...) + jtypeName<T>;
    }

    template <typename... Args>
    static FString MakeVoid(Args... args)
    {
        return Constuct(getName(args)...) + jtypeName<void>;
    }

    template <typename... Args>
    static FString MakeInt(Args... args)
    {
        return Constuct(getName(args)...) + jtypeName<int>;
    }

    template <typename... Args>
    static FString MakeLong(Args... args)
    {
        return Constuct(getName(args)...) + jtypeName<long>;
    }

    template <typename... Args>
    static FString MakeFString(Args... args)
    {
        return Constuct(getName(args)...) + jtypeName<FString>;
    }

    template <typename... Args>
    static FString MakeAJClass(Args... args)
    {
        return Constuct(getName(args)...) + "Ljava/lang/Class;";// jtypeName<AndroidJavaClass*>;
    }

    template <typename... Args>
    static FString MakeAJObject(Args... args)
    {
        return Constuct(getName(args)...) + jtypeName<AndroidJavaObject*>;
    }
};
