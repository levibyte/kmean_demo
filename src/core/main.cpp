#include "my_renderer.h"

int main( int argc, char* args[] )
{
    LeMySdlRenderer* re = new LeMySdlRenderer;
    re->enter_event_loop();
}
