#ifndef kmeans_h
#define kmeans_h

#include "point.h"
#include "../renderer/rendering_controller_impl_base.h"

#include <map>
#include <set>
#include <vector>


class KMeansAlgo 
{

public:  
    
    KMeansAlgo(LeRenderingControllerImplBase* renderer, unsigned int k, unsigned int gravity);
    void init();     
    void add_new_point(const LePoint& p);
    void classify_and_draw();
    void assign_classes();
    void draw_classes();

    //bool is_accepting();

    //TODO: move to renderer
    enum LeColor {red,blue,pink,yellow,green,unknown = 999};

    void set_color(LeColor c = unknown ) {
        switch (c) {
            case red: m_renderer->set_drawing_color(255,0,0); break;  
            case blue: m_renderer->set_drawing_color(0,0,255); break;
            case pink: m_renderer->set_drawing_color(255,0,255); break;
            case green: m_renderer->set_drawing_color(0,255,0); break;
            case yellow: m_renderer->set_drawing_color(0xFF, 0xFF, 0x00); break;
            default:m_renderer->set_drawing_color(255,255,255); break;
        }
    }

private:
    void create_pivot_points();

    void draw_colored_class(LeColor c, const std::vector<LePoint>& v);
    void set_class(int ii);

    bool is_all_converged();
    bool is_done(); 
    

private:
    int m_K;
    float m_gravity;
    LeRenderingControllerImplBase* m_renderer;
    
    std::map<LeColor,std::vector<LePoint> > m_class2points;
    std::set<LePoint> m_seen_points;
    std::vector<bool> m_converge_flags;
    std::vector<LePoint> m_all_points;
    std::vector<LePoint> m_pivot_points;
};

#endif
