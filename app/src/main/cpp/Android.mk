LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_LDLIBS := -llog
LOCAL_MODULE := xxxxxx

# means encrypt or decrypt

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := encrypt.cpp aes.c
# src/sha1.c

#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
LOCAL_CFLAGS := -DHAVE_ANDROID_OS -fno-unwind-tables -fvisibility=hidden -Os

#ADD _DEBUG flag for log
#NEED TO DISABLE WHEN BUILDING RELEASE
ifeq ($(NDK_DEBUG),1)
	LOCAL_CFLAGS += -D_DEBUG
endif

#NEED TO DISABLE WHEN BUILDING RELEASE,PASS SIGN CHECK
#LOCAL_CFLAGS += -D_PASS
include $(BUILD_SHARED_LIBRARY)
