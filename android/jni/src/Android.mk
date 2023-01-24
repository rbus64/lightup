LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_CFLAGS += -g -std=c99

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

YOUR_SRC_FILES=game_text.c game_aux.c game_examples.c game_ext.c game_private.c game_random.c  game_tools.c game_visuals.c game.c queue.c visuals.c

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c $(YOUR_SRC_FILES)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
