// **********************************************************************
// PUCRS/Escola PolitŽcnica
// COMPUTA‚ÌO GRçFICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>


using namespace std;

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include "Poligono.h"

#include "Temporizador.h"
Temporizador T;
double AccumDeltaT = 0;

Poligono A, B, Uniao, Intersecao, Diferenca;

// Limites l—gicos da ‡rea de desenho
Ponto Min, Max;
Ponto Meio, Terco, Largura;

bool desenha = false;

float angulo = 0.0;

// **********************************************************************
//    Calcula o produto escalar entre os vetores V1 e V2
// **********************************************************************
double ProdEscalar(Ponto v1, Ponto v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
// **********************************************************************
//    Calcula o produto vetorial entre os vetores V1 e V2
// **********************************************************************
void ProdVetorial(Ponto v1, Ponto v2, Ponto& vresult)
{
	vresult.x = v1.y * v2.z - (v1.z * v2.y);
	vresult.y = v1.z * v2.x - (v1.x * v2.z);
	vresult.z = v1.x * v2.y - (v1.y * v2.x);
}
/* ********************************************************************** */
/*                                                                        */
/*  Calcula a interseccao entre 2 retas (no plano "XY" Z = 0)             */
/*                                                                        */
/* k : ponto inicial da reta 1                                            */
/* l : ponto final da reta 1                                              */
/* m : ponto inicial da reta 2                                            */
/* n : ponto final da reta 2                                              */
/*                                                                        */
/* s: valor do par‰metro no ponto de interse‹o (sobre a reta KL)         */
/* t: valor do par‰metro no ponto de interse‹o (sobre a reta MN)         */
/*                                                                        */
/* ********************************************************************** */
int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t)
{
	double det;

	det = (n.x - m.x) * (l.y - k.y) - (n.y - m.y) * (l.x - k.x);

	if (det == 0.0)
		return 0; // n‹o h‡ intersec‹o

	s = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x)) / det;
	t = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x)) / det;

	return 1; // h‡ intersec‹o
}

// **********************************************************************
bool HaInterseccao(Ponto k, Ponto l, Ponto m, Ponto n)
{
	int ret;
	double s, t;
	ret = intersec2d(k, l, m, n, s, t);
	if (!ret) return false;
	if (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0)
		return true;
	else return false;
}
// **********************************************************************
//
// **********************************************************************
void LePoligono(const char* nome, Poligono& P)
{
	ifstream input;
	input.open(nome, ios::in);
	if (!input)
	{
		cout << "Erro ao abrir " << nome << ". " << endl;
		exit(0);
	}
	cout << "Lendo arquivo " << nome << "...";
	string S;
	int nLinha = 0;
	unsigned int qtdVertices;

	input >> qtdVertices;

	for (int i = 0; i < qtdVertices; i++)
	{
		double x, y;
		// Le cada elemento da linha
		input >> x >> y;
		if (!input)
			break;
		nLinha++;
		P.insere_vertice(Ponto(x, y));
	}
	cout << "Poligono lido com sucesso!" << endl;

}

// **********************************************************************
//
// **********************************************************************
void init()
{

	// Define a cor do fundo da tela (AZUL)
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Le o primeiro pol’gono
	LePoligono("Retangulo.txt", A);

	cout << "\tMinimo:"; A.get_min().imprime();
	cout << "\tMaximo:"; A.get_max().imprime();

	// Le o segundo pol’gono
	LePoligono("Triangulo.txt", B);

	cout << "\tMinimo:"; B.get_min().imprime();
	cout << "\tMaximo:"; B.get_max().imprime();

	// Atualiza os limites globais ap—s cada leitura
	Min = get_min(A.get_min(), B.get_min());
	Max = get_max(A.get_max(), B.get_max());

	cout << "Limites Globais" << endl;
	cout << "\tMinimo:"; Min.imprime();
	cout << "\tMaximo:"; Max.imprime();
	cout << endl;

	// Ajusta a largura da janela l—gica
	// em fun‹o do tamanho dos pol’gonos
	Largura.x = Max.x - Min.x;
	Largura.y = Max.y - Min.y;

	// Calcula 1/3 da largura da janela
	Terco = Largura;
	double factor = 1.0 / 3.0;
	Terco.multiply(factor, factor, factor);

	// Calcula 1/2 da largura da janela
	Meio.x = (Max.x + Min.x) / 2;
	Meio.y = (Max.y + Min.y) / 2;
	Meio.z = (Max.z + Min.z) / 2;

}

double nFrames = 0;
double TempoTotal = 0;
// **********************************************************************
//
// **********************************************************************
void animate()
{
	double dt;
	dt = T.getDeltaT();
	AccumDeltaT += dt;
	TempoTotal += dt;
	nFrames++;

	if (AccumDeltaT > 1.0 / 30) // fixa a atualiza‹o da tela em 30
	{
		AccumDeltaT = 0;
		//angulo+=0.05;
		glutPostRedisplay();
	}
	if (TempoTotal > 5.0)
	{
		cout << "Tempo Acumulado: " << TempoTotal << " segundos. ";
		cout << "Nros de Frames sem desenho: " << nFrames << endl;
		cout << "FPS(sem desenho): " << nFrames / TempoTotal << endl;
		TempoTotal = 0;
		nFrames = 0;
	}
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape(int w, int h)
{
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Define a area a ser ocupada pela area OpenGL dentro da Janela
	glViewport(0, 0, w, h);
	// Define os limites logicos da area OpenGL dentro da Janela
	glOrtho(Min.x, Max.x,
		Min.y, Max.y,
		0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// **********************************************************************
//
// **********************************************************************
void DesenhaEixos()
{
	glBegin(GL_LINES);
	//  eixo horizontal
	glVertex2f(Min.x, Meio.y);
	glVertex2f(Max.x, Meio.y);
	//  eixo vertical 1
	glVertex2f(Min.x + Terco.x, Min.y);
	glVertex2f(Min.x + Terco.x, Max.y);
	//  eixo vertical 2
	glVertex2f(Min.x + 2 * Terco.x, Min.y);
	glVertex2f(Min.x + 2 * Terco.x, Max.y);
	glEnd();
}
// **********************************************************************
//  void display( void )
//
// **********************************************************************
void display(void)
{

	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	// Define os limites lógicos da área OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenham os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	glLineWidth(1);
	glColor3f(1, 1, 1); // R, G, B  [0..1]
	DesenhaEixos();

	//Desenha os dois pol’gonos no canto superior esquerdo
	glPushMatrix();
	glTranslatef(0, Meio.y, 0);
	glScalef(0.33, 0.5, 1);
	glLineWidth(2);
	glColor3f(1, 1, 0); // R, G, B  [0..1]
	A.desenha_poligono();
	glColor3f(1, 0, 0); // R, G, B  [0..1]
	B.desenha_poligono();
	glPopMatrix();

	// Desenha o pol’gono A no meio, acima
	glPushMatrix();
	glTranslatef(Terco.x, Meio.y, 0);
	glScalef(0.33, 0.5, 1);
	glLineWidth(2);
	glColor3f(1, 1, 0); // R, G, B  [0..1]
	A.desenha_poligono();
	glPopMatrix();

	// Desenha o pol’gono B no canto superior direito
	glPushMatrix();
	glTranslatef(Terco.x * 2, Meio.y, 0);
	glScalef(0.33, 0.5, 1);
	glLineWidth(2);
	glColor3f(1, 0, 0); // R, G, B  [0..1]
	B.desenha_poligono();
	glPopMatrix();

	// Desenha o pol’gono A no canto inferior esquerdo
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(0.33, 0.5, 1);
	glLineWidth(2);
	glColor3f(1, 1, 0); // R, G, B  [0..1]
	A.desenha_poligono();
	glPopMatrix();

	// Desenha o pol’gono B no meio, abaixo
	glPushMatrix();
	glTranslatef(Terco.x, 0, 0);
	glScalef(0.33, 0.5, 1);
	glLineWidth(2);
	glColor3f(1, 0, 0); // R, G, B  [0..1]
	B.desenha_poligono();
	glPopMatrix();

	glutSwapBuffers();
}
// **********************************************************************
// ContaTempo(double tempo)
//      conta um certo nœmero de segundos e informa quanto frames
// se passaram neste per’odo.
// **********************************************************************
void ContaTempo(double tempo)
{
	Temporizador T;

	unsigned long cont = 0;
	cout << "Inicio contagem de " << tempo << "segundos ..." << flush;
	while (true)
	{
		tempo -= T.getDeltaT();
		cont++;
		if (tempo <= 0.0)
		{
			cout << "fim! - Passaram-se " << cont << " frames." << endl;
			break;
		}
	}

}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
// **********************************************************************

void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:        // Termina o programa qdo
		exit(0);   // a tecla ESC for pressionada
		break;
	case 't':
		ContaTempo(3);
		break;
	case ' ':
		desenha = !desenha;
		break;
	default:
		break;
	}
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys(int a_keys, int x, int y)
{
	switch (a_keys)
	{
	case GLUT_KEY_UP:       // Se pressionar UP
		glutFullScreen(); // Vai para Full Screen
		break;
	case GLUT_KEY_DOWN:     // Se pressionar UP
							// Reposiciona a janela
		glutPositionWindow(50, 50);
		glutReshapeWindow(700, 500);
		break;
	default:
		break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
// **********************************************************************
int  main(int argc, char** argv)
{
	cout << "Programa OpenGL" << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(0, 0);

	// Define o tamanho inicial da janela grafica do programa
	glutInitWindowSize(1000, 500);

	// Cria a janela na tela, definindo o nome da
	// que aparecera na barra de titulo da janela.
	glutCreateWindow("Primeiro Programa em OpenGL");

	// executa algumas inicializações
	init();

	// Define que o tratador de evento para
	// o redesenho da tela. A funcao "display"
	// será chamada automaticamente quando
	// for necessário redesenhar a janela
	glutDisplayFunc(display);

	// Define que o tratador de evento para
	// o invalida‹o da tela. A funcao "display"
	// será chamada automaticamente sempre que a
	// m‡quina estiver ociosa (idle)
	glutIdleFunc(animate);

	// Define que o tratador de evento para
	// o redimensionamento da janela. A funcao "reshape"
	// será chamada automaticamente quando
	// o usuário alterar o tamanho da janela
	glutReshapeFunc(reshape);

	// Define que o tratador de evento para
	// as teclas. A funcao "keyboard"
	// será chamada automaticamente sempre
	// o usuário pressionar uma tecla comum
	glutKeyboardFunc(keyboard);

	// Define que o tratador de evento para
	// as teclas especiais(F1, F2,... ALT-A,
	// ALT-B, Teclas de Seta, ...).
	// A funcao "arrow_keys" será chamada
	// automaticamente sempre o usuário
	// pressionar uma tecla especial
	glutSpecialFunc(arrow_keys);

	// inicia o tratamento dos eventos
	glutMainLoop();

	return 0;
}
