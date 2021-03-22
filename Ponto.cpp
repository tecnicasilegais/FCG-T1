//
//  Ponto.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Ponto.h"
Ponto::Ponto()
{
	x = y = z = 0;
}
Ponto::Ponto(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
void Ponto::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
void Ponto::imprime() {
	cout << "(" << x << ", " << y << ")" << flush;
}

void Ponto::multiply(double x, double y, double z)
{
	this->x *= x;
	this->y *= y;
	this->z *= z;
}

void Ponto::sum(double x, double y, double z)
{
	this->x += x;
	this->y += y;
	this->z += z;
}

Ponto get_max(Ponto p1, Ponto p2)
{
	Ponto max;

	max.x = (p2.x > p1.x) ? p2.x : p1.x;
	max.y = (p2.y > p1.y) ? p2.y : p1.y;
	max.z = (p2.z > p1.x) ? p2.z : p1.z;
	return max;
}

Ponto get_min(Ponto p1, Ponto p2)
{
	Ponto min;

	min.x = (p2.x < p1.x) ? p2.x : p1.x;
	min.y = (p2.y < p1.y) ? p2.y : p1.y;
	min.z = (p2.z < p1.x) ? p2.z : p1.z;

	return min;
}

bool Ponto::operator==(const Ponto other) const
{
	return (x == other.x) && (y == other.y);
}

