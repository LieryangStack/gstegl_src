###############################################################################
#
# Copyright (c) 2022-2023, NVIDIA CORPORATION.  All rights reserved.
#
# NVIDIA Corporation and its licensors retain all intellectual property
# and proprietary rights in and to this software, related documentation
# and any modifications thereto.  Any use, reproduction, disclosure or
# distribution of this software and related documentation without an express
# license agreement from NVIDIA Corporation is strictly prohibited.
#
###############################################################################

ifneq ($(MAKECMDGOALS),install)
endif
            
SO_NAME := libnvdsgst_eglglessink.so
DEST_DIR = /usr/lib/x86_64-linux-gnu/gstreamer-1.0/deepstream

SRCS := ext/eglgles/gstegladaptation.c \
	ext/eglgles/gstegladaptation_egl.c \
	ext/eglgles/gsteglglessink.c \
	ext/eglgles/gstegljitter.c \
	ext/eglgles/video_platform_wrapper.c \
	gst-libs/gst/egl/egl.c

INCLUDES += -I./pre-gen-source_64/ \
        -I./gst-libs \
        -I./gst-libs/gst/egl \
        -I/opt/nvidia/deepstream/deepstream-6.4/sources/includes/ \
        -I/usr/local/include/gstreamer-1.0 \
        -I/usr/local/cuda/targets/x86_64-linux/include/ \
        -I./

PKGS := glib-2.0 \
        gstreamer-1.0 \
        gstreamer-base-1.0 \
        gstreamer-video-1.0

OBJS := $(SRCS:.c=.o)

CFLAGS := -fPIC \
	-DHAVE_CONFIG_H \
	-DG_THREADS_MANDATORY \
	-DG_DISABLE_DEPRECATED \
	-DUSE_EGL_TEGRA 

CFLAGS += `pkg-config --cflags $(PKGS)`

LDFLAGS = -Wl,--no-undefined -L/opt/nvidia/deepstream/deepstream-6.4/lib/ \
                             -L/usr/lib/aarch64-linux-gnu/tegra \
														 -L/usr/local/cuda/targets/x86_64-linux/lib/

LIBS = -lnvbufsurface -lGLESv2 -lEGL -lX11 -lm -lcuda -lcudart -lwayland-client -lwayland-egl

LIBS += `pkg-config --libs $(PKGS)`

all: $(SO_NAME)

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(SO_NAME): $(OBJS)
	$(CC) -shared -o $(SO_NAME) $(OBJS) $(LIBS) $(LDFLAGS)

.PHONY: install
install: $(SO_NAME)
	cp -v $(SO_NAME) $(DEST_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJS) $(SO_NAME)

