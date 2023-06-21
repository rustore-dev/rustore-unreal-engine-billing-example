#include "JavaMethodSignature.h"

template <typename T>
FString JavaMethodSignature::getName(T) { return TEXT(""); }
FString JavaMethodSignature::getName(IAndroidClasses* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(AndroidJavaObject* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(JavaActivity* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(JavaApplication* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(void) { return TEXT("V"); }
FString JavaMethodSignature::getName(bool) { return TEXT("Z"); }
FString JavaMethodSignature::getName(unsigned char) { return TEXT("B"); }
FString JavaMethodSignature::getName(char) { return TEXT("C"); }
FString JavaMethodSignature::getName(short) { return TEXT("S"); }
FString JavaMethodSignature::getName(int) { return TEXT("I"); }
FString JavaMethodSignature::getName(long) { return TEXT("J"); }
FString JavaMethodSignature::getName(float) { return TEXT("F"); }
FString JavaMethodSignature::getName(double) { return TEXT("D"); }
FString JavaMethodSignature::getName(FString&) { return TEXT("Ljava/lang/String;"); }
FString JavaMethodSignature::getName(TArray<FString>&) { return TEXT("[Ljava/lang/String;"); }

#if PLATFORM_ANDROID
template <> FString JavaMethodSignature::jtypeName<void> = "V";
template <> FString JavaMethodSignature::jtypeName<int> = "I";
template <> FString JavaMethodSignature::jtypeName<long> = "J";
template <> FString JavaMethodSignature::jtypeName<FString> = "Ljava/lang/String;";
//template <> FString JavaMethodSignature::jtypeName<AndroidJavaClass*> = "Ljava/lang/Class;";
template <> FString JavaMethodSignature::jtypeName<AndroidJavaObject*> = "Ljava/lang/Object;";
#endif
