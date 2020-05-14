/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
#include "gdump.c"
#ifdef G_OS_WIN32
  #include <gio/gwin32outputstream.h>
#else
  #include <gio/gunixoutputstream.h>
#endif

int
main (int    argc,
      char **argv)
{
  int i;
  GOutputStream *Stdout;
  GModule *self;

#if defined(G_OS_WIN32)
  Stdout = g_win32_output_stream_new (1, FALSE);
#else
  Stdout = g_output_stream (1, FALSE);
#endif

  self = g_module_open (NULL, 0);

  for (i = 1; i < argc; i++)
    {
      GError *error = NULL;
      GType type;

      type = invoke_get_type (self, argv[i], &error);
      if (!type)
	{
	  g_printerr ("%s\n", error->message);
	  g_clear_error (&error);
	}
      else
	dump_type (type, argv[i], Stdout);
    }

  return 0;
}
