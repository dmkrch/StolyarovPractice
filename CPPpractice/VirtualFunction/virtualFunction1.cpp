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
    int GetColor() { return color; }
};


void Pixel::Show() 
{
}

void Pixel::Hide()
{
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
}

void Circle::Hide()
{
}



class PolygonalChain : public GraphObject
{
private:   
    struct Vertex 
    {
        double dx;
        double dy;
        Vertex* next;
    };

    Vertex* first;

public:
    PolygonalChain(double x, double y, int color)
        : GraphObject(x, y, color), first(0) {}
    virtual ~PolygonalChain();
    void AddVertex(double adx, double ady);
    virtual void Show();
    virtual void Hide();
};


void PolygonalChain::Show() 
{
}

void PolygonalChain::Hide()
{
}



void PolygonalChain::AddVertex(double ax, double ay)
{
    Vertex* tmp = new Vertex;
    tmp->dx = ax;
    tmp->dy = ay;
    tmp->next = first;
    first = tmp;
}

PolygonalChain::~PolygonalChain()
{
    while(first)
    {
        Vertex* tmp = first;
        first = first->next;
        delete tmp;
    }
}





class Square : public PolygonalChain 
{
public:
    Square(double x, double y, double a, int color)
        : PolygonalChain(x, y, color)
    {
        AddVertex(0, 0);
        AddVertex(0, a);
        AddVertex(a, a);
        AddVertex(a, 0);
        AddVertex(0, 0);
    }
};



void MakeAction(GraphObject* obj)
{
    obj->Show();
}





int main()
{
    /* example 1 of polymorphism */
    Circle cr1(25.1, -50.2, 3.0, 255);
    Pixel px1(26, 28.3, -255);

    MakeAction(&cr1);
    MakeAction(&px1);

    /* example 2 */
    int scene_length = 3;
    GraphObject** scene;    // stores pointers to objects of graphObject

    // allocating memory according to scene_length
    scene = new GraphObject*[scene_length];

    /* we can use this way, because we can cast 
       Pixel* to GraphObj, or Circle* to GraphObj */
    scene[0] = new Pixel(1.25, 15.75, 255);
    scene[1] = new Circle(20.9, 7.25, 3.5, 243);
    scene[2] = new Square(55.0, 30.5, 10.0, 201);

    ((Pixel*)scene[0])->GetColor(); // right
    // scene[0]->GetColor(); // wrong - this is graphObj already

    // deleting all objects + scene
    for (int i = 0; i < scene_length; i++)
        delete scene[i];
    delete [] scene;



    return 0;
}