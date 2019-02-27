#include "kmeans.h"

KMeansAlgo::KMeansAlgo(LeRenderingControllerImplBase* renderer, unsigned int k, unsigned int gravity):m_renderer(renderer),m_K(k),m_gravity(gravity) {
    m_converge_flags.resize(m_K);
    for(int i=0;i<m_K;i++){ 
        std::vector<LePoint> v; 
        m_class2points[static_cast<LeColor>(i)] = v; 
        m_converge_flags[i] = false;
    }
}

void KMeansAlgo::init() {
    create_pivot_points();
}

void KMeansAlgo::add_new_point(const LePoint& p) {
    //LePoint p(x,y);
    m_all_points.push_back(p);
}

void KMeansAlgo::classify_and_draw() {
    assign_classes();
    draw_classes();
}

void KMeansAlgo::draw_classes() {
    draw_colored_class(unknown,m_all_points);
    draw_colored_class(green,m_pivot_points);
    for(int i=0;i<m_K;i++) 
        draw_colored_class(static_cast<LeColor>(i), m_class2points[static_cast<LeColor>(i)]);
}

void KMeansAlgo::assign_classes() {
    //TODO: while(!is_all_converged())
      for(int j=0;j<40; ++j)  
        for(int i=0;i<m_K;i++) 
            set_class(i);
}


void KMeansAlgo::draw_colored_class(LeColor c, const std::vector<LePoint>& v) {
    if(v.empty()) 
        return;
    
    set_color(c);
    for ( int i=0; i<v.size(); ++i)
        m_renderer->draw_point(v[i].y(),v[i].x());
        
    //draw_points(&(v[0]),v.size());
}

void KMeansAlgo::set_class(int ii) {
    std::vector<LePoint> v = m_class2points[static_cast<LeColor>(ii)];
    
    std::vector<LePoint>::iterator i;
    for(i = m_all_points.begin();i!=m_all_points.end();i++)
        if( LePoint::distance(*i,m_pivot_points[ii]) < m_gravity ) v.push_back(*i);
 
    m_class2points[static_cast<LeColor>(ii)] = v;
    //assert(!v.empty());
    if (!v.empty()) {
        LePoint l = m_pivot_points[ii];
        LePoint n = LePoint::get_centroid(v);
        if ( l.x() == n.x() && l.y() == n.y() )
            m_converge_flags[ii] = true;
        else
            m_pivot_points[ii] = LePoint::get_centroid(v);
    }
}


bool KMeansAlgo::is_all_converged() {
    bool res = false;
    for(int i=0;i<m_K;i++) 
        res = res & m_converge_flags[i];
    
    return res;
}

bool KMeansAlgo::is_done ( ) { 
    return m_seen_points.size() == m_all_points.size(); 
}


void KMeansAlgo::create_pivot_points() {
    for(unsigned int i=0;i<m_K;i++)
        m_pivot_points.push_back(m_all_points[rand()%m_all_points.size()]);

}
