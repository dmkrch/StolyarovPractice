#include <stdio.h>

class GraphObject
{
protected:
    double x, y;
    int color;
public:
    GraphObject(double ax, double ay, int acolor)
        : x(ax), y(ay), color(acolor) {}
    
    virtual ~GraphObject() {}
    virtual void Show() = 0;
    virtual void Hide() = 0;
    void Move(double nx, double ny);
};

void GraphObject::Move(double nx, double ny)
{
   Hide();
    x = nx;
    y = ny;
    Show();
}


class Pixel : public GraphObject
{
public:
    Pixel(double x, double y, int col)
        : GraphObject(x, y, col) {}
    
    virtual ~Pixel() {}
    virtual void Show();
    virtual void Hide();
};

void Pixel::Show() 
{
    /* realisation of showing pixel */
}

void Pixel::Hide()
{
    /* realisation of hiding pixel */
}


class Circle : public GraphObject
{
private:    
    double radius;
public:
    Circle(double x, double y, double rad, int col)
        : GraphObject(x, y, col), radius(rad) {}
    
    virtual ~Circle() {}
    virtual void Show();
    virtual void Hide();
};

void Circle::Show()
{
    /* realisation of showing circle */
}

void Circle::Hide()
{
    /* realisation of hiding circle */
}


void MakeAction(GraphObject* obj)
{
    obj->Show();
}



int main()
{
    Circle cr1(25.1, -50.2, 3.0, 255);
    Pixel px1(26, 28.3, -255);

    MakeAction(&cr1);
    MakeAction(&px1);


    return 0;
}