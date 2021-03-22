//
//  Ponto.h
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef Ponto_hpp
#define Ponto_hpp

#include <iostream>
using namespace std;

class Ponto
{

public:
	float x, y, z;
	Ponto();
	Ponto(float x, float y, float z = 0);
	void set(float x, float y, float z = 0);
	void imprime();
	bool operator==(const Ponto other) const;
	void multiply(double x, double y, double z);
	void sum(double x, double y, double z);
};

Ponto get_min(Ponto p1, Ponto p2);
Ponto get_max(Ponto p1, Ponto p2);
int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t);
bool ha_interseccao(Ponto k, Ponto l, Ponto m, Ponto n);

#endif /* Ponto_hpp */
