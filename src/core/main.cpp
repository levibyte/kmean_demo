#include "controller.h"

int main( int argc, char* args[] )
{
    unsigned int k = 3;
    unsigned int gravity = 30;
    Controller c(k,gravity);
    c.enter_event_loop();
}
