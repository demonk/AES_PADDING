#include <jni.h>
#include <cstring>
#include <malloc.h>
#include "aes.h"

#ifdef _DEBUG
#define __JNI_LOG_TAG__ ("JNI_NG") // Log switch

#define ANDROID_DEBUG_LOG(...) (__android_log_print(ANDROID_LOG_DEBUG, __JNI_LOG_TAG__, __VA_ARGS__))
#define ANDROID_WARN_LOG(...) (__android_log_print(ANDROID_LOG_WARN, __JNI_LOG_TAG__, __VA_ARGS__))
#define ANDROID_ERROR_LOG(...) (__android_log_print(ANDROID_LOG_ERROR, __JNI_LOG_TAG__, __VA_ARGS__))
#else
#define ANDROID_DEBUG_LOG(...)
#define ANDROID_WARN_LOG(...)
#define ANDROID_ERROR_LOG(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

const unsigned char KEY[] = "abcdefghijklmnop";//16bytes
const unsigned char IV[] = "0123456789abcdef";//16bytes

jbyteArray encrypt(JNIEnv *env, jclass thiz, jbyteArray src) {
    unsigned char *str = NULL;
    jbyte *bytes;
    bytes = env->GetByteArrayElements(src, 0);
    int srcLength = env->GetArrayLength(src);

    int encs_length = ((srcLength + AES_BLOCKLEN) / AES_BLOCKLEN) * AES_BLOCKLEN;
    str = (unsigned char *) malloc(encs_length);

    int sum = encs_length - srcLength;
    memset(str, sum, encs_length);
    memcpy(str, bytes, srcLength);

    env->ReleaseByteArrayElements(src, bytes, 0);

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, KEY, IV);
    AES_CBC_encrypt_buffer(&ctx, str, encs_length);

    jbyteArray result2 = env->NewByteArray(encs_length);
    env->SetByteArrayRegion(result2, 0, encs_length, (jbyte *) str);
    return result2;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = 0;
    if ((vm->GetEnv((void **) &env, JNI_VERSION_1_6)) != JNI_OK) {
        return JNI_ERR;
    }

    //for aes
    JNINativeMethod aes_methods[] = {
            {"encrypt", "([B)[B", (void *) &encrypt}
    };


#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
    jclass aaHelper = env->FindClass("cn/demonk/aes/MainActivity");
    if (aaHelper == NULL) {
        return JNI_ERR;
    }

    if (env->RegisterNatives(aaHelper, aes_methods, NELEM(aes_methods)) < 0) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif
