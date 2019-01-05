#include <jni.h>
#include <string>
#include "include/inlineHook.h"
#include <stdio.h>

#define LOG_TAG "QSSQ_DEBUG"
#define ENABLEDEBUG 1
#if ENABLEDEBUG
#ifdef ANDROID










#include <android/log.h>
#include <string.h>

#define TF()  (strrchr(__FILE__,'/')+1)
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,TF(), __FUNCTION__,##__VA_ARGS__)
#define LOGI(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,TF(),__FUNCTION__,##__VA_ARGS__)
#define LOGV(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,TF(), __FUNCTION__,##__VA_ARGS__)
#define LOGW(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,TF(), __FUNCTION__,##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,TF(), __FUNCTION__,##__VA_ARGS__)
#define LOGF(fmt, ...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, "[%s:%s]" fmt,TF(), __FUNCTION__,##__VA_ARGS__)
#else
#define LOGD(fmt,...) printf("[%s %s]" fmt, __FILE__,__FUNCTION__,##__VA_ARGS__)
#define LOGI(fmt,...) printf("[%s %s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGV(fmt,...) printf("[%s %s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGW(fmt,...) printf("[%s %s]" fmt, __FILE__,__FUNCTION__,##__VA_ARGS__)
#define LOGE(fmt,...) printf("[%s %s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGF(fmt,...) printf("[%s %s]" fmt, __FILE__,__FUNCTION__,##__VA_ARGS__)
#endif
#else
#include <android/log.h>
#define TF() ("")
#define LOGD(fmt,...) if(true){}
#define LOGI(fmt,...) if(true){}
#define LOGV(fmt,...) if(true){}
#define LOGW(fmt,...) if(true){}
#define LOGE(fmt,...) if(true){}
#define LOGF(fmt,...) if(true){}
#endif




int (*old_puts)(const char *) = NULL;

int new_puts(const char *string) {
    LOGW("new_put call %s",string);
//    old_puts("inlineHook success");
}

int hook() {
    if (registerInlineHook((uint32_t) puts, (uint32_t) new_puts, (uint32_t **) &old_puts) !=
        ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) puts) != ELE7EN_OK) {
        return -1;
    }

    return 0;
}

int unHook() {
    if (inlineUnHook((uint32_t) puts) != ELE7EN_OK) {
        return -1;
    }

    return 0;
}

extern "C" JNIEXPORT jstring

JNICALL Java_cn_qssq666_ndkhook_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello hello !!";
//
    puts("test");
    LOGW("fuck");
    // LOGW("callll");
//    LOGW("hook resut %d", hook());
    LOGW("HOOK RESULT %D",hook());
    puts("test");
//    unHook();
//    puts("test");
    return env->NewStringUTF(hello.c_str());
}
