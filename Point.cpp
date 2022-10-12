#include "Point.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}
Point::Point() {
	this->x = 0;
	this->y = 0;
}


Point Point::operator+(const Point& other) {
	Point point;
	point.x = this->x + other.x;
	point.y = this->y + other.y;
	return point;
}
Point& Point::operator+=(const Point& other) {
	*this = *this + other;
	return *this;
}
Point Point::operator-(const Point& other) {
	Point point;
	point.x = this->x - other.x;
	point.y = this->y - other.y;
	return point;
}
Point& Point::operator-=(const Point& other) {
	*this = *this - other;
	return *this;
}


Point Point::operator+(const int& other) {
	Point point;
	point.x = this->x + other;
	point.y = this->y + other;
	return point;
}
Point& Point::operator+=(const int& other) {
	*this = *this + other;
	return *this;
}
Point Point::operator-(const int& other) {
	Point point;
	point.x = this->x - other;
	point.y = this->y - other;
	return point;
}
Point& Point::operator-=(const int& other) {
	*this = *this - other;
	return *this;
}


bool Point::operator==(const Point& other) {
	return x == other.x && y == other.y;
}
bool Point::operator!=(const Point& other) {
	return x != other.x || y != other.y;
}
bool Point::operator<(const Point& other) {
	return x < other.x && y < other.y;
}
bool Point::operator>(const Point& other) {
	return x > other.x&& y > other.y;
}
bool Point::operator<=(const Point& other) {
	return x <= other.x && y <= other.y;
}
bool Point::operator>=(const Point& other) {
	return x >= other.x && y >= other.y;
}
