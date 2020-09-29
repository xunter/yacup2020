#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std; 

#define TYPE_CIRCLE 0
#define TYPE_RECTANGLE 1
#define null 0

vector<string> split(const string& str, const string& delim);

struct CoordsF {
 float x;
 float y;
};

class Line {
 public:
  CoordsF p1;
  CoordsF p2;

  Line() { }
  Line(CoordsF &p1, CoordsF &p2) { this->setCoords(p1, p2); }

  void setCoords(const CoordsF &p1, const CoordsF &p2) {
   this->p1 = p1;
   this->p2 = p2;
  }
};

bool cutsInHalf(Line &line, float x, float y);

class Shape {
 public:
  virtual CoordsF calcCenter() const {
   CoordsF c;
   c.x = 0;
   c.y = 0;
   return c;
  }
  int m_type;

  int getType() { return m_type; }

  Shape() {}
  Shape(int type) : m_type(type) {}
  virtual ~Shape() {}
};

class Rectangle : public Shape {
 public:
  Rectangle() { this->m_type = TYPE_RECTANGLE; }

  void setCoords(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

  int calcAreaRect();

  int leftSize();
  int topSize();
  int rightSize();
  int bottomSize();

  CoordsF calcCenter() const override {
   float xstart = x1;
   float xend = x3 == x1 ? x2 : x3;
   float ystart = y1;
   float yend = y2 == y1 ? y3 : y2;
   float x = xstart + (xend - xstart) / 2.0;
   float y = ystart + (yend - ystart) / 2.0;
   CoordsF c;
   c.x = x;
   c.y = y;
   return c;
  }

  float x1;
  float y1;
  float x2;
  float y2;
  float x3;
  float y3;
  float x4;
  float y4;
};

class Circle : public Shape {
 public:
  Circle() { this->m_type = TYPE_CIRCLE; }

  int calcAreaCircle();
  //int intersectsLine(Line &line);
  void setCoords(int r, float x, float y);

  CoordsF calcCenter() const override { 
   CoordsF coordsf; 
   coordsf.x = this->x; 
   coordsf.y = this->y; 
   return coordsf; 
  }

  int r;
  float x;
  float y;
};


int main()
{
 string str_buf;
 getline(cin, str_buf);

 int shapes_count = atoi(str_buf.c_str());

 if (shapes_count < 3) {
  cout << "Yes" << endl;
  return 0;
 }

 vector<Shape *> shapes;

 Shape *shapeForCalcLinePoint1 = null;
 Shape *shapeForCalcLinePoint2 = null;
 for (int i = 0; i < shapes_count; i++) {
  getline(cin, str_buf);
  vector<string> tokens = split(str_buf, " ");
  int shape_type = atoi(tokens[0].c_str());
  if (shape_type == TYPE_CIRCLE) {
   int r = atoi(tokens[1].c_str());
   float x = atof(tokens[2].c_str());
   float y = atof(tokens[3].c_str());
   Circle *circle = new Circle();
   circle->setCoords(r, x, y);
   shapes.push_back((Shape *)circle);
  } else if (shape_type == TYPE_RECTANGLE) {
   float x1 = atof(tokens[1].c_str());
   float y1 = atof(tokens[2].c_str());
   float x2 = atof(tokens[3].c_str());
   float y2 = atof(tokens[4].c_str());
   float x3 = atof(tokens[5].c_str());
   float y3 = atof(tokens[6].c_str());
   float x4 = atof(tokens[7].c_str());
   float y4 = atof(tokens[8].c_str());
   Rectangle *rectangle = new Rectangle();
   rectangle->setCoords(x1, y1, x2, y2, x3, y3, x4, y4);
   shapes.push_back(rectangle);
  }
  if (shapeForCalcLinePoint1 == null) {
   shapeForCalcLinePoint1 = shapes[i];
  } else if (shapeForCalcLinePoint2 == null) {
   Shape *shapeForCalcLinePointNext = shapes[i];
   CoordsF center1 = shapeForCalcLinePoint1->calcCenter();
   CoordsF center2 = shapeForCalcLinePointNext->calcCenter();

   if (center1.x != center2.x && center1.y != center2.y) {
    shapeForCalcLinePoint2 = shapeForCalcLinePointNext;
   }
  }
 }

 if (shapeForCalcLinePoint2 == null) {
  //all shapes on hor or ver straight line
  cout << "Yes" << endl;
  return 0;
 }

 const CoordsF centerCoords1 = shapeForCalcLinePoint1->calcCenter();
 const CoordsF centerCoords2 = shapeForCalcLinePoint2->calcCenter();
 Line line;
 line.setCoords(centerCoords1, centerCoords2);

 for (int i = 2; i < shapes.size(); i++) {
  const Shape *shape = shapes[i];
  const CoordsF &center = shape->calcCenter();
  if (!cutsInHalf(line, center.x, center.y)) {
   cout << "No" << endl;
   return 0;
  }
 }


 cout << "Yes" << endl;
 return 0;
}

void Rectangle::setCoords(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
 this->x1 = x1;
 this->y1 = y1;
 this->x2 = x2;
 this->y2 = y2;
 this->x3 = x3;
 this->y3 = y3;
 this->x4 = x4;
 this->y4 = y4;
}

int Rectangle::calcAreaRect() {
 int areasize = this->leftSize() * this->topSize();
 return areasize;
}

int Rectangle::leftSize() {
 int x12diff = this->x2 - this->x1;
 int y12diff = this->y2 - this->y1;
 int leftsize = x12diff == 0 ? y12diff : x12diff;
 return abs(leftsize);
}

int Rectangle::topSize() {
 int x23diff = this->x3 - this->x2;
 int y23diff = this->y3 - this->y2;
 int topsize = x23diff == 0 ? y23diff : x23diff;
 return abs(topsize);
}

int Rectangle::rightSize() {
 int x34diff = this->x4 - this->x3;
 int y34diff = this->y4 - this->y3;
 int rightsize = x34diff == 0 ? y34diff : x34diff;
 return abs(rightsize);
}

int Rectangle::bottomSize() {
 int x41diff = this->x1 - this->x4;
 int y41diff = this->y1 - this->y4;
 int bottomsize = x41diff == 0 ? y41diff : x41diff;
 return abs(bottomsize);
}

int Circle::calcAreaCircle() {
   return M_PI * this->r * this->r;
}

void Circle::setCoords(int r, float x, float y) {
 this->x = x;
 this->y = y;
 this->r = r;
}

/*
int Circle::intersectsLine(Line &line) {
 int x1 = line.p1.x;
 int x2 = line.p2.x;
 int y1 = line.p1.y;
 int y2 = line.p2.y;
 int r = this->r;
 int x = this->x;
 int y = this->y;
 int dx = x2 - x1;
 int dy = y2 - y1;
 int dr = sqrt(dx * dx + dy * dy);
 int dgrand = x1 * y2 - x2 * y1;
 int discr = r * r * dr * dr - dgrand * dgrand;

 bool intersectionNoTangent = discr > 0;
 if (!intersectionNoTangent) {
  return 0;
 }


}

bool Line::cutsCircleInHalf(Circle &circle) {
 int x = circle.x;
 int y = circle.y;
 
 return cutsInHalf(this, x, y);
}

bool Line::cutsRectangleInHalf(Rectangle &rectangle) {
 int x1 = rectangle.x1;
 int x2 = rectangle.x2;
 int y1 = rectangle.y1;
 int y2 = rectangle.y2;

 float xcenter = (x2 - x1) / 2.0;
 float ycenter = (y2 - y1) / 2.0;

 return cutsInHalf(this, xcenter, ycenter);
}
*/

bool cutsInHalf(Line &line, float x, float y) {
 float x1 = line.p1.x;
 float x2 = line.p2.x;
 float y1 = line.p1.y;
 float y2 = line.p2.y;
 float a = (y2 - y1) / (x2 - x1);
 return (y - y1) == a * (x - x1);
}

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
} //https://stackoverflow.com/a/37454181/1487713