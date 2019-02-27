#ifndef my_renderer_h
#define my_renderer_h

#include "kmeans.h"
#include "../renderer/sdl_renderer.h"

#include <cassert>

class LeMySdlRenderer: public LeSdlRenderer
{

    KMeansAlgo* j;

    virtual void on_key_press(unsigned int) {
        //short way of create brand new state
        delete j;
        j = new KMeansAlgo(this,3,20);
        j->init();
        //assert(0);
    }
    
    virtual void on_mouse_click(unsigned int) {
        j->assign_classes();
    }
    
    virtual void on_draw_event() {
        //j->done()
        j->draw_classes();
    }
        
public:
    LeMySdlRenderer() {
        j = new KMeansAlgo(this,3,20);
        j->init();
    }
    
};

#endif
