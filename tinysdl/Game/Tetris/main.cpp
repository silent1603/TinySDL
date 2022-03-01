#include "main.hpp"
int main(int argc, char *argv[])
{

  TETRIS_INFO("Tetris Log init");
  Tetris::App app("Tetris", 800, 600);
  if (app.init())
  {
	  app.update();
  }
  app.clean();
  return 0;
}