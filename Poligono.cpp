//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Poligono.h"
#include "Ponto.h"

#include<bits/stdc++.h>
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

int Poligono::index(Ponto p)
{
    auto it = std::find(Vertices.begin(), Vertices.end(), p);

	if (it != Vertices.end())
	{
        return it - Vertices.begin();
	}
	return -1;
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
        Ponto ponto_intersecao(0,0);
        bool ha_intersecao = intersec2d(a.get_vertice(i), a.get_vertice(i + 1),
                                        b.get_vertice(tamanho_b-1), b.get_vertice(0),
                                        ponto_intersecao);
        if (ha_intersecao)
        {
            a.insere_vertice(i + 1, ponto_intersecao);
            b.insere_vertice(0, ponto_intersecao);
            tamanho_a++;
            tamanho_b++;
            i++;
        }
    }
    for (int j = 0; j < tamanho_b - 1; j++)
    {
        Ponto ponto_intersecao(0, 0);
        bool ha_intersecao = intersec2d(a.get_vertice(tamanho_a-1), a.get_vertice(0),
                                        b.get_vertice(j), b.get_vertice(j + 1),
                                        ponto_intersecao);
        if (ha_intersecao)
        {
            a.insere_vertice(0, ponto_intersecao);
            b.insere_vertice(j + 1, ponto_intersecao);
            tamanho_a++;
            tamanho_b++;
            j++;
        }
    }
    Ponto ponto_intersecao(0,0);
    bool ha_intersecao = intersec2d(a.get_vertice(tamanho_a-1), a.get_vertice(0),
                                    b.get_vertice(tamanho_b-1), b.get_vertice(0),
                                    ponto_intersecao);
    if (ha_intersecao)
    {
        a.insere_vertice(0, ponto_intersecao);
        b.insere_vertice(0, ponto_intersecao);
        tamanho_a++;
        tamanho_b++;
    }
}

void insere_unico(Poligono &pol, Ponto p)
{
    if (pol.index(p) != -1)
    {
        return;
    }
    pol.insere_vertice(p);
}

Poligono uniao(Poligono &a, Poligono &b, Ponto &min)
{
    Poligono uniao;
    u_long tamanho_a = a.size();
    for (int i = 0; i < tamanho_a - 1; i++)
    {
        Ponto ponto_medio((a.get_vertice(i).x + a.get_vertice(i + 1).x) / 2,
                          (a.get_vertice(i).y + a.get_vertice(i + 1).y) / 2);

        if (!ponto_dentro(ponto_medio, b, min))
        {
            uniao.insere_vertice(a.get_vertice(i));
            uniao.insere_vertice(a.get_vertice(i + 1));
        }
    }
    u_long tamanho_b = b.size();
    for (int i = 0; i < tamanho_b - 1; i++)
    {
        Ponto bi = b.get_vertice(i);
        Ponto bii = b.get_vertice(i + 1);
        Ponto ponto_medio((bi.x + bii.x) / 2,
                          (bi.y + bii.y) / 2);

        if (!ponto_dentro(ponto_medio, a, min))
        {
            auto index_bii = uniao.index(bii);
            auto index_bi = uniao.index(bi);
            if (index_bii != -1 && index_bi != -1)
            {
                continue; //a aresta esta toda la?
            }
            if (index_bii != -1)
            {
                uniao.insere_vertice(index_bii, bi);
            }
            else if (index_bi != -1)
            {
                uniao.insere_vertice(index_bi + 1, bii);
            }
            else
            {
                uniao.insere_vertice(bi);
                uniao.insere_vertice(bii);
            }
        }
    }
    return uniao;
}

Poligono intersecao(Poligono &a, Poligono &b, Ponto &min)
{
    Poligono intersecao;
	
    u_long tamanho_b = b.size();
    for (int i = 0; i < tamanho_b - 1; i++)
    {
        Ponto ponto_medio((b.get_vertice(i).x + b.get_vertice(i + 1).x) / 2,
            (b.get_vertice(i).y + b.get_vertice(i + 1).y) / 2);

        if (ponto_dentro(ponto_medio, a, min))
        {
            intersecao.insere_vertice(b.get_vertice(i));
            intersecao.insere_vertice(b.get_vertice(i + 1));
        }
    }
    u_long tamanho_a = a.size();
	
    for (int i = 0; i < tamanho_a - 1; i++)
    {
        Ponto ai = a.get_vertice(i);
        Ponto aii = a.get_vertice(i + 1);
        Ponto ponto_medio((ai.x + aii.x) / 2,
										(ai.y + aii.y) / 2);

        if (ponto_dentro(ponto_medio, b, min))
        {
            auto index_aii = intersecao.index(aii);
            auto index_ai = intersecao.index(ai);
        	if(index_aii != -1 && index_ai != -1)
        	{
                continue; //a aresta esta toda la?
        	}
        	if( index_aii != -1)
        	{
                intersecao.insere_vertice(index_aii, ai);
        	}
            else if(index_ai != -1)
            {
                intersecao.insere_vertice(index_ai + 1, aii);
            }
            else
            {
                intersecao.insere_vertice(ai);
                intersecao.insere_vertice(aii);
            }
        }
    }
    return intersecao;
}

Poligono diferenca(Poligono &a, Poligono &b, Ponto &min)
{
    Poligono diferenca;  //a - b

    u_long tamanho_a = a.size();
    u_long tamanho_b = b.size();

    for (int i=0; i < tamanho_a -1; i++)
    {
        Ponto a_i = a.get_vertice(i);
        Ponto a_ii = a.get_vertice(i + 1);

        Ponto p_medio((a_i.x + a_ii.x) / 2, (a_i.y + a_ii.y)/2);

    	if(!ponto_dentro(p_medio, b, min))
    	{
	        insere_unico(diferenca, a_i);
	        insere_unico(diferenca, a_ii);
        }
    	else
        {
	        //pontos dentro de B que nao forem de intersecao nao devem ser incluidos
	        if(b.index(a_i) != -1) //poligono B tambem contem o ponto a(i), eh ponto de intersecao
	        {
		        insere_unico(diferenca, a_i);
	        }
	        if(b.index(a_ii) != -1) // poligono B tambem contem o ponto a(i+1), eh ponto intersec
	        {
		        insere_unico(diferenca, a_ii);
	        }
        }
    }

    for (int i = 0; i < tamanho_b - 1; i++)
    {
        Ponto b_i = b.get_vertice(i);
        Ponto b_ii = b.get_vertice(i + 1);
        Ponto p_medio((b_i.x + b_ii.x) / 2,
								(b_i.y + b_ii.y) / 2);

        if (ponto_dentro(p_medio, a, min))
        {
            auto index_bi = diferenca.index(b_i);
            auto index_bii = diferenca.index(b_ii);
            if (index_bii != -1 && index_bi != -1)
            {
                continue; //a aresta esta toda la?
            }
        	//logica inversa aa da intersecao
            if (index_bii != -1)
            {
                diferenca.insere_vertice(index_bii + 1, b_i);
            }
            else if (index_bi != -1)
            {
                diferenca.insere_vertice(index_bi, b_ii);
            }
            else
            {
                diferenca.insere_vertice(b_i);
                diferenca.insere_vertice(b_ii);
            }
        }
    }
    return diferenca;
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
