#include <stdio.h>


/*actually the example is not correct. It will be fixed in 
  virtualFunction2.cpp */
class Pixel
{
private:   
    double x;
    double y;
    int color;
public:
    Pixel(double ax, double ay, int acolor)
        : x(ax), y(ay), color(acolor) {}
    virtual void Show();
    virtual void Hide();
    void Move(double nx, double ny);

    double GetX() { return x; }
};

void Pixel::Show() {/*general implementation*/}
void Pixel::Hide() {/*general implementation*/}
void Pixel::Move(double nx, double ny)
{
    Hide();
    x = nx;
    y = ny;
    Show();
}


class Circle : public Pixel
{
private:
    double radius;
public:
    Circle(double x, double y, int color, double rad)
        : Pixel(x, y, color), radius(rad) {}

    void Show();
    void Hide();
}

void Circle::Show() {/* another implementation */}
void Circle::Hide() {/* another implementation */}


int main()
{
    
    return 0;
}