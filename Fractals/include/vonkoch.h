#ifndef VONKOCH_H
#define VONKOCH_H
#include <list>
#include <string>
#include <vector>

using namespace std;

typedef struct Point
{
    float x;
    float y;
} point;

class VonKoch
{
public:
    VonKoch(point init1, point init2, string tp, int numIter);

    void nextFrameVertices();

    void build_GL_vertices();

    virtual ~VonKoch();
private:
    list<point> calc3p(point P1, point P2);

    void insert3p(list<point> newPoints, int idx);

    vector<point> pointList;
    string type;
    int numIter;
};

#endif // VONKOCH_H
