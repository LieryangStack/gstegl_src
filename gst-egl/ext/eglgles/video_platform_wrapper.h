/*
 * GStreamer Android Video Platform Wrapper
 * Copyright (C) 2012 Collabora Ltd.
 *   @author: Reynaldo H. Verdejo Pinochet <reynaldo@collabora.com>
 * Copyright (c) 2014-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * General idea is to have all platform dependent code here for easy
 * tweaking and isolation from the main routines
 */

#ifndef __GST_VIDEO_PLATFORM_WRAPPER__
#define __GST_VIDEO_PLATFORM_WRAPPER__

#include <gst/gst.h>
#include <EGL/egl.h>

#define USE_EGL_X11 1
#define IS_DESKTOP 1

#ifdef USE_EGL_X11
#include <X11/Xlib.h>
typedef struct
{
  Display *display;
} X11WindowData;

EGLNativeWindowType platform_create_native_window_x11 (gint x, gint y, gint width, gint height, gpointer * window_data);
gboolean platform_destroy_native_window_x11 (EGLNativeDisplayType display,
    EGLNativeWindowType w, gpointer * window_data);
#endif

#ifdef USE_EGL_WAYLAND
#include <wayland-client.h>
#include <wayland-client-core.h>
#include "wayland-client-protocol.h"
#include "wayland-egl.h"
#include "presentation-time-client-protocol.h"
#include "ivi-application-client-protocol.h"
typedef struct
{
  struct wl_egl_window *egl_window;
  struct wl_shell_surface *shell_surface;
  struct ivi_surface *ivi_surface;
  struct wl_surface *surface;
} WaylandWindowData;

typedef struct
{
  struct wl_display *display;
  struct wl_compositor *compositor;
  struct wl_shell *shell;
  struct wp_presentation *presentation;
  struct wp_presentation_feedback *presentation_feedback;
  struct wl_registry *registry;
  struct ivi_application *ivi_application;
  guint32 clock_id;
} WaylandDisplay;

EGLNativeWindowType platform_create_native_window_wayland (gint x, gint y, gint width, gint height, guint ivisurf_id, gpointer * window_data);
EGLNativeDisplayType platform_initialize_display_wayland (void);
gboolean platform_destroy_native_window_wayland (EGLNativeDisplayType display,
    EGLNativeWindowType w, gpointer * window_data);
gboolean platform_destroy_display_wayland (void);
gboolean register_frame_callback_wayland(gpointer * window_data, GstBuffer * buf);
gboolean register_presentation_feedback(gpointer * window_data, GstBuffer * buf);
#endif

gboolean platform_wrapper_init (void);

#if !defined(USE_EGL_X11) && !defined(USE_EGL_WAYLAND)
EGLNativeWindowType platform_create_native_window (gint x, gint y, gint width, gint height, gpointer * window_data);
gboolean platform_destroy_native_window (EGLNativeDisplayType display,
    EGLNativeWindowType w, gpointer * window_data);
#endif

#endif
