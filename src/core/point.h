#ifndef point_h
#define point_h

#include <vector>
#include <cmath>

class LePoint
{
    public:
    
    static LePoint get_centroid(const std::vector<LePoint>& v) {
        //assert(!v.empty());
        LePoint centroid;
        
        int x = 0; 
        int y = 0;
        for ( int i = 0; i < v.size(); i++ )
        {
            x += v[i].x();
            y += v[i].y();
        }
        centroid.rx() = x / v.size();
        centroid.ry() = y / v.size();  
        
        return centroid;
    }


    static float distance(const LePoint& a, const LePoint& b) {
        return sqrt(pow(abs(a.x() - b.x()), 2) + pow(abs(a.y() - b.y()), 2));
    }

    public: 
        LePoint():m_x(0),m_y(0) {}
        LePoint(int x, int y):m_x(x),m_y(y) {}
        int x() const { return m_x; }
        int y() const { return m_y; }
        int& ry() { return m_y; }
        int& rx() { return m_x; }
        
 
    private:
        int m_x;
        int m_y;
};

namespace {
    bool operator<(const LePoint &lhs, const LePoint &rhs) {
        return (lhs.x() < rhs.x()) || ((lhs.x() == rhs.x()) && (lhs.y() < rhs.y()));
    }       
}

#endif
