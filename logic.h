#include "init.h"

#include <map>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>

class JPoint{
 
};


float distance(SDL_Point a,  SDL_Point b){
  float f = sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
  //std::cout << f << std::endl;
  return f;
}


bool operator<(const SDL_Point &lhs, const SDL_Point &rhs) {
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}


class JManager {
  
  public:  
    
	JManager() {
	    m_K = 2;
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




        SDL_Point get_centroid(std::vector<SDL_Point> v) {
              //assert(!v.empty());
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
        
//        

	void draw_colored_class(JColor c, const std::vector<SDL_Point>& v) {
	      if(v.empty()) return;
	      set_color(c);
              for(int i=0;i<v.size();i++) SDL_RenderDrawPoint(gRenderer,v[i].x,v[i].y);
	}
	
        void draw_classes() {
              draw_colored_class(unknown,m_all_points);
	      draw_colored_class(green,m_pivot_points);
	      for(int i=0;i<m_K;i++) draw_colored_class(static_cast<JColor>(i), m_class2points[static_cast<JColor>(i)]);
        }

        void set_class(int ii) {
	     //std::cout << "setting class "<< ii << std::endl;
             std::vector<SDL_Point> v;
           
	     float gravity = 20.0;
	     std::vector<SDL_Point>::iterator i;
	     for(i = m_all_points.begin();i!=m_all_points.end();i++)
               if ( distance(*i,m_pivot_points[ii]) < gravity ) v.push_back(*i);

             m_class2points[static_cast<JColor>(ii)] = v;
              
              if (!v.empty())
                m_pivot_points[ii] = get_centroid(v);
	}
	
	
        void set_classes() {
	    for(int i=0;i<m_K;i++) set_class(i);
	}


        void init_data() {
	  /* 
          for(unsigned int i=0;i<10;i++) {
             SDL_Point p;
             p.x=rand()%100;
             p.y=rand()%100;
             m_all_points.push_back(p);
           }
          /**/
	  
          SDL_Point p7 = { 10 , 30 };
          SDL_Point p8 = { 15 , 30 };
          SDL_Point p9 = { 20 , 30 };
          SDL_Point p4 = { 10 , 20 };
          SDL_Point p5 = { 15 , 20 };
          SDL_Point p6 = { 20 , 20 };
          SDL_Point p1 = { 10 , 10 };
          SDL_Point p2 = { 15 , 10 };
          SDL_Point p3 = { 20 , 10 };
          
          
          m_all_points.push_back(p1);
          m_all_points.push_back(p2);
          m_all_points.push_back(p3);
          m_all_points.push_back(p4);
          m_all_points.push_back(p5);
          m_all_points.push_back(p6);
          m_all_points.push_back(p7);
          m_all_points.push_back(p8);
          m_all_points.push_back(p9);
          
          
               
          SDL_Point p71 = { 25 , 40 };
          SDL_Point p81 = { 30 , 40 };
          SDL_Point p91 = { 35 , 40 };
          SDL_Point p41 = { 25 , 50 };
          SDL_Point p51 = { 30 , 50 };
          SDL_Point p61 = { 35 , 50 };
          SDL_Point p11 = { 25 , 60 };
          SDL_Point p21 = { 30 , 60 };
          SDL_Point p31 = { 35 , 60 };
          
                   
          m_all_points.push_back(p11);
          m_all_points.push_back(p21);
          m_all_points.push_back(p31);
          m_all_points.push_back(p41);
          m_all_points.push_back(p51);
          m_all_points.push_back(p61);
          m_all_points.push_back(p71);
          m_all_points.push_back(p81);
          m_all_points.push_back(p91);


	  for(unsigned int i=0;i<m_K;i++) 
             m_pivot_points.push_back(m_all_points[rand()%m_all_points.size()]);
	}

	
  private:
          int m_K;
	  std::map<JColor,std::vector<SDL_Point> > m_class2points;
          std::vector<SDL_Point> m_all_points;
	  std::vector<SDL_Point> m_pivot_points;
};