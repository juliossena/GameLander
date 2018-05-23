#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <string>
//#include <stdio.h>
#include <math.h>
#include <iostream>
#include "functions/escreveTexto.h"
#include "functions/functions.h"
#include "models/Rgb.h"
#include "models/Triangle.h"
#include "models/Position.h"
#include "drawings/drawRocket.h"
//#include <iostream>
using namespace std;
#include <time.h>


Rgb *yellow = new Rgb(1.0, 1.0, 0);
Rgb *blue = new Rgb(0, 0, 1.0);
Rgb *white = new Rgb(1.0, 1.0, 1.0);
Rgb *red = new Rgb (0.6, 0, 0);
Rgb *grey = new Rgb (0.3, 0.3, 0.3);

clock_t tInicio, tFim, tDecorrido;

GLfloat gravidade = 1.01;
GLfloat velocidade = 0;
GLfloat aceleracao = 0;
GLfloat orientacaoEmGraus = 90;
GLfloat velocidadeAngular = 0;
GLfloat x = 0, y = 0;
Triangle *montanhas[150];

bool possuiBonusVida = false;
bool possuiBonusCombustivel = false;
Position *positionBonus;
int vidas;
int combustivel = 0;
int qtdMontanhas = 0;
float pontuacao = 0;
bool acelerando = false;
bool girandoEsquerda = false;
bool girandoDireita = false;
bool fimDeJogo = false;
bool jogoPausado = false;
bool pedidoSair = false;
bool peditoReiniciar = false;
char mensagemFim[30];
const GLfloat velocidadeTangencial = 0.5;
int estaNoLocal();
void reiniciarJogo(float, int, int, bool);
void gerarMontanhas();
bool verificaSeNaoEstaNoPouso(int, int);
bool verificaSeBateuMontanha();
bool verificaSeEstaNoBonus();
bool isMenu = true;
int positionInitialLanding = 0;
int menuSelect = 0;

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)



void desenhaCena(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (isMenu) {
    	if (menuSelect == 0) {
    		escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "Comecar Jogo", new Position(-30, 0));
			escreverTexto(*grey, GLUT_BITMAP_HELVETICA_18, "Sair", new Position(-20, -10));
    	} else if (menuSelect == 1) {
    		escreverTexto(*grey, GLUT_BITMAP_HELVETICA_18, "Comecar Jogo", new Position(-30, 0));
			escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "Sair", new Position(-20, -10));
    	}

    } else {
    	escreveHUD(*white, *red, velocidade, orientacaoEmGraus, y, combustivel, pontuacao, vidas);

    	//Desenha bonus
    	if (possuiBonusVida) {
    		escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "V", positionBonus);
    	} else if (possuiBonusCombustivel) {
    		escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "C", positionBonus);
    	}

		//Desenha chão e base de pouso
		drawSquare(*white, new Square(new Position(-100, -100), 200, 10));
		drawSquare(*blue, new Square(new Position(positionInitialLanding, -100), 10, 10));

		//desenhar montanhas
		for (int i = 0 ; i < qtdMontanhas ; i++) {
			drawTriangle(*white, montanhas[i]);
		}

		glPushMatrix();
			// Move o sistema de coordenadas para a posição onde deseja-se desenhar
			glTranslatef(x, y, 0);
			glRotatef(orientacaoEmGraus, 0, 0, 1);

			// Desenha a nave
			drawTriangle(*yellow, new Triangle(new Position(-6, -3), 6, 20, 2));
			if (acelerando) {
				//Quando acelera desenha o fogo central
				drawTriangle(*red, new Triangle(new Position(-6, 2), 4, 6, 4));
				acelerando = false;
			}
			if (girandoEsquerda) {
				//Quando vira a esquerda acende o fogo lateral direito
				drawTriangle(*red, new Triangle(new Position(-6, -1), 2, 4, 4));
				girandoEsquerda = false;
			}
			if (girandoDireita) {
				//Quando vira a direita acende o fogo lateral esquerdo
				drawTriangle(*red, new Triangle(new Position(-6, 3), 2, 4, 4));
				girandoDireita = false;
			}

		glPopMatrix();


		if (fimDeJogo) {
			escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "Fim de Jogo", new Position(0, 0));
			escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, mensagemFim, new Position(0, -10));
		} else if (jogoPausado) {
			//Se o jogo estiver pausado vai escrever na tela
			if (peditoReiniciar) {
				escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "Deseja reiniciar o jogo?", new Position(0, 0));
				escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "(S) Sim / (N) Nao", new Position(0, -10));
			} else if (pedidoSair) {
				escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "Deseja fechar o jogo?", new Position(0, 0));
				escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "(S) Sim / (N) Nao", new Position(0, -10));
			} else {
				escreverTexto(*white, GLUT_BITMAP_HELVETICA_18, "Jogo Pausado", new Position(0, 0));
			}
		}
    }



    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}



// Inicia algumas variáveis de estado
void inicializa(void) {
    // cor para limpar a tela
    glClearColor(0, 0, 0, 0);

}

// Callback de redimensionamento
void redimensiona(int w, int h) {
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100, 100, -100, 100, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void atualiza(int idx) {
	if (!jogoPausado && !fimDeJogo) {
		if (y > -83 && !verificaSeBateuMontanha()) {
			if (possuiBonusCombustivel) {
				if (verificaSeEstaNoBonus()) {
					possuiBonusCombustivel = false;
					combustivel += 400;
				}
			} else if (possuiBonusVida) {
				if (verificaSeEstaNoBonus()) {
					possuiBonusVida = false;
					vidas ++;
				}
			}
			velocidade -= 0.01;

			if (velocidade > 0) {
				x += cos(grausParaRadianos(orientacaoEmGraus)) * velocidade;
				y += sin(grausParaRadianos(orientacaoEmGraus)) * velocidade;
			}
			if (aceleracao == 0) {
				y += velocidade;
			} else {
				velocidade += aceleracao;
				if (velocidade > 0) {
					x += cos(grausParaRadianos(orientacaoEmGraus)) * velocidade;
				} else {
					x += cos(grausParaRadianos(orientacaoEmGraus)) * -velocidade;
				}

				aceleracao = 0;
			}

		} else {
			fimDeJogo = true;
			if (velocidade < -0.9 || orientacaoEmGraus != 90 || !estaNoLocal() || verificaSeBateuMontanha()) {
				if (vidas == 0) {
					strcpy (mensagemFim, "Perdeu - Deseja começar novamente? S / N");
				} else {
					vidas --;
					fimDeJogo = false;
					reiniciarJogo(pontuacao, 500, vidas, false);
				}

			} else {
				tFim = clock();
				tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000)) / 1000;
				pontuacao += 100 - tDecorrido;
				reiniciarJogo(pontuacao, combustivel + 400, vidas, true);
				fimDeJogo = false;
			}

		}
	}


	glutPostRedisplay();
	glutTimerFunc(17, atualiza, 0);
}

void pausarJogo() {
	if (!jogoPausado) {
		jogoPausado = true;
	} else {
		jogoPausado = false;
	}
}

int estaNoLocal() {
	if (x >= positionInitialLanding && x < positionInitialLanding + 10) {
		return 1;
	}
	return 0;
}

void tecladoEspecial(int key, int a, int b) {
	switch(key) {
		// Tecla para cima
		case 101:
			if (isMenu) {
				if (menuSelect == 0) {
					menuSelect ++;
				} else {
					menuSelect --;
				}
			} else {
				if (combustivel > 0) {
					acelerando = true;
					girandoEsquerda = true;
					girandoDireita = true;
					aceleracao = 0.1;
					combustivel -= 5;
				}
			}

			break;

		//Tecla para baixo
		case 103:
			if (isMenu) {
				if (menuSelect == 0) {
					menuSelect ++;
				} else {
					menuSelect --;
				}
			}

			break;

		// Tecla para direita
		case 100:
			if (orientacaoEmGraus < 160 && combustivel > 0) {
				girandoEsquerda = true;
				orientacaoEmGraus += 1.5;
				combustivel --;
			}
			break;

		// Teclas para esquerda
		case 102:
			if (orientacaoEmGraus > 15 && combustivel > 0) {
				girandoDireita = true;
				orientacaoEmGraus -= 1.5;
				combustivel --;
			}
			break;

		default:
			break;
	}
}

// Callback de evento de teclado
void teclado(unsigned char key, int a, int b) {
	switch(key) {
		//Reiniciar o jogo
		case 'R':
		case 'r':
			peditoReiniciar = true;
			jogoPausado = true;
			break;
		//Pausar o jogo
		case 'P':
		case 'p':
			pausarJogo();
			break;

		// Tecla Enter
		case 10:
		case 13:
			if (isMenu) {
				if (menuSelect == 0) {
					reiniciarJogo(0, 1000, 5, true);
					isMenu = false;
				} else if (menuSelect == 1) {
					exit(0);
				}
			}

			break;

		// Tecla ESC
		case 27:
			pedidoSair = true;
			jogoPausado = true;
			break;

		case 'S':
		case 's':
			if (pedidoSair) {
				exit(0);
			} else if (peditoReiniciar) {
				reiniciarJogo(0, 1000, 5, true);
				peditoReiniciar = false;
				jogoPausado = false;
			} else if (fimDeJogo) {
				reiniciarJogo(0, 1000, 5, true);
				fimDeJogo = false;
				jogoPausado = false;
			}
			break;
		case 'N':
		case 'n':
			if (pedidoSair) {
				pedidoSair = false;
				jogoPausado = false;
			} else if (peditoReiniciar) {
				peditoReiniciar = false;
				jogoPausado = false;
			} else if (fimDeJogo) {
				exit(0);
			}
			break;
		default:
			break;
	}
}

void reiniciarJogo(float pontos, int nCombustivel, int nVidas, bool newScenarium) {
	vidas = nVidas;
	pontuacao = pontos;
	tInicio = clock();


	velocidade = 0;
	aceleracao = 0;
	orientacaoEmGraus = 90;
	combustivel = nCombustivel;
	y = 100;
	if (newScenarium) {
		//Chance de aparecer combustivel
		possuiBonusCombustivel = gerarPossuirBonus(0.5);
		if (!possuiBonusCombustivel) {
			//Chance de aparecer Vida
			possuiBonusVida = gerarPossuirBonus(0.2);
		}
		positionBonus = new Position(numberRandon(-90, 90), numberRandon(10, 40));
		x = numberRandon(-100, 90);
		positionInitialLanding = numberRandon(-90, 90);
		qtdMontanhas = numberRandon(100, 120);
		gerarMontanhas();
	}

}

bool verificaSeEstaNoBonus() {
	if (x >= positionBonus->getX() && x <= positionBonus->getX() + 10 && y >= positionBonus->getY() && y <= positionBonus->getY() + 10) {
		return true;
	}
	return false;
}

bool verificaSeNaoEstaNoPouso(int start, int width) {
	if ((start < positionInitialLanding && start + width < positionInitialLanding)
		|| (start > positionInitialLanding + 10 && start + width > positionInitialLanding + 10) ) {
		return false;
	}
	return true;
}

bool verificaSeBateuMontanha() {
	for (int i = 0 ; i < qtdMontanhas ; i++) {
		if (x >= montanhas[i]->getPosition1() && x <= montanhas[i]->getPosition3()) {
			if (y <= montanhas[i]->getPosition6()) {
				return true;
			}
		}
	}
	return false;
}

void gerarMontanhas() {
	for (int i = 0 ; i < qtdMontanhas ; i++) {
		int start = numberRandon(-100, 90);
		int width = numberRandon(10, 30);
		int height = numberRandon(10, 30);
		while (verificaSeNaoEstaNoPouso(start, width)) {
			start = numberRandon(-100, 90);
			width = numberRandon(10, 20);
			height = numberRandon(10, 30);
		}
		montanhas[i] = new Triangle(new Position(start, -100), width, height, 1);
	}
}

// Rotina principal
int main(int argc, char **argv) {

	reiniciarJogo(0, 1000, 5, true);

    // Configuração inicial da janela do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    // Abre a janela
    glutCreateWindow("Thunder");

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(0, atualiza, 0);
    inicializa();

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
