//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Poligono.h"
#include "Ponto.h"

Poligono::Poligono()
= default;

void Poligono::insere_vertice(int index, Ponto p)
{
    if (p.x < min.x)
    {
        min.x = p.x;
    }
    if (p.x > max.x)
    {
        max.x = p.x;
    }
    if (p.y < min.y)
    {
        min.y = p.y;
    }
    if (p.y > max.y)
    {
        max.y = p.y;
    }

    Vertices.insert(Vertices.begin() + index, p);
}

void Poligono::insere_vertice(Ponto p)
{
    if (p.x < min.x)
    {
        min.x = p.x;
    }
    if (p.x > max.x)
    {
        max.x = p.x;
    }
    if (p.y < min.y)
    {
        min.y = p.y;
    }
    if (p.y > max.y)
    {
        max.y = p.y;
    }

    Vertices.push_back(p);
}

Ponto Poligono::get_vertice(int i)
{
    return Vertices[i];
}

void Poligono::desenha_poligono()
{
    glBegin(GL_LINE_LOOP);
    for (auto &Vertice : Vertices)
    {
        glVertex3f(Vertice.x, Vertice.y, Vertice.z);
    }
    glEnd();
}

void Poligono::desenha_vertices()
{
    glBegin(GL_POINTS);
    for (auto &vertice : Vertices)
    {
        glVertex3f(vertice.x, vertice.y, vertice.z);
    }
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
    for (auto &vertice : Vertices)
    {
        vertice.imprime();
    }
}

unsigned long Poligono::size()
{
    return Vertices.size();
}

void Poligono::initialize(Ponto initial)
{
    min = initial;
    max = initial;
    Vertices.push_back(initial);
}

Ponto Poligono::get_min()
{
    return min;
}

Ponto Poligono::get_max()
{
    return max;
}

void encontrar_intersecoes(Poligono &a, Poligono &b)
{
    u_long tamanhoA = a.size();
    u_long tamanhoB = b.size();

    for (int i = 0; i < tamanhoA - 1; i++)
    {
        for (int j = 0; j < tamanhoB - 1; j++)
        {
            Ponto pontoIntersecao = Ponto(0, 0);
            bool haIntersecao = intersec2d(a.get_vertice(i), a.get_vertice(i + 1),
                                           b.get_vertice(j), b.get_vertice(j + 1),
                                           pontoIntersecao);
            if (haIntersecao)
            {
                a.insere_vertice(i+1, Ponto(pontoIntersecao.x, pontoIntersecao.y, 0));//TODO: mudar para inserir no indice
                b.insere_vertice(j+1, Ponto(pontoIntersecao.x, pontoIntersecao.y, 0));//TODO
                tamanhoA++;
                tamanhoB++;
                i++;
                j++;
            }
        }
    }
}

Poligono uniao(Poligono a, Poligono b)
{

    Poligono p; //TODO: actual code required
    return p;
}

Poligono intersecao(Poligono a, Poligono b)
{
    Poligono p; //TODO: actual code required
    return p;
}

Poligono diferenca(Poligono a, Poligono b)
{
    Poligono p; //TODO: actual code required
    return p;
}