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
void Ponto::imprime()
{
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

/* ********************************************************************** */
/*                                                                        */
/*  Calcula a intersecao entre 2 retas (no plano "XY" Z = 0)              */
/*                                                                        */
/* k : ponto inicial da reta 1                                            */
/* l : ponto final da reta 1                                              */
/* m : ponto inicial da reta 2                                            */
/* n : ponto final da reta 2                                              */
/*                                                                        */
/* s: valor do parametro no ponto de intersecao (sobre a reta KL)         */
/* t: valor do parametro no ponto de intersecao (sobre a reta MN)         */
/*                                                                        */
/* ********************************************************************** */
int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t)
{
	double det;

	det = (n.x - m.x) * (l.y - k.y) - (n.y - m.y) * (l.x - k.x);

	if (det == 0.0)
		return 0; //nao ha intersecao

	s = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x)) / det;
	t = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x)) / det;

	return 1; //ha intersecao
}

bool ha_interseccao(Ponto k, Ponto l, Ponto m, Ponto n)
{
	int ret;
	double s, t;
	ret = intersec2d(k, l, m, n, s, t);
	if (!ret) return false;
	if (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0)
		return true;
	else return false;
}
