//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Poligono.h"
#include "Ponto.h"

#include <chrono>
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

/// <summary>
/// Classifica se o meio da aresta esta dentro ou fora do poligono
/// </summary>
/// <param name="pol">poligono a ser testado</param>
/// <param name="ponto_medio"> centro da aresta </param>
/// <param name="min"> limites inferiores da tela</param>
/// <returns>true quando estiver dentro, false quando estiver fora do poligono</returns>
bool classifica_aresta(Poligono& pol, Ponto& ponto_medio, Ponto& min)
{
    auto num_intersec = 0;
    Ponto dummy(0, 0); //nao serao necessarias as coordenadas da intersecao
    Ponto line(min.x, ponto_medio.y);
    for (auto j = 0; j < pol.size() - 1; j++)
    {
        if (intersec2d(ponto_medio, line, pol.get_vertice(j), pol.get_vertice(j + 1), dummy))
        {
            if (j < pol.size() - 2)
            {
                if (!testa_mid_intersec(line, pol, j, j + 1, j + 2))
                {
                    num_intersec++;
                }
            }
            else
            {
                if (!testa_mid_intersec(line, pol, j, j + 1, 0))
                {
                    num_intersec++;
                }
            }
        }
    }
    if (intersec2d(ponto_medio, line, pol.get_vertice(pol.size() - 1), pol.get_vertice(0),dummy))
    {
        if (!testa_mid_intersec(line, pol, pol.size() - 1, 0, 1))
        {
            num_intersec++;
        }
    }
    if (num_intersec % 2 == 0)
    {
        return false;
    }
    return true;
}


bool testa_mid_intersec(Ponto& line, Poligono& pol, int i, int j, int k)
{
    if (line.y == pol.get_vertice(j).y)
    {
        if ((pol.get_vertice(i).y < pol.get_vertice(j).y &&
            pol.get_vertice(j).y < pol.get_vertice(k).y) || (
                pol.get_vertice(i).y > pol.get_vertice(j).y &&
                pol.get_vertice(j).y > pol.get_vertice(k).y))
        {
            return true;
        }
    }
    return false;
}
