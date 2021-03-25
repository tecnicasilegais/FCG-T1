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
    u_long tamanho_a = a.size();
    u_long tamanho_b = b.size();

    for (int i = 0; i < tamanho_a - 1; i++)
    {
        for (int j = 0; j < tamanho_b - 1; j++)
        {
            Ponto ponto_intersecao(0, 0);
            bool ha_intersecao = intersec2d(a.get_vertice(i), a.get_vertice(i + 1),
                                            b.get_vertice(j), b.get_vertice(j + 1),
                                            ponto_intersecao);
            if (ha_intersecao)
            {
                a.insere_vertice(i + 1, ponto_intersecao);
                b.insere_vertice(j + 1, ponto_intersecao);
                tamanho_a++;
                tamanho_b++;
                i++;
                j++;
            }
        }
    }
}

Poligono uniao(Poligono a, Poligono b)
{
    Ponto limite(0, 0);
    Poligono uniao;
    u_long tamanho_a = a.size();
    for (int i = 0; i < tamanho_a - 1; i++)
    {
        Ponto ponto_medio((a.get_vertice(i).x + a.get_vertice(i + 1).x) / 2,
                          (a.get_vertice(i).y + a.get_vertice(i + 1).y) / 2);

        if (!ponto_dentro(ponto_medio, b, limite))
        {
            uniao.insere_vertice(a.get_vertice(i));
            uniao.insere_vertice(a.get_vertice(i + 1));
        }
    }
    u_long tamanho_b = b.size();
    for (int i = 0; i < tamanho_b - 1; i++)
    {
        Ponto ponto_medio((b.get_vertice(i).x + b.get_vertice(i + 1).x) / 2,
                          (b.get_vertice(i).y + b.get_vertice(i + 1).y) / 2);

        if (!ponto_dentro(ponto_medio, a, limite))
        {
            uniao.insere_vertice(b.get_vertice(i));
            uniao.insere_vertice(b.get_vertice(i + 1));
        }
    }
    return uniao;
}

Poligono intersecao(Poligono a, Poligono b)
{
    Ponto limite(0, 0);
    Poligono intersecao;
    u_long tamanho_a = a.size();
    for (int i = 0; i < tamanho_a - 1; i++)
    {
        Ponto ponto_medio((a.get_vertice(i).x + a.get_vertice(i + 1).x) / 2,
                          (a.get_vertice(i).y + a.get_vertice(i + 1).y) / 2);

        if (ponto_dentro(ponto_medio, b, limite))
        {
            intersecao.insere_vertice(a.get_vertice(i));
            intersecao.insere_vertice(a.get_vertice(i + 1));
        }
    }
    u_long tamanho_b = b.size();
    for (int i = 0; i < tamanho_b - 1; i++)
    {
        Ponto ponto_medio((b.get_vertice(i).x + b.get_vertice(i + 1).x) / 2,
                          (b.get_vertice(i).y + b.get_vertice(i + 1).y) / 2);

        if (ponto_dentro(ponto_medio, a, limite))
        {
            intersecao.insere_vertice(b.get_vertice(i));
            intersecao.insere_vertice(b.get_vertice(i + 1));
        }
    }
    return intersecao;
}

Poligono diferenca(Poligono a, Poligono b)
{
    Poligono p; //TODO: actual code required
    return p;
}

/**
 * Classifica se o meio da aresta esta dentro ou fora do poligono
 * @param ponto_medio - centro da aresta
 * @param poligono - poligono a ser testado
 * @param min - limites inferiores da tela
 * @returns true quando estiver dentro, false quando estiver fora do poligono
 */
bool ponto_dentro(Ponto &ponto_medio, Poligono &poligono, Ponto &min)
{
    auto num_intersec = 0;
    Ponto dummy(0, 0); //nao serao necessarias as coordenadas da intersecao
    Ponto line(min.x, ponto_medio.y);
    for (auto j = 0; j < poligono.size() - 1; j++)
    {
        if (intersec2d(ponto_medio, line, poligono.get_vertice(j), poligono.get_vertice(j + 1), dummy))
        {
            if (j < poligono.size() - 2)
            {
                if (!testa_mid_intersec(line, poligono, j, j + 1, j + 2))
                {
                    num_intersec++;
                }
            }
            else
            {
                if (!testa_mid_intersec(line, poligono, j, j + 1, 0))
                {
                    num_intersec++;
                }
            }
        }
    }
    if (intersec2d(ponto_medio, line, poligono.get_vertice(poligono.size() - 1), poligono.get_vertice(0), dummy))
    {
        if (!testa_mid_intersec(line, poligono, poligono.size() - 1, 0, 1))
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

bool testa_mid_intersec(Ponto &line, Poligono &pol, int i, int j, int k)
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
