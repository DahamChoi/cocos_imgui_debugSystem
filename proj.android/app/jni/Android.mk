LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../Classes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/**/**/**/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += hellocpp/main.cpp


HEADER_LIST := $(wildcard $(LOCAL_PATH)/../../../Classes/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/**/**/*.h)
HEADER_LIST += $(wildcard $(LOCAL_PATH)/../../../Classes/**/**/**/**/**/**/**/**/**/**/**/*.h)

LOCAL_C_INCLUDES := $(dir $(HEADER_LIST))
# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
