#ifndef my_renderer_h
#define my_renderer_h

#include "kmeans.h"
#include "point.h"
#include "../renderer/sdl_renderer.h"

#include <cassert>

class Controller: public LeSdlRenderer
{

    KMeansAlgo* j;
    unsigned int m_K;
    unsigned int m_gravity;

    void create_nice_data() {
        //creating data that is distributed nicely
        for(unsigned int i=0;i<300;i++) {
            LePoint p(rand()%20,rand()%20),p2(p.x()+rand()%30,p.y()+rand()%30),p3(p2.x()+rand()%30,p2.y()+rand()%30),p4(p.x()+70, p.y()+70);
            j->add_new_point(p);
            j->add_new_point(p2);
            j->add_new_point(p3);
            j->add_new_point(p4);
            
        }
        j->init();
    }
    
    virtual void on_key_press(unsigned int) {
        //short way of create brand new state
        delete j;
        j = new KMeansAlgo(this,m_K,m_gravity);
        create_nice_data();
        //assert(0);
    }
    
    virtual void on_mouse_click(unsigned int) {
        //start classification when mouse clicked
        j->assign_classes();
    }
    
    virtual void on_draw_event() {
        //TODO: run if only done
        j->draw_classes();
    }
        
public:
    Controller(unsigned int k, unsigned int gravity):m_K(k),m_gravity(gravity) {
        j = new KMeansAlgo(this,m_K,m_gravity);
        create_nice_data();
    }
    
};

#endif
