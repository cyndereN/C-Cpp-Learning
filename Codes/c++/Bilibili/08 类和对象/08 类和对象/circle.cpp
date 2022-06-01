#include "circle.h"


void Circle::setR(int r) {
	m_r = r;
}


int Circle::getR() {
	return m_r;
}

void Circle::setCenter(Point center) {
	m_center = center;
}

Point Circle::getCenter() {
	return m_center;
}