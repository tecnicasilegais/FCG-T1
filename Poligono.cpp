//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Poligono.h"

Poligono::Poligono()
= default;

void Poligono::insere_vertice(Ponto p)
{
	if (p.x < left.x)
        left = p;
    if (p.x > right.x)
        right = p;
    if (p.y < bottom.y)
        bottom = p;
    if (p.y > top.y)
        top = p;
	
    Vertices.push_back(p);
}

Ponto Poligono::get_vertice(int i)
{
    return Vertices[i];
}
void Poligono::desenha_poligono()
{
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}
void Poligono::desenha_vertices()
{
    glBegin(GL_POINTS);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}
void Poligono::desenha_vertice(int r, int g, int b, int pos)
{
    glColor3f(r, g, b); // R, G, B  [0..1]
    glBegin(GL_POINTS);
    glVertex3f(Vertices[pos].x, Vertices[pos].y, Vertices[pos].z);
    glEnd();
}
void Poligono::imprime()
{
    for (int i=0; i<Vertices.size(); i++)
        Vertices[i].imprime();
}
unsigned long Poligono::size()
{
    return Vertices.size();
}
void Poligono::initialize(Ponto initial)
{
    left = initial;
    right = initial;
    top = initial;
    bottom = initial;
    Vertices.push_back(initial);
}
Ponto Poligono::get_left()
{
    return left;
}
Ponto Poligono::get_right()
{
    return right;
}
Ponto Poligono::get_top()
{
    return top;
}
Ponto Poligono::get_bottom()
{
    return bottom;
}