LOCAL_PATH := $(call my-dir)
PROJECT_ROOT:= $(call my-dir)/../../../../..
APP_ROOT:= $(call my-dir)/../../../..

include $(CLEAR_VARS)
LOCAL_MODULE    := libopencl_pointcloud
LOCAL_SHARED_LIBRARIES := tango_client_api tango_support_api
LOCAL_CFLAGS    := -Werror -std=c++11
LOCAL_SRC_FILES := native-lib.cpp \
                   OpenCL_PointCloud.cpp
LOCAL_LDLIBS    := -llog -lGLESv3 -L$(SYSROOT)/usr/lib -lOpenCL
include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(PROJECT_ROOT))
$(call import-module,tango_client_api)
$(call import-module,tango_support_api)

$(call import-add-path, $(APP_ROOT))
$(call import-module,tango_support_api)

