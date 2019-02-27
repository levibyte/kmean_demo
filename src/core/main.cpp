#include "controller.h"

int main( int argc, char* args[] )
{
    unsigned int k = 4;
    unsigned int gravity = 20;
    Controller c(k,gravity);
    c.enter_event_loop();
}
