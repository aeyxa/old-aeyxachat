#include "../common/common.h"
#include "client_ncurses.h"

void Reading(SSL *ssl)
{
  char buffer[300];
  WINDOW *display_top_border, *display_top_window;

  display_top_border = draw_top_border();
  display_top_window = draw_top_window();

  top_border_configure(display_top_border);
  top_window_configure(display_top_window);

  for(;;)
  {
    if(SSL_read(ssl,buffer,sizeof(buffer)))
    {
      redraw_window(display_top_window,buffer);
      memset(buffer,0,sizeof(buffer));
    }
  }
  std::cout << "Connection was terminated!" << std::endl;
  endwin();
}

void Writing(SSL *ssl)
{
  char buffer[256];
  WINDOW *display_bot_border, *display_bot_window;

  display_bot_border = draw_bot_border();
  display_bot_window = draw_bot_window();

  bot_border_configure(display_bot_border);
  bot_window_configure(display_bot_window);

  for(;;)
  {
    redraw_writer(display_bot_window,buffer);
    wgetnstr(display_bot_window,buffer,255);
    SSL_write(ssl,buffer,sizeof(buffer));
    memset(buffer,0,sizeof(buffer));
    wclear(display_bot_window);
  }
  std::cout << "Connection was terminated!" << std::endl;
  endwin();
}

void SpeakConnection(int sock)
{
  SSL *ssl = WrapSocketWithSSL(sock,"client");

  std::thread thread_one(Writing,ssl);
  std::thread thread_two(Reading,ssl);

  thread_one.join(); thread_two.join();
}
