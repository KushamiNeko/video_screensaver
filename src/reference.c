

//#include <string.h>
//
//#include <gstreamer-0.10/gst/gst.h>
//#include <gstreamer-0.10/gst/interfaces/xoverlay.h>
//#include <gtk/gtk.h>
//
//#include <gdk/gdk.h>
//#if defined(GDK_WINDOWING_X11)
//#include <gdk/gdkx.h>
//#elif defined(GDK_WINDOWING_WIN32)
//#include <gdk/gdkwin32.h>
//#elif defined(GDK_WINDOWING_QUARTZ)
//#include <gdk/gdkquartz.h>
//#endif
//
///* Structure to contain all our information, so we can pass it around */
// typedef struct _CustomData {
//  GstElement *playbin2; /* Our one and only pipeline */
//
//  GtkWidget *slider;       /* Slider widget to keep track of current position
//  */
//  GtkWidget *streams_list; /* Text widget to display info about the streams */
//  gulong slider_update_signal_id; /* Signal ID for the slider update signal */
//
//  GstState state;  /* Current state of the pipeline */
//  gint64 duration; /* Duration of the clip, in nanoseconds */
//
//} CustomData;
//
///* This function is called when the GUI toolkit creates the physical window
/// that
// * will hold the video.
// *  * At this point we can retrieve its handler (which has a different meaning
// * depending on the windowing system)
// *   * and pass it to GStreamer through the XOverlay interface. */
// static void realize_cb(GtkWidget *widget, CustomData *data) {
//  GdkWindow *window = gtk_widget_get_window(widget);
//  guintptr window_handle;
//
//  if (!gdk_window_ensure_native(window))
//    g_error("Couldn't create native window needed for GstXOverlay!");
//
///* Retrieve window handler from GDK */
//#if defined(GDK_WINDOWING_WIN32)
//  window_handle = (guintptr)GDK_WINDOW_HWND(window);
//#elif defined(GDK_WINDOWING_QUARTZ)
//  window_handle = gdk_quartz_window_get_nsview(window);
//#elif defined(GDK_WINDOWING_X11)
//  window_handle = GDK_WINDOW_XID(window);
//#endif
//  /* Pass it to playbin2, which implements XOverlay and will forward it to the
//   * video sink */
//  gst_x_overlay_set_window_handle(GST_X_OVERLAY(data->playbin2),
//  window_handle);
//}
//
///* This function is called when the PLAY button is clicked */
////static void play_cb(GtkButton *button, CustomData *data) {
////  gst_element_set_state(data->playbin2, GST_STATE_PLAYING);
////}
////
/////* This function is called when the PAUSE button is clicked */
////static void pause_cb(GtkButton *button, CustomData *data) {
////  gst_element_set_state(data->playbin2, GST_STATE_PAUSED);
////}
////
///* This function is called when the STOP button is clicked */
// static void stop_cb(GtkButton *button, CustomData *data) {
//  gst_element_set_state(data->playbin2, GST_STATE_READY);
//}
//
///* This function is called when the main window is closed */
// static void delete_event_cb(GtkWidget *widget, GdkEvent *event,
//                            CustomData *data) {
//  stop_cb(NULL, data);
//  gtk_main_quit();
//}
//
///* This function is called everytime the video window needs to be redrawn (due
// * to damage/exposure,
// *  * rescaling, etc). GStreamer takes care of this in the PAUSED and PLAYING
// * states, otherwise,
// *   * we simply draw a black rectangle to avoid garbage showing up. */
// static gboolean expose_cb(GtkWidget *widget, GdkEventExpose *event,
//                          CustomData *data) {
//  if (data->state < GST_STATE_PAUSED) {
//    GtkAllocation allocation;
//    GdkWindow *window = gtk_widget_get_window(widget);
//    cairo_t *cr;
//
//    /* Cairo is a 2D graphics library which we use here to clean the video
//     * window.
//     *      * It is used by GStreamer for other reasons, so it will always be
//     * available to us. */
//    gtk_widget_get_allocation(widget, &allocation);
//    cr = gdk_cairo_create(window);
//    cairo_set_source_rgb(cr, 0, 0, 0);
//    cairo_rectangle(cr, 0, 0, allocation.width, allocation.height);
//    cairo_fill(cr);
//    cairo_destroy(cr);
//  }
//
//  return FALSE;
//}
//
///* This function is called when the slider changes its position. We perform a
// * seek to the
// *  * new position here. */
////static void slider_cb(GtkRange *range, CustomData *data) {
////  gdouble value = gtk_range_get_value(GTK_RANGE(data->slider));
////  gst_element_seek_simple(data->playbin2, GST_FORMAT_TIME,
////                          GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT,
////                          (gint64)(value * GST_SECOND));
////}
//
///* This creates all the GTK+ widgets that compose our application, and
/// registers
// * the callbacks */
// static void create_ui(CustomData *data) {
//  GtkWidget *main_window;
//  GtkWidget *video_window;
//
// // GtkWidget *main_box;
// // GtkWidget *main_hbox;
//
// // GtkWidget *controls;
// // GtkWidget *play_button, *pause_button, *stop_button;
//
//  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//  g_signal_connect(G_OBJECT(main_window), "delete-event",
//                   G_CALLBACK(delete_event_cb), data);
//
//  video_window = gtk_drawing_area_new();
//  //gtk_widget_set_double_buffered(video_window, FALSE);
//  g_signal_connect(video_window, "realize", G_CALLBACK(realize_cb), data);
//  g_signal_connect(video_window, "expose_event", G_CALLBACK(expose_cb), data);
//
// // play_button = gtk_button_new_with_label(GTK_STOCK_MEDIA_PLAY);
// // g_signal_connect(G_OBJECT(play_button), "clicked", G_CALLBACK(play_cb),
// data);
//
// // pause_button = gtk_button_new_with_label(GTK_STOCK_MEDIA_PAUSE);
// // g_signal_connect(G_OBJECT(pause_button), "clicked", G_CALLBACK(pause_cb),
// //                  data);
//
// // stop_button = gtk_button_new_with_label(GTK_STOCK_MEDIA_STOP);
// // g_signal_connect(G_OBJECT(stop_button), "clicked", G_CALLBACK(stop_cb),
// data);
//
// // data->slider = gtk_hscale_new_with_range(0, 100, 1);
// // gtk_scale_set_draw_value(GTK_SCALE(data->slider), 0);
// // data->slider_update_signal_id = g_signal_connect(
// //     G_OBJECT(data->slider), "value-changed", G_CALLBACK(slider_cb), data);
//
// // data->streams_list = gtk_text_view_new();
// // gtk_text_view_set_editable(GTK_TEXT_VIEW(data->streams_list), FALSE);
//
// // controls = gtk_hbox_new(FALSE, 0);
// // gtk_box_pack_start(GTK_BOX(controls), play_button, FALSE, FALSE, 2);
// // gtk_box_pack_start(GTK_BOX(controls), pause_button, FALSE, FALSE, 2);
// // gtk_box_pack_start(GTK_BOX(controls), stop_button, FALSE, FALSE, 2);
// // gtk_box_pack_start(GTK_BOX(controls), data->slider, TRUE, TRUE, 2);
//
// // main_hbox = gtk_hbox_new(FALSE, 0);
// // gtk_box_pack_start(GTK_BOX(main_hbox), video_window, TRUE, TRUE, 0);
// // gtk_box_pack_start(GTK_BOX(main_hbox), data->streams_list, FALSE, FALSE,
// 2);
//
// // main_box = gtk_vbox_new(FALSE, 0);
// // gtk_box_pack_start(GTK_BOX(main_box), main_hbox, TRUE, TRUE, 0);
// // gtk_box_pack_start(GTK_BOX(main_box), controls, FALSE, FALSE, 0);
// // gtk_container_add(GTK_CONTAINER(main_window), main_box);
// // gtk_window_set_default_size(GTK_WINDOW(main_window), 640, 480);
//
//  gtk_widget_show_all(main_window);
//}
//
///* This function is called periodically to refresh the GUI */
// static gboolean refresh_ui(CustomData *data) {
//  GstFormat fmt = GST_FORMAT_TIME;
//  gint64 current = -1;
//
//  /* We do not want to update anything unless we are in the PAUSED or PLAYING
//   * states */
//  if (data->state < GST_STATE_PAUSED) return TRUE;
//
//  /* If we didn't know it yet, query the stream duration */
//  if (!GST_CLOCK_TIME_IS_VALID(data->duration)) {
//    if (!gst_element_query_duration(data->playbin2, &fmt, &data->duration)) {
//      g_printerr("Could not query current duration.\n");
//
//    } else {
//      /* Set the range of the slider to the clip duration, in SECONDS */
//      gtk_range_set_range(GTK_RANGE(data->slider), 0,
//                          (gdouble)data->duration / GST_SECOND);
//    }
//  }
//
//  if (gst_element_query_position(data->playbin2, &fmt, &current)) {
//    /* Block the "value-changed" signal, so the slider_cb function is not
//    called
//     *      * (which would trigger a seek the user has not requested) */
//    g_signal_handler_block(data->slider, data->slider_update_signal_id);
//    /* Set the position of the slider to the current pipeline positoin, in
//     * SECONDS */
//    gtk_range_set_value(GTK_RANGE(data->slider), (gdouble)current /
//    GST_SECOND);
//    /* Re-enable the signal */
//    g_signal_handler_unblock(data->slider, data->slider_update_signal_id);
//  }
//  return TRUE;
//}
//
///* This function is called when new metadata is discovered in the stream */
// static void tags_cb(GstElement *playbin2, gint stream, CustomData *data) {
//  /* We are possibly in a GStreamer working thread, so we notify the main
//   *    * thread of this event through a message in the bus */
//  gst_element_post_message(
//      playbin2,
//      gst_message_new_application(GST_OBJECT(playbin2),
//                                  gst_structure_new("tags-changed", NULL)));
//}
//
///* This function is called when an error message is posted on the bus */
// static void error_cb(GstBus *bus, GstMessage *msg, CustomData *data) {
//  GError *err;
//  gchar *debug_info;
//
//  /* Print error details on the screen */
//  gst_message_parse_error(msg, &err, &debug_info);
//  g_printerr("Error received from element %s: %s\n",
//  GST_OBJECT_NAME(msg->src),
//             err->message);
//  g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
//  g_clear_error(&err);
//  g_free(debug_info);
//
//  /* Set the pipeline to READY (which stops playback) */
//  gst_element_set_state(data->playbin2, GST_STATE_READY);
//}
//
///* This function is called when an End-Of-Stream message is posted on the bus.
// *  * We just set the pipeline to READY (which stops playback) */
// static void eos_cb(GstBus *bus, GstMessage *msg, CustomData *data) {
//  g_print("End-Of-Stream reached.\n");
//  gst_element_set_state(data->playbin2, GST_STATE_READY);
//}
//
///* This function is called when the pipeline changes states. We use it to
// *  * keep track of the current state. */
// static void state_changed_cb(GstBus *bus, GstMessage *msg, CustomData *data)
// {
//  GstState old_state, new_state, pending_state;
//  gst_message_parse_state_changed(msg, &old_state, &new_state,
//  &pending_state);
//  if (GST_MESSAGE_SRC(msg) == GST_OBJECT(data->playbin2)) {
//    data->state = new_state;
//    g_print("State set to %s\n", gst_element_state_get_name(new_state));
//    if (old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) {
//      /* For extra responsiveness, we refresh the GUI as soon as we reach the
//       * PAUSED state */
//      refresh_ui(data);
//    }
//  }
//}
//
///* Extract metadata from all the streams and write it to the text widget in
/// the
// * GUI */
// static void analyze_streams(CustomData *data) {
//  gint i;
//  GstTagList *tags;
//  gchar *str, *total_str;
//  guint rate;
//  gint n_video, n_audio, n_text;
//  GtkTextBuffer *text;
//
//  /* Clean current contents of the widget */
//  text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->streams_list));
//  gtk_text_buffer_set_text(text, "", -1);
//
//  /* Read some properties */
//  g_object_get(data->playbin2, "n-video", &n_video, NULL);
//  g_object_get(data->playbin2, "n-audio", &n_audio, NULL);
//  g_object_get(data->playbin2, "n-text", &n_text, NULL);
//
//  for (i = 0; i < n_video; i++) {
//    tags = NULL;
//    /* Retrieve the stream's video tags */
//    g_signal_emit_by_name(data->playbin2, "get-video-tags", i, &tags);
//    if (tags) {
//      total_str = g_strdup_printf("video stream %d:\n", i);
//      gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//      g_free(total_str);
//      gst_tag_list_get_string(tags, GST_TAG_VIDEO_CODEC, &str);
//      total_str = g_strdup_printf("  codec: %s\n", str ? str : "unknown");
//      gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//      g_free(total_str);
//      g_free(str);
//      gst_tag_list_free(tags);
//    }
//  }
//
//  for (i = 0; i < n_audio; i++) {
//    tags = NULL;
//    /* Retrieve the stream's audio tags */
//    g_signal_emit_by_name(data->playbin2, "get-audio-tags", i, &tags);
//    if (tags) {
//      total_str = g_strdup_printf("\naudio stream %d:\n", i);
//      gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//      g_free(total_str);
//      if (gst_tag_list_get_string(tags, GST_TAG_AUDIO_CODEC, &str)) {
//        total_str = g_strdup_printf("  codec: %s\n", str);
//        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//        g_free(total_str);
//        g_free(str);
//      }
//      if (gst_tag_list_get_string(tags, GST_TAG_LANGUAGE_CODE, &str)) {
//        total_str = g_strdup_printf("  language: %s\n", str);
//        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//        g_free(total_str);
//        g_free(str);
//      }
//      if (gst_tag_list_get_uint(tags, GST_TAG_BITRATE, &rate)) {
//        total_str = g_strdup_printf("  bitrate: %d\n", rate);
//        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//        g_free(total_str);
//      }
//      gst_tag_list_free(tags);
//    }
//  }
//
//  for (i = 0; i < n_text; i++) {
//    tags = NULL;
//    /* Retrieve the stream's subtitle tags */
//    g_signal_emit_by_name(data->playbin2, "get-text-tags", i, &tags);
//    if (tags) {
//      total_str = g_strdup_printf("\nsubtitle stream %d:\n", i);
//      gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//      g_free(total_str);
//      if (gst_tag_list_get_string(tags, GST_TAG_LANGUAGE_CODE, &str)) {
//        total_str = g_strdup_printf("  language: %s\n", str);
//        gtk_text_buffer_insert_at_cursor(text, total_str, -1);
//        g_free(total_str);
//        g_free(str);
//      }
//      gst_tag_list_free(tags);
//    }
//  }
//}
//
///* This function is called when an "application" message is posted on the bus.
// *  * Here we retrieve the message posted by the tags_cb callback */
// static void application_cb(GstBus *bus, GstMessage *msg, CustomData *data) {
//  if (g_strcmp0(gst_structure_get_name(msg->structure), "tags-changed") == 0)
//  {
//    /* If the message is the "tags-changed" (only one we are currently
//    issuing),
//     * update
//     *      * the stream info GUI */
//    analyze_streams(data);
//  }
//}
//
// int main(int argc, char *argv[]) {
//  CustomData data;
//  GstStateChangeReturn ret;
//  GstBus *bus;
//
//  /* Initialize GTK */
//  gtk_init(&argc, &argv);
//
//  /* Initialize GStreamer */
//  gst_init(&argc, &argv);
//
//  /* Initialize our data structure */
//  memset(&data, 0, sizeof(data));
//  data.duration = GST_CLOCK_TIME_NONE;
//
//  /* Create the elements */
//  data.playbin2 = gst_element_factory_make("playbin2", "playbin2");
//
//  if (!data.playbin2) {
//    g_printerr("Not all elements could be created.\n");
//    return -1;
//  }
//
//  /* Set the URI to play */
//  g_object_set(data.playbin2, "uri",
//               "http://docs.gstreamer.com/media/sintel_trailer-480p.webm",
//               NULL);
//
//  /* Connect to interesting signals in playbin2 */
////  g_signal_connect(G_OBJECT(data.playbin2), "video-tags-changed",
////                   (GCallback)tags_cb, &data);
////  g_signal_connect(G_OBJECT(data.playbin2), "audio-tags-changed",
////                   (GCallback)tags_cb, &data);
////  g_signal_connect(G_OBJECT(data.playbin2), "text-tags-changed",
////                   (GCallback)tags_cb, &data);
//
//  /* Create the GUI */
//  create_ui(&data);
//
//  /* Instruct the bus to emit signals for each received message, and connect
//  to
//   * the interesting signals */
//  bus = gst_element_get_bus(data.playbin2);
//  gst_bus_add_signal_watch(bus);
////  g_signal_connect(G_OBJECT(bus), "message::error", (GCallback)error_cb,
///&data);
////  g_signal_connect(G_OBJECT(bus), "message::eos", (GCallback)eos_cb, &data);
////  g_signal_connect(G_OBJECT(bus), "message::state-changed",
////                   (GCallback)state_changed_cb, &data);
//  g_signal_connect(G_OBJECT(bus), "message::application",
//                   (GCallback)application_cb, &data);
//  gst_object_unref(bus);
//
//  /* Start playing */
//  ret = gst_element_set_state(data.playbin2, GST_STATE_PLAYING);
//  if (ret == GST_STATE_CHANGE_FAILURE) {
//    g_printerr("Unable to set the pipeline to the playing state.\n");
//    gst_object_unref(data.playbin2);
//    return -1;
//  }
//
//  /* Register a function that GLib will call every second */
//  g_timeout_add_seconds(1, (GSourceFunc)refresh_ui, &data);
//
//  /* Start the GTK main loop. We will not regain control until gtk_main_quit
//  is
//   * called. */
//  gtk_main();
//
//  /* Free resources */
//  gst_element_set_state(data.playbin2, GST_STATE_NULL);
//  gst_object_unref(data.playbin2);
//  return 0;
//}

//#include <gstreamer-0.10/gst/gst.h>
//
// int main(int argc, char *argv[]) {
//  GstElement *pipeline;
//  GstBus *bus;
//  GstMessage *msg;
//
//  /* Initialize GStreamer */
//  gst_init(&argc, &argv);
//
//  /* Build the pipeline */
//  pipeline = gst_parse_launch(
//      "playbin2 uri=http://docs.gstreamer.com/media/sintel_trailer-480p.webm",
//      NULL);
//
//  /* Start playing */
//  gst_element_set_state(pipeline, GST_STATE_PLAYING);
//
//  /* Wait until error or EOS */
//  bus = gst_element_get_bus(pipeline);
//  msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
//                                   GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
//
//  /* Free resources */
//  if (msg != NULL) gst_message_unref(msg);
//  gst_object_unref(bus);
//  gst_element_set_state(pipeline, GST_STATE_NULL);
//  gst_object_unref(pipeline);
//  return 0;
//}
//

#include <string.h>

#include <gdk/gdk.h>
#include <gtk-3.0/gtk/gtk.h>
//#if defined(GDK_WINDOWING_X11)
//#include <gdk/gdkx.h>
//#endif


#include <gdk/gdk.h>
#if defined(GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined(GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined(GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif

// required header for gstreamer
#include <gstreamer-1.0/gst/gst.h>
#include <gstreamer-1.0/gst/video/videooverlay.h>

// video window handle
static guintptr video_window_handle = 0;
GtkWidget *video_window;
GtkWidget *main_window;
// GtkWidget *hbox;
// GtkWidget *vbox;
// GtkWidget *control;
// GtkWidget *Play;
// GtkWidget *Pause;
// GtkWidget *Open;

GstElement *pipeline, *src, *sink;
GstBus *bus;

static void video_widget_realize_cb(GtkWidget *widget, gpointer data);
static GstBusSyncReply bus_sync_handler(GstBus *bus, GstMessage *message,
                                        gpointer user_data);

// static void play_cb(GtkButton *button, GstElement *pipeline) {
//  gst_element_set_state(pipeline, GST_STATE_PLAYING);
//}
//
// static void pause_cb(GtkButton *button, GstElement *pipeline) {
//  gst_element_set_state(pipeline, GST_STATE_PAUSED);
//}
//
// static void open_cb(GtkButton *button, GstElement *pipeline) {
//  gst_element_set_state(pipeline, GST_STATE_READY);
//  GtkWidget *dialog;
//  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
//  gint res;
//
//  dialog = gtk_file_chooser_dialog_new("Open File ", NULL, action, "Cancel",
//                                       GTK_RESPONSE_CANCEL, "Open",
//                                       GTK_RESPONSE_ACCEPT, NULL);
//
//  res = gtk_dialog_run(GTK_DIALOG(dialog));
//  if (res == GTK_RESPONSE_ACCEPT) {
//    char *filename;
//    char video_loc[100] = "file://";
//    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
//    filename = gtk_file_chooser_get_filename(chooser);
//    strcat(video_loc, filename);
//    g_object_set(G_OBJECT(pipeline), "uri", video_loc, NULL);
//    gst_element_set_state(pipeline, GST_STATE_PLAYING);
//    g_free(filename);
//  }
//
//  gtk_widget_destroy(dialog);
//}

int main(int argc, char *argv[]) {
  gst_init(&argc, &argv);
  gtk_init(&argc, &argv);

  pipeline = gst_element_factory_make("playbin", "play");
  g_object_set(G_OBJECT(pipeline), "uri",
               "http://docs.gstreamer.com/media/sintel_trailer-480p.webm",
               NULL);

  bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
  gst_element_set_state(pipeline, GST_STATE_READY);

  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  video_window = gtk_drawing_area_new();
  g_signal_connect(video_window, "realize", G_CALLBACK(video_widget_realize_cb),
                   NULL);
  // gtk_widget_set_double_buffered(video_window, FALSE);

  //  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  //  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  //  control = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  //  // add video_window in hbox
  //  gtk_box_pack_start(GTK_BOX(hbox), video_window, TRUE, TRUE, 0);

  //  // create buttons
  //  Play = gtk_button_new_with_label("Play");
  //  g_signal_connect(G_OBJECT(Play), "clicked", G_CALLBACK(play_cb),
  //  pipeline);
  //  Pause = gtk_button_new_with_label("Pause");
  //  g_signal_connect(G_OBJECT(Pause), "clicked", G_CALLBACK(pause_cb),
  //  pipeline);
  //  Open = gtk_button_new_with_label("Open");
  //  g_signal_connect(G_OBJECT(Open), "clicked", G_CALLBACK(open_cb),
  //  pipeline);
  //
  //  // add button box to hbox_controller
  //  gtk_box_pack_start(GTK_BOX(control), Play, TRUE, TRUE, 0);
  //  gtk_box_pack_start(GTK_BOX(control), Pause, TRUE, TRUE, 0);
  //  gtk_box_pack_start(GTK_BOX(control), Open, TRUE, TRUE, 0);

  // add vbox to main window
  // gtk_container_add(GTK_CONTAINER(main_window), vbox);
  gtk_container_add(GTK_CONTAINER(main_window), video_window);
  // add hbox containing video_window to vbox
  //  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
  //  gtk_box_pack_start(GTK_BOX(vbox), control, FALSE, FALSE, 0);

  gtk_widget_show_all(main_window);
  gtk_widget_realize(video_window);

  gst_element_set_state(pipeline, GST_STATE_PLAYING);
  // set up sync handler for setting the xid once the pipeline is started
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
  video_window_handle = (guintptr)GDK_WINDOW_HWND(gtk_widget_get_window(video_window));
#elif defined GDK_WINDOWING_QUARTZ
  video_window_handle = gdk_quartz_window_get_nsview(gtk_widget_get_window(video_window));
#elif defined GDK_WINDOWING_X11
  video_window_handle = GDK_WINDOW_XID(gtk_widget_get_window(video_window));
#endif
//#ifdef GDK_WINDOWING_X11
//  {
//    gulong xid = GDK_WINDOW_XID(gtk_widget_get_window(video_window));
//    video_window_handle = xid;
//  }
//#endif
}

static GstBusSyncReply bus_sync_handler(GstBus *bus, GstMessage *message,
                                        gpointer user_data) {
  // ignore anything but 'prepare-window-handle' element messages
  if (!gst_is_video_overlay_prepare_window_handle_message(message))
    return GST_BUS_PASS;

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
