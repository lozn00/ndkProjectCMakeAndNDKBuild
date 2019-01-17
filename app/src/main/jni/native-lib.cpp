#include <jni.h>
#include<android/log.h>
#include <string>
#include "include/inlineHook.h"
#include <stdio.h>

#define LOG_TAG "QSSQ_DEBUG"
#define ENABLEDEBUG 1
#if ENABLEDEBUG
#ifdef ANDROID










#include <android/log.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>

//int __android_log_print(int prio, const char* tag, const char* fmt, ...)
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGI(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,__FILE__,__FUNCTION__,##__VA_ARGS__)
#define LOGV(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGW(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
#define LOGF(fmt, ...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, "[%s:%s]" fmt,__FILE__, __FUNCTION__,##__VA_ARGS__)
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
    LOGW("new_put call %s", string);
    return old_puts("inlineHook success");//必须返回 否则崩溃。
}


FILE *(*old_fopen)(const char *__path, const char *__mode);

FILE *new_fopen(const char *__path, const char *__mode) {

    LOGW("hook_path %s mode %s", __path, __mode);
    return old_fopen(__path, __mode);
}


int (*old_access)(const char *__path, int __mode);

int new_access(const char *__path, int __mode) {

    LOGW("accessfile  %s ,mode %d", __path, __mode);
    return old_access(__path, __mode);
}


int hook() {
    if (registerInlineHook((uint32_t) puts, (uint32_t) new_puts, (uint32_t **) &old_puts) !=
        ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) puts) != ELE7EN_OK) {
        return -1;
    }


    if (registerInlineHook((uint32_t) fopen, (uint32_t) new_fopen, (uint32_t **) &old_fopen) !=
        ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) fopen) != ELE7EN_OK) {
        return -1;
    }
    if (registerInlineHook((uint32_t) access, (uint32_t) new_access, (uint32_t **) &old_access) !=
        ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) access) != ELE7EN_OK) {
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

/*返回str2第一次出现在str1中的位置(下表索引),不存在返回-1*/
int indexOf(char *str1, const char *str2) {
    char *p = str1;
    int i = 0;
    p = strstr(str1, str2);
    if (p == NULL)
        return -1;
    else {
        while (str1 != p) {
            str1++;
            i++;
        }
    }
    return i;
}



bool endWith(const char *str, const char *end) {
    bool result = false;
    if (str != NULL && end != NULL) {
        int l1 = strlen(str);
        int l2 = strlen(end);
        if (l1 >= l2) {
            if (strcmp(str + l1 - l2, end) == 0) {
                result = true;
            }
        }
    }
    return result;
}

bool startsWith(const char *str, const char *token) {
    if (str == NULL || token == NULL)
        return 0;
    return (strncmp(str, token, strlen(token)) == 0);

}

extern "C" JNIEXPORT jstring

JNICALL Java_cn_qssq666_ndkhook_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello hello !!";
//
    puts("test");

    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" __FILE__, __FUNCTION__,
            "FUNCC...............");

    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s:%s]" "bb", "文件名宏定义", "函数名宏定义", "bb1");
    //输出 [文件名宏定义:函数名宏定义]bb 这里我当时比较困惑的是为什么两个字符串在一起拼写，这明显的语法错误么，其实这可以这么写的，

    LOGW("fuck");
    // LOGW("callll");
//    LOGW("hook resut %d", hook());
    puts("aaaaa");
    int hookResult = hook();
    puts("hook after1");
    puts("hook after2");
    puts("hook after3");
    puts("hook after4");
    FILE *fp;
    fp = fopen("/proc/self/maps", "r");
    char buffer[2048];

    while (!feof(fp)) {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer), fp);
//        LOGI("map dump %s currentpackage %s\n", buffer, packagename);//获取当前扫描的内容maps
        int index = indexOf(buffer, "/data/app/");
        if (index != -1 && indexOf(buffer, "aaa") == -1) {//如果不等于当前包名 ，但是是别的包。

            LOGI("mapdump-data/app/ %s\n", buffer);//获取当前扫描的内容maps
            char *path_so = strchr(buffer, '/');
            //去掉换行符
            path_so[strlen(path_so) - 1] = 0;
            LOGI("map-path=%s\n", path_so); //路径可能会重复出现多次，需要做过滤。
            //char path[1024]={0};
            //strcpy(path,path_so);
            if (endWith(path_so, ".apk") || endWith(path_so, ".jar") || endWith(path_so, ".zip")) {

                LOGW("found debug apk %s ", path_so);
            }

        }
    }
    fclose(fp);



    if (hookResult != 0) {
        LOGW("HOOK fail %d", hookResult);
    } else {
        LOGW("HOOK succ %d", hookResult);
        puts("test");
    }

    void *handle = dlopen("libc.so", RTLD_NOW);
    const char *symbol = nullptr;
    void *addr = dlsym(handle, "mkdir"); //功能是根据动态链接库操作句柄与符号，返回符号对应的地址，不但可以获取函数地址，也可以获取变量地址。
    if (addr == NULL) {
        LOGW("libc so mkdir find fail");
    } else {
        LOGW("libc so mkdir find succ %#x", addr);
    }

//    MSHookFunction(addr, new_func, old_func);

    if (access("/sdcard/qssq666/a.txt", W_OK) == 0) {

    }



//    MSHookFunction(addr, new_func, old_func);


//    unHook();
//    puts("test");
    return env->NewStringUTF("hello");
//    return env->NewStringUTF(hello.c_str());
}


/*
     void *handle = dlopen("libc.so", RTLD_NOW);
    if (handle) {
        HOOK_SYMBOL(handle, faccessat);
        HOOK_SYMBOL(handle, __openat);
        HOOK_SYMBOL(handle, fchmodat);
        HOOK_SYMBOL(handle, fchownat);
        HOOK_SYMBOL(handle, renameat);
        HOOK_SYMBOL(handle, fstatat64);
        HOOK_SYMBOL(handle, __statfs);
        HOOK_SYMBOL(handle, __statfs64);
        HOOK_SYMBOL(handle, mkdirat);
        HOOK_SYMBOL(handle, mknodat);
        HOOK_SYMBOL(handle, truncate);
        HOOK_SYMBOL(handle, linkat);
        HOOK_SYMBOL(handle, readlinkat);
        HOOK_SYMBOL(handle, unlinkat);
        HOOK_SYMBOL(handle, symlinkat);
        HOOK_SYMBOL(handle, utimensat);
        HOOK_SYMBOL(handle, __getcwd);//查看当前目录
//        HOOK_SYMBOL(handle, __getdents64);
        HOOK_SYMBOL(handle, chdir); //改变工作目录
        HOOK_SYMBOL(handle, execve);
        if (api_level <= 20) {
            HOOK_SYMBOL(handle, access)//判断文件是否可读 （）;
            HOOK_SYMBOL(handle, __open);
            HOOK_SYMBOL(handle, stat);
            HOOK_SYMBOL(handle, lstat);
            HOOK_SYMBOL(handle, fstatat);
            HOOK_SYMBOL(handle, chmod);
            HOOK_SYMBOL(handle, chown);
            HOOK_SYMBOL(handle, rename);
            HOOK_SYMBOL(handle, rmdir);
            HOOK_SYMBOL(handle, mkdir);
            HOOK_SYMBOL(handle, mknod);
            HOOK_SYMBOL(handle, link);
            HOOK_SYMBOL(handle, unlink);
            HOOK_SYMBOL(handle, readlink);
            HOOK_SYMBOL(handle, symlink);
//            HOOK_SYMBOL(handle, getdents);
//            HOOK_SYMBOL(handle, execv);
        }
        dlclose(handle);
    }
    hook_dlopen(api_level);




 */