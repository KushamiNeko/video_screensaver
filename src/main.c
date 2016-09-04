#include <gdk/gdk.h>
#include <gtk-3.0/gtk/gtk.h>

#include <gdk/gdk.h>
#if defined GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#elif defined GDK_WINDOWING_WIN32
#include <gdk/gdkwin32.h>
#elif defined GDK_WINDOWING_QUARTZ
#include <gdk/gdkquartz.h>
#endif

#include <gstreamer-1.0/gst/gst.h>
#include <gstreamer-1.0/gst/video/videooverlay.h>

#include <string.h>

static guintptr video_window_handle = 0;
GtkWidget *video_window;
GtkWidget *main_window;

GstElement *pipeline, *src, *sink;
GstBus *bus;

static void video_widget_realize_cb(GtkWidget *widget, gpointer data);
static GstBusSyncReply bus_sync_handler(GstBus *bus, GstMessage *message,
                                        gpointer user_data);

int main(int argc, char *argv[]) {
  gst_init(&argc, &argv);
  gtk_init(&argc, &argv);

  pipeline = gst_element_factory_make("playbin", "play");

  const char *initVideo = "file:///home/onionhuang/Videos/01.webm";
  //  g_object_set(G_OBJECT(pipeline), "uri",
  //               "http://docs.gstreamer.com/media/sintel_trailer-480p.webm",
  //               NULL);

  g_object_set(G_OBJECT(pipeline), "uri", initVideo, NULL);

  bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
  gst_element_set_state(pipeline, GST_STATE_READY);

  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  video_window = gtk_drawing_area_new();
  g_signal_connect(video_window, "realize", G_CALLBACK(video_widget_realize_cb),
                   NULL);
  gtk_container_add(GTK_CONTAINER(main_window), video_window);

  gtk_widget_show_all(main_window);
  gtk_widget_realize(video_window);

  gst_element_set_state(pipeline, GST_STATE_PLAYING);

  bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
  gst_bus_set_sync_handler(bus, (GstBusSyncHandler)bus_sync_handler, NULL,
                           NULL);
  gst_object_unref(bus);

  // run main loop
  gtk_main();
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
  return 0;
}

static void video_widget_realize_cb(GtkWidget *widget, gpointer data) {
#if defined GDK_WINDOWING_WIN32
  video_window_handle =
      (guintptr)GDK_WINDOW_HWND(gtk_widget_get_window(video_window));
#elif defined GDK_WINDOWING_QUARTZ
  video_window_handle =
      gdk_quartz_window_get_nsview(gtk_widget_get_window(video_window));
#elif defined GDK_WINDOWING_X11
  video_window_handle = GDK_WINDOW_XID(gtk_widget_get_window(video_window));
#endif
}

static GstBusSyncReply bus_sync_handler(GstBus *bus, GstMessage *message,
                                        gpointer user_data) {
  // ignore anything but 'prepare-window-handle' element messages
  if (!gst_is_video_overlay_prepare_window_handle_message(message)) {
    return GST_BUS_PASS;
  }

  if (video_window_handle != 0) {
    GstVideoOverlay *overlay;

    // GST_MESSAGE_SRC (message) will be the video sink element
    overlay = GST_VIDEO_OVERLAY(GST_MESSAGE_SRC(message));
    gst_video_overlay_set_window_handle(overlay, video_window_handle);
    return GST_BUS_DROP;
  } else {
    g_warning("Should have obtained video_window_handle by now!");
    return GST_BUS_DROP;
  }
}
