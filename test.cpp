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
  //std::cout << "distance " << abs(a.x - b.x) << "!!!!" << abs(a.y - b.y); 
  float f = sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
  
  //float f = 1;
  //std::cout << "=====" << f << std::endl;

  return f;
}


bool operator<(const SDL_Point &lhs, const SDL_Point &rhs) {
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}


class JManager {
  
  public:  
        enum JColor {red,blue,green,yellow, unknown};

        void set_color(JColor c = unknown ) {
              switch (c) {
                case red: SDL_SetRenderDrawColor(gRenderer,255,0,0,255); break;  
                case blue: SDL_SetRenderDrawColor(gRenderer,0,0,255,255); break;
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
        void draw_classes() {
              set_color();
              if(m_all_points.empty()) return;
              for(int i=0;i<=m_all_points.size();i++)
                SDL_RenderDrawPoint(gRenderer,m_all_points[i].x,m_all_points[i].y);

               set_color(green);
                SDL_RenderDrawPoint(gRenderer,m_pivot_point1.x,m_pivot_point1.y);
              
               set_color(yellow);
                SDL_RenderDrawPoint(gRenderer,m_pivot_point2.x,m_pivot_point2.y);
                
              //*
              set_color(red);
              std::vector<SDL_Point> v = m_class2points[red];
              if(!v.empty())
                for(int i=0;i<=v.size();i++)
                  SDL_RenderDrawPoint(gRenderer,v[i].x,v[i].y);

              //*
              set_color(blue);
              std::vector<SDL_Point> v1 = m_class2points[blue];
              if(!v1.empty()) 
                for(int i=0;i<=v1.size();i++)
                  SDL_RenderDrawPoint(gRenderer,v1[i].x,v1[i].y);
              /**/
        }

        void set_classes() {
            // assert(0);
            
           
               
             std::vector<SDL_Point> r;
             std::vector<SDL_Point> b;
             std::vector<SDL_Point>::iterator i;
             for(i = m_all_points.begin();i!=m_all_points.end();i++) {
               if ( distance(*i,m_pivot_point1) < 20 ) r.push_back(*i);
               //else  b.push_back(*i);
               else if ( distance(*i,m_pivot_point2) < 20 ) b.push_back(*i);
             }
             
             
              m_class2points[red] = r;
              m_class2points[blue] = b;
              
              if (!r.empty())
                m_pivot_point1 = get_centroid(r);
              
              if (!b.empty())
                m_pivot_point2 = get_centroid(b);
              
        
        }


        void init_data() {
//           * 
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

          
           
             //SDL_Point p;
          m_pivot_point1.x=rand()%30;
          m_pivot_point1.y=rand()%30;
          
          m_pivot_point2.x=rand()%30;
          m_pivot_point2.y=rand()%30;
           
        }
        
  private:
          std::map<JColor,std::vector<SDL_Point> > m_class2points;
          std::vector<SDL_Point> m_all_points;
          SDL_Point m_pivot_point1;
          SDL_Point m_pivot_point2;
          //std::vector<SDL_Point> m_pivot_points;
};

int main( int argc, char* args[] )
{
       if( !init() ) exit(1);
       if( !loadMedia() ) exit(1);

        bool quit = false;
        SDL_Event e;
        JManager j;

        j.init_data();
        //j.set_classes();
       
        SDL_RenderSetScale(gRenderer,6.0,6.0);
       
        while( !quit )
        {
                while( SDL_PollEvent( &e ) != 0 )
                {
                        if( e.type == SDL_QUIT ) quit = true;
                        if( e.type == SDL_MOUSEBUTTONDOWN ) j.set_classes();
                } 
 
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
               
                j.draw_classes();
                
                SDL_RenderPresent( gRenderer );

 
        }

        close();

        return 0;
}