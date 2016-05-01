#include "vonkoch.h"
#include <GL/glew.h>
using namespace std;

VonKoch::VonKoch(point init1, point init2, string tp, int numIter)
{
    type = tp;
    this->numIter = numIter;
    pointList.push_back(init1);
    pointList.push_back(init2);
}

list<point> VonKoch::calc3p(point P1, point P2)
{
    list<point> new3P;
    point p1, p2, p3;
    p1.x = (P2.x - P1.x) / 3;
    p1.y = (P2.y - P1.y) / 3;
    p3.x = (2*(P2.x - P1.x)) / 3;
    p3.y = (2*(P2.y - P1.y)) / 3;
    p2.x = 0.5;
    p2.y = 0.5;

    new3P.push_back(p1);
    new3P.push_back(p2);
    new3P.push_back(p3);
    return new3P;
}

void VonKoch::insert3p(list<point> newPoint, int idx)
{
    vector<point>::iterator iter = pointList.begin();
    advance(iter, idx + 1);
    pointList.insert(iter, newPoint.begin(), newPoint.end());
}

void VonKoch::nextFrameVertices()
{
    vector<point>::iterator iter = pointList.begin();
    int s = int(pointList.size());
    list<point> temp;
    for (int i = 0; i < s; i++)
    {
        if(i+1 >= s)
        {
            if (type == "line")
            {
                continue;
            }
            else
            {
                temp = calc3p(pointList.at(i), pointList.at(0));
                insert3p(temp, i);
            }
        }
        else
        {
            temp = calc3p(pointList.at(i), pointList.at(i + 1));
            insert3p(temp, i);
        }

    }

}

void VonKoch::build_GL_vertices()
{
    int sz = int(pointList.size());
    if(type=="line")
    {
        glBegin(GL_LINE_STRIP);
        glColor4f(1.0f, 0.3f, 0.5f, 0.8f);
        for (int i = 0; i < sz; i++)
        {
            glVertex2f(GLfloat(pointList.at(i).x), GLfloat(pointList.at(i).y));
        }
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_LOOP);
        glColor4f(1.0f, 0.1f, 0.1f, 0.8f);
        for (int i = 0; i < sz; i++)
        {
            glVertex2f(GLfloat(pointList.at(i).x), GLfloat(pointList.at(i).y));
        }
        glEnd();
    }
}

VonKoch::~VonKoch()
{
    type = "";
    pointList.clear();
}
