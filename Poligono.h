//
//  Poligono.hpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef Poligono_hpp
#define Poligono_hpp

#include <iostream>

using namespace std;

#ifdef WIN32

#include <windows.h>
#include <GL/glut.h>

#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Ponto.h"
#include <vector>

class Poligono
{
    vector<Ponto> Vertices;
    Ponto min, max;
public:
    int menorPosicao{};
    Poligono();
    unsigned long size();
    int index(Ponto p);
    void desenha_poligono();
    void desenha_vertice(int r, int g, int b, int pos);
    void desenha_vertices();
    void imprime();
    void initialize(Ponto initial);
    void insere_vertice(Ponto);
    void insere_vertice(int index, Ponto p);
    Ponto get_min();
    Ponto get_max();
    Ponto get_vertice(int);
};

void encontrar_intersecoes(Poligono &a, Poligono &b);
void insere_unico(Ponto);
Poligono diferenca(Poligono &a, Poligono &b, Ponto &min);
Poligono intersecao(Poligono &a, Poligono &b, Ponto &min);
Poligono uniao(Poligono &a, Poligono &b, Ponto &min);
bool ponto_dentro(Ponto &ponto_medio, Poligono &poligono, Ponto &min);
bool testa_mid_intersec(Ponto &line, Poligono &mapa, int i, int j, int k);

#endif 
