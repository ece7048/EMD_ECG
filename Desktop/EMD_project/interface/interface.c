#include <gtk/gtk.h>
// gcc interface.c -o mywindow `pkg-config --cflags --libs gtk+-3.0 gladeui-2.0`
//gcc `pkg-config --cflags gtk+-3.0` -o interface interface.c `pkg-config --libs gtk+-3.0`

// pkg-config --list-all | grep (gtk or glade)

G_MODULE_EXPORT void
print_1 (GtkButton *button,
             gpointer   data)
{
  g_print ("RUN\n");
}
G_MODULE_EXPORT void
print_2 (GtkButton *button,
             gpointer   data)
{
  g_print ("STOP\n");
}

int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;
  GtkWidget *window;
  GtkButton *button;

  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "interface.glade", NULL);
  window = GTK_WIDGET(gtk_builder_get_object (builder, "EMD parameters"));
  gtk_builder_connect_signals(builder,NULL);
  g_object_unref(G_OBJECT(builder));

  /* Connect signal handlers to the constructed widgets. */
 // window = GTK_WIDGET(gtk_builder_get_object (builder, "EMD parameters"));
 // g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

 // button = gtk_builder_get_object (builder, "run");
  //g_signal_connect (button, "clicked", G_CALLBACK (print_1), NULL);

  //button = gtk_builder_get_object (builder, "stop");
  //g_signal_connect (button, "clicked", G_CALLBACK (print_2), NULL);

  //button = gtk_builder_get_object (builder, "quit");
  //g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  
 

  /* Show window. All other widgets are automatically shown by GtkBuilder */
gtk_widget_show(window);
gtk_main ();

  return 0;
}
