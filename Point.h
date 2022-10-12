/*Point Class by Leon Plattner*/

#include <iostream>

class Point
{
public:
    Point();
    Point(int x, int y);

    Point operator+(const Point &other);
    Point &operator+=(const Point &other);
    Point operator-(const Point &other);
    Point &operator-=(const Point &other);

    Point operator+(const int &other);
    Point &operator+=(const int &other);
    Point operator-(const int &other);
    Point &operator-=(const int &other);

    bool operator==(const Point &other);
    bool operator!=(const Point &other);
    bool operator<(const Point &other);
    bool operator>(const Point &other);
    bool operator<=(const Point &other);
    bool operator>=(const Point &other);

    int x = 0;
    int y = 0;
};
