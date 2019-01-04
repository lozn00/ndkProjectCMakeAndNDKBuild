NDK_DEBUG=1
LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#LOCAL_MODULE    := hook
#LOCAL_SRC_FILES := inlineHook.c relocate.c
#include $(BUILD_STATIC_LIBRARY)





LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
PROJECT_PATH = $(LOCAL_PATH)/..

LOCAL_MODULE    := hook
LOCAL_LDFLAGS += -shared

#添加模块使用宏定义
LOCAL_CFLAGS += -DMODULE_FLAG

#添加需要包含的头文件路径，会依次遍历向下所有目录，
MY_HEADER_PATH += $(PROJECT_PATH)

#添加需要包含的头文件路径，不会向下遍历，最后一个不要加\号
LOCAL_C_INCLUDES += $(PROJECT_PATH)../include
#LOCAL_C_INCLUDES += $(shell find $(MY_HEADER_PATH) -type d) 只适合linux
$(warning "module name: $(LOCAL_MODULE)->LOCAL_C_INCLUDES =$(LOCAL_C_INCLUDES)")

# 扫描目录下的所有源文件，会向下依次遍历
MY_FILES_PATH  := $(PROJECT_PATH)
# 添加指定C/CPP文件，只添加某个
$(warning "local_path $(LOCAL_PATH)")

#LOCAL_SRC_FILES += $(LOCAL_PATH)/inlineHook.c $(LOCAL_PATH)/relocate.c

MY_FILES_SUFFIX := %.cpp %.c %.cc
# My_All_Files := $(foreach src_path,$(MY_FILES_PATH), $(shell find "$(src_path)" -type f) )只适合linux find -type f
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(My_All_Files))
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(MY_SRC_LIST)
$(warning "dirs->$(LOCAL_MODULE): LOCAL_SRC_FILES =$(LOCAL_SRC_FILES)")



#LOCAL_SRC_FILES += $(LOCAL_PATH)inlineHook.c $(LOCAL_PATH)relocate.c

#添加需要链接的静态库
LOCAL_STATIC_LIBRARIES  :=

#添加需要链接的动态库
LOCAL_SHARED_LIBRARIES  :=
$(warning "$(LOCAL_MODULE): LOCAL_SHARED_LIBRARIES=$(LOCAL_SHARED_LIBRARIES)")

#添加需要链接的系统库，如ndk编译，需要链接的log/android等
LOCAL_LDLIBS    += -llog -landroid -lc

#指定编译目标，这边编译动态库
include $(BUILD_SHARED_LIBRARY)




#include $(CLEAR_VARS)
#LOCAL_MODULE    := hook
#LOCAL_SRC_FILES := inlineHook.c relocate.c

#BUILD_STATIC_LIBRARY：编译为静态库。
#BUILD_SHARED_LIBRARY ：编译为动态库
#BUILD_EXECUTABLE：编译为Native C可执行程序


a:=aaaaa
b:=${a}
a:=a1
a:=a
$(warning "a=${a} b=${b}") #结果是 a =d  b=aaa


c=ccccc
d=${c}
c=c
$(warning "c=${c} d=${d}") #结果是 c=c  b=c 把d=改为d:= 那么d的值就变成了cccc

# :=和 =是一样的用法， 是类似普通的变量赋值按顺序流程 = 是有一点区别某个变量用:=获取其他变量的时候， 会有区别=的区别是以最后整个文件走完之后的变量为准。








