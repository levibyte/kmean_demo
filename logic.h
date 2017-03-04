#include "init.h"

#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>

bool operator<(const SDL_Point &lhs, const SDL_Point &rhs) {
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}


class JManager {
  
  public:  
    
	JManager() {
	    m_K = 3;
             //std::vector<SDL_Point> v;
	    m_converge_flags.resize(m_K);
             for(int i=0;i<m_K;i++){ 
	       std::vector<SDL_Point> v; 
	       m_class2points[static_cast<JColor>(i)] = v; 
	       m_converge_flags[i] = false;
	    }
	}
	
        enum JColor {red,blue,pink,yellow,green,unknown = 999};

	
        void set_color(JColor c = unknown ) {
              switch (c) {
                case red: SDL_SetRenderDrawColor(gRenderer,255,0,0,255); break;  
                case blue: SDL_SetRenderDrawColor(gRenderer,0,0,255,255); break;
                case pink: SDL_SetRenderDrawColor(gRenderer,255,0,255,255); break;
                case green: SDL_SetRenderDrawColor(gRenderer,0,255,0,255); break;
                case yellow: SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF ); break;
                default:SDL_SetRenderDrawColor(gRenderer,0,0,0,255); break;
              }
        }


        float distance(const SDL_Point& a, const SDL_Point& b){
          return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
        }


        SDL_Point get_centroid(const std::vector<SDL_Point>& v) {
              assert(!v.empty());
              SDL_Point centroid;
              
              int x = 0; 
              int y = 0;
              for ( int i = 0; i < v.size(); i++ )
              {
                  x += v[i].x;
                  y += v[i].y;
              }
              centroid.x = x / v.size();
              centroid.y = y / v.size();  
              
              return centroid;
        }
        

	void draw_colored_class(JColor c, const std::vector<SDL_Point>& v) {
	      if(v.empty()) return;
	      set_color(c);
              SDL_RenderDrawPoints(gRenderer,&(v[0]),v.size());
              //std::cout << static_cast<int>(c) << " " << v.size() << std::endl;
              //for(int i=0;i<v.size();i++) SDL_RenderDrawPoint(gRenderer,v[i].x,v[i].y);
	}
	
        void set_class(int ii) {
             std::vector<SDL_Point> v = m_class2points[static_cast<JColor>(ii)];
             //m_all_points.push_back(p);
             
             m_gravity = 10;
	     std::vector<SDL_Point>::iterator i;
	     for(i = m_all_points.begin();i!=m_all_points.end();i++)
                  if( distance(*i,m_pivot_points[ii]) < m_gravity ) v.push_back(*i);
                //}
                //}
               //}

             m_class2points[static_cast<JColor>(ii)] = v;
             //assert(!v.empty());
              if (!v.empty()) {
                SDL_Point l = m_pivot_points[ii];
                SDL_Point n = get_centroid(v);
                if ( l.x == n.x && l.y == n.y )
                  //m_pivot_points[ii] = get_centroid(v);
                  m_converge_flags[ii] = true;
                else
                  m_pivot_points[ii] = get_centroid(v);
              }
	}
	

        void draw_classes() {
              draw_colored_class(unknown,m_all_points);
              draw_colored_class(green,m_pivot_points);
              for(int i=0;i<m_K;i++) draw_colored_class(static_cast<JColor>(i), m_class2points[static_cast<JColor>(i)]);
        }

        void set_classes() {
              for(int i=0;i<m_K;i++) set_class(i);
	}


        bool is_all_converged() {
              bool res;
              for(int i=0;i<m_K;i++) res = res & m_converge_flags[i];
        }
        
        bool is_done ( ) { return m_seen_points.size() == m_all_points.size(); }
        
        void classify() {
            //if ( !is_done() && is_all_converged() ) {
            //  create_pivot_points();
            //}
            set_classes();
        }
        
        void classify_and_draw() {
            classify();
            draw_classes();
        }
        
        void init_data() {
	  /// 
          for(unsigned int i=0;i<300;i++) {
             //SDL_Point p;
             SDL_Point p,p2,p3;
             p.x=rand()%20;
             p.y=rand()%20;
             
             p2.x = p.x + 30;
             p2.y = p.y + 30;
             
             p3.x = p2.x + 30;
             p3.y = p2.y + 30;
             
             
             m_all_points.push_back(p);
             m_all_points.push_back(p2);
             m_all_points.push_back(p3);
	  }
	  
	  create_pivot_points();
	  
	}
         
         void create_pivot_points() {
	    for(unsigned int i=0;i<m_K;i++) {
             //SDL_Point p;
             //p.x=rand()%100;
             //p.y=rand()%100;
             //m_pivot_points.push_back(p);
             m_pivot_points.push_back(m_all_points[rand()%m_all_points.size()]);
          }
	 }
	
  private:
          int m_K;
          float m_gravity;
	  std::map<JColor,std::vector<SDL_Point> > m_class2points;
          std::set<SDL_Point> m_seen_points;
          std::vector<bool> m_converge_flags;
          std::vector<SDL_Point> m_all_points;
	  std::vector<SDL_Point> m_pivot_points;
};