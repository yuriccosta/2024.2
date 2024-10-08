#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define ALTURA_ARV_MED 0.8
#define LARGURA_ARV_MED 0.1

#define ALTURA_ARV_COMPRIDA 0.8
#define LARGURA_ARV_COMPRIDA 0.1

#define RAIO_DO_VID_GRANDE 0.42
#define RAIO_DO_VID_CENTRAL 0.19

#define DISTANCIA_ESQUERDA_DA_BASE 1.5
#define DISTANCIA_DIREITA_DA_BASE 0.5

GLdouble min = -5, max = 5;

void display(void);

void criarArvore(double x, double y, double altura);
void criaCirculo(double x0, double y0, double raio);
void criaElipse(double x0, double y0, double raioX, double raioY);
void criaOctagono(double x0, double y0, double raio);
void criaEstrelas(int n, int random);
void criaArvoreMedia(double x, double y);
void criarArvoreComprida(double x, double y);
void criaArbusto(double x, double y, double raio);
void criaNuvem(double x0,double y0, double raioX, double raioY);
void criaRio(double x0, double y0, double limx, double limy, int seed, int type);
void criaTieFighter(double x, double y);

int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  glutInitWindowSize (800, 600); //Estabelece o tamanho (em pixels) da janela a ser criada
  glutInitWindowPosition (1367, 00); //Posição inicial do canto superior esquerdo da janela a ser criada 
  glutCreateWindow (argv[1]); //Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(0.047, 0.052, 0.061, 0.0); //selecionar cor de fundo (Branco)
  glOrtho (min, max, min, max, min, max); //define as coordenadas +do volume de recorte (clipping volume),
  glutDisplayFunc(display); //Função callback chamada para fazer o desenho
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  printf("\nTestando... \n");
  return 0;
}


void criarArvore(double x, double y, double altura){
  // Tronco
  glColor3ub(75, 51, 0);
  glBegin(GL_QUADS);
    glVertex2d(x, y);
    glVertex2d(x, y + altura);
    glVertex2d(x + 0.05, y + altura );
    glVertex2d(x + 0.05, y);
  glEnd();

  // Galhos
  glLineWidth(2.0);
  glBegin(GL_LINES);
    for (int c = 0; c <= 10; c++){
      glVertex2d((2*x+ 0.05) / 2 , y + altura  - 0.1);
      glVertex2d(x - 0.5 + c *0.1, y + altura + 0.5);
    }
  glEnd();
  glLineWidth(1.0);

  // Folhas
  glColor3ub(33, 40, 15);
  /* glBegin(GL_POLYGON);
    glVertex2d(x - 0.5, y + 1.5);
    glVertex2d(x - 0.25, y + 1.7);
    glVertex2d(x + 0.25, y + 1.7);
    glVertex2d(x + 0.5, y + 1.5);
  glEnd(); */

  criaElipse(x, y + altura + 0.5, 0.5, 0.2);
  criaElipse(x, y + altura + 0.6, 0.25, 0.4);


}

void criaArvoreMedia(double x, double y){
  // Tronco
  glColor3ub(75, 51, 0);
  glBegin(GL_QUADS);
    glVertex2d(x, y);
    glVertex2d(x, y + ALTURA_ARV_MED);
    glVertex2d(x + LARGURA_ARV_MED, y + ALTURA_ARV_MED );
    glVertex2d(x + LARGURA_ARV_MED, y);
  glEnd();

  // Folhas
  glColor3ub(33, 40, 15);
  criaElipse((2 * x + LARGURA_ARV_MED) / 2, y + ALTURA_ARV_MED, 0.5, 0.2);
  criaElipse((2 * x + LARGURA_ARV_MED) / 2, y + 0.7, 0.6, 0.2);
}

void criarArvoreComprida(double x, double y){
    // Tronco
  glColor3ub(75, 51, 0);
  glBegin(GL_QUADS);
    glVertex2d(x, y);
    glVertex2d(x, y + ALTURA_ARV_COMPRIDA);
    glVertex2d(x + LARGURA_ARV_COMPRIDA, y + ALTURA_ARV_COMPRIDA );
    glVertex2d(x + LARGURA_ARV_COMPRIDA, y);
  glEnd();

  // Folhas
  glColor3ub(33, 40, 15);
  criaElipse((2 * x + LARGURA_ARV_COMPRIDA) / 2, y + 1.25, 0.2, 0.4);
  criaElipse((2 * x + LARGURA_ARV_COMPRIDA) / 2, y + 1, 0.2, 0.6);
}


void criaCirculo(double x0, double y0, double raio){
  glBegin(GL_TRIANGLE_FAN);
      glVertex2d(x0, y0); // Centro do círculo
      double ang, x, y;
      for (int i = 0; i <= 100; i++) {
          ang = 2.0 * M_PI * i / 100; // Ângulo atual
          x = raio * cos(ang); // Coordenada x
          y = raio * sin(ang); // Coordenada y
          glVertex2d(x0 + x, y0 + y);
      }
  glEnd();
}

void criaElipse(double x0, double y0, double raioX, double raioY){
  glBegin(GL_TRIANGLE_FAN);
      glVertex2d(x0, y0); // Centro do círculo
      double ang, x, y;
      for (int i = 0; i <= 100; i++) {
          ang = 2.0 * M_PI * i / 100; // Ângulo atual
          x = raioX * cos(ang); // Coordenada x
          y = raioY * sin(ang); // Coordenada y
          glVertex2d(x0 + x, y0 + y);
      }
  glEnd();
}

void criaSemiElipse(double x0, double y0, double raioX, double raioY){
  glBegin(GL_TRIANGLE_FAN);
      glVertex2d(x0, y0); // Centro do círculo
      double ang, x, y;
      for (int i = 0; i <= 50; i++) {
          ang = 2.0 * M_PI * i / 100; // Ângulo atual
          x = raioX * cos(ang); // Coordenada x
          y = raioY * sin(ang); // Coordenada y
          glVertex2d(x0 + x, y0 + y);
      }
  glEnd();
}

void criaOctagono(double x0, double y0, double raio){
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x0, y0);
    double ang, x, y;
    for (int i = 0; i <= 8; i++){
      ang = 2.0 * M_PI * i / 8;
      x = raio * cos(ang);
      y = raio * sin(ang);
      glVertex2d(x0 + x, y0 + y);
    }
  glEnd();
}



void criaEstrelas(int n, int random){
  srand(random);
  glColor3ub(255, 255, 255);
  glBegin(GL_POINTS);
    for (int i = 0; i < n; i++){
      glVertex2d(((double)rand() / RAND_MAX) * 10.0 - 5.0, ((double)rand() / RAND_MAX) * 5.0);
    }
  glEnd();
}

void criaArbusto(double x, double y, double raio){
  double ang, x0, y0;
  glColor3ub(33, 40, 15);
  glBegin(GL_LINES);
    for (int i = 0; i <= 25; i++){
      ang = 2.0 * M_PI * i / 50;
      x0 =  raio * cos(ang);
      y0 = raio * sin(ang);
      glVertex2d(x + x0, y + y0);
      glVertex2d(x , y);
    }
  glEnd();
}

void criaRio(double x0, double y0, double limx, double limy, int seed, int type){
  srand(seed);
  if (type == 1){
    glBegin(GL_QUAD_STRIP);
      double x = x0, y = y0, randx, randy;
      while (1){
        if (x < limx || y > limy){
          break;
        }
        randx = (double) rand() / RAND_MAX * 0.5;
        randy = (double) rand() / RAND_MAX * 0.5;
        glVertex2d(x, y);
        glVertex2d(x - randx, y + randy);
        x -= randx;
        y += randy;
      }
    glEnd();

  } else{
    glBegin(GL_QUAD_STRIP);
      double x = x0, y = y0, randx, randy;
      while (1){
        if (x > limx || y > limy){
          break;
        }
        randx = (double) rand() / RAND_MAX * 0.5;
        randy = (double) rand() / RAND_MAX * 0.5;
        glVertex2d(x, y);
        glVertex2d(x + randx, y + randy);
        x += randx;
        y += randy;
      }
    glEnd();
  }
}


void criaTieFighter(double x, double y){
  double ang, x1, y1, x0, y0;

  // Base
  glColor3ub(166, 175, 186);
  criaElipse(x, y + 0.1, 0.6, 0.55);
  criaElipse(x, y - 0.1, 0.6, 0.55);

  // Base da asa esquerda
  glColor3ub(166, 175, 186);
  glBegin(GL_QUADS);
    glVertex2d(x - DISTANCIA_DIREITA_DA_BASE, y + 0.4);
    glVertex2d(x - DISTANCIA_DIREITA_DA_BASE, y - 0.4);
    glVertex2d(x - DISTANCIA_ESQUERDA_DA_BASE, y - 0.05);
    glVertex2d(x - DISTANCIA_ESQUERDA_DA_BASE, y + 0.05);
  glEnd();
  // Detalhe da base da asa esquerda
  glColor3ub(76, 80, 86);
  glBegin(GL_QUADS);
    glVertex2d(x - 0.7, y + 0.1);
    glVertex2d(x - 0.7, y - 0.1);
    glVertex2d(x - 1, y - 0.05);
    glVertex2d(x - 1, y + 0.05);
  glEnd();
  // Linha da asa esquerda
  glBegin(GL_LINES);
    glVertex2d(x - 0.5, y + 0.3);
    glVertex2d(x - 1.4, y );
    glVertex2d(x - 0.5, y - 0.3);
    glVertex2d(x - 1.4, y );
  glEnd();

  // Base da asa direita
  glColor3ub(166, 175, 186);
  glBegin(GL_QUADS);
    glVertex2d(x + 0.5, y + 0.4);
    glVertex2d(x + 0.5, y - 0.4);
    glColor3ub(166, 175, 186);
    glVertex2d(x + 1.5, y - 0.05);
    glVertex2d(x + 1.5, y + 0.05);
  glEnd();
  // Detalhe da base da asa direita
  glColor3ub(76, 80, 86);
  glBegin(GL_QUADS);
    glVertex2d(x + 0.7, y + 0.1);
    glVertex2d(x + 0.7, y - 0.1);
    glVertex2d(x + 1, y - 0.05);
    glVertex2d(x + 1, y + 0.05);
  glEnd();
  // Linha da asa direita
  glBegin(GL_LINES);
    glVertex2d(x + 0.5, y + 0.3);
    glVertex2d(x + 1.4, y );
    glVertex2d(x + 0.5, y - 0.3);
    glVertex2d(x + 1.4, y );
  glEnd();

  // Asa esquerda
  glColor3ub(62, 70, 81);
  glBegin(GL_QUAD_STRIP);
    // Parte de cima
    glVertex2d(x - 0.9, y + 1.5);
    glVertex2d(x - 0.8, y + 1.5);
    glVertex2d(x - 1.45, y + 0.5);
    glVertex2d(x - 1.3, y + 0.5);

    // Parte do meio
    glVertex2d(x - 1.45, y - 0.5);
    glVertex2d(x - 1.3, y - 0.5);

    // Parte de baixo
    glVertex2d(x - 0.9, y - 1.5);
    glVertex2d(x - 0.8, y - 1.5);
  glEnd();

  // Asa direita
  glBegin(GL_QUAD_STRIP);
    // Parte de cima
    glVertex2d(x + 0.9, y + 1.5);
    glVertex2d(x + 0.8, y + 1.5);
    glVertex2d(x + 1.45, y + 0.5);
    glVertex2d(x + 1.3, y + 0.5);

    // Parte do meio
    glVertex2d(x + 1.45, y - 0.5);
    glVertex2d(x + 1.3, y - 0.5);

    // Parte de baixo
    glVertex2d(x + 0.9, y - 1.5);
    glVertex2d(x + 0.8, y - 1.5);
  glEnd();

  // Detalhe da base
  glColor3ub(76, 80, 86);
  glBegin(GL_LINES);
    glBegin(GL_LINES);
    for (int i = 0; i <= 10; i++){
      ang = 2.0 * M_PI * i / 10;
      x1 = 0.60 * cos(ang);
      y1 = 0.65 * sin(ang);
      glVertex2d(x + x1, y + y1);
      glVertex2d(x , y);
    }
  glEnd();

  // Aro do vidro
  glColor3ub(62, 70, 81);
  criaCirculo(x, y, 0.47);
  // Vidro grande
  glColor3ub(15, 36, 50);
  criaCirculo(x, y, RAIO_DO_VID_GRANDE);

  // Aro do vidro central
  glColor3ub(62, 70, 81);
  criaOctagono(x, y, 0.22);
  // Vidro central
  glColor3ub(15, 36, 50);
  criaOctagono(x, y, RAIO_DO_VID_CENTRAL);

  glLineWidth(2.0);
  // Aros de sustentação do vidro central
  glColor3ub(62, 70, 81);
  glBegin(GL_LINES);
    for (int i = 0; i <= 8; i++){
      ang = 2.0 * M_PI * i / 8;
      x1 = RAIO_DO_VID_GRANDE * cos(ang);
      y1 = RAIO_DO_VID_GRANDE * sin(ang);
      x0 = RAIO_DO_VID_CENTRAL * cos(ang);
      y0 = RAIO_DO_VID_CENTRAL * sin(ang);
      glVertex2d(x + x1, y + y1);
      glVertex2d(x + x0, y + y0);
    }
  glEnd();
  glLineWidth(1.0);

  // Canhão
  glColor3ub(151, 54, 53);
  criaCirculo(x + 0.25 ,y - 0.5, 0.045);
  criaCirculo(x - 0.25 ,y - 0.5, 0.045);

  // Escotilha
  glColor3ub(166, 175, 186);
  criaSemiElipse(x, y + 0.5, 0.4, 0.15);
  glColor3ub(76, 80, 86);
  glBegin(GL_LINES);
    glVertex2d(x - 0.4, y + 0.5);
    glVertex2d(x + 0.4, y + 0.5);
  glEnd();
  criaSemiElipse(x, y + 0.53, 0.3, 0.1);

}

void criaNuvem(double x0,double y0, double raioX, double raioY){
  criaElipse(x0, y0, raioX, raioY);
  criaElipse(x0 - 0.5, y0, raioX - 0.1, raioY - 0.15);
  criaElipse(x0 + 0.5, y0, raioX - 0.1, raioY - 0.15);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada

  // Cria o terreno
  glColor3ub(57, 69, 13);
  glBegin(GL_QUADS);
    glVertex2d(max, min);
    glColor3ub(77, 89, 33);
    glVertex2d(min, min);
    glColor3ub(57, 69, 13);
    glVertex2d(min, 0);
    glColor3ub(37, 39, 0);
    glVertex2d(max, 0);
  glEnd();

  //Cria estrelas
  criaEstrelas(200, 2);

  //Cria rio
  glColor3ub(105, 149, 172);
  criaRio(5, -5, 0, 0, 10, 1);
  criaRio(5, -5, 0, 0, 3, 1);
  criaRio(2, -5 , 4, -4, 5, 2);


  // Cria as arvóres
  criarArvore(-4, -4.5, 1);
  criarArvore(-3, -3.2, 0.5);
  criarArvore(-2, -4.2, 0.8);
  criarArvore(4.8, -1, 0.4);

  criaArvoreMedia(-1, -4);
  criaArvoreMedia(0, -3.4);

  criarArvoreComprida(1, -4);
  criarArvoreComprida(2, -2.8);
  
  
  // Cria os arbustos
  criaArbusto(-3.5, -1.5, 0.3);
  criaArbusto(2, -4, 0.25);
  criaArbusto(3, -3.5, 0.2);
  criaArbusto(-2.5, -3.4, 0.2);  
  criaArbusto(1.5, -3.8, 0.1);   
  criaArbusto(3.5, -3.0, 0.25);  
  criaArbusto(4.0, -3.5, 0.2);


  // Cria a lua
  glColor3ub(190, 242, 236);
  criaCirculo(-3, 3.5, sqrt(0.5));
  // Crateras na lua
  glColor3ub(57, 79, 105);
  criaElipse(-3.25, 3.8, 0.2, 0.08);
  glColor3ub(71, 94, 113);
  criaElipse(-3.45, 3.6, 0.2, 0.1);
  glColor3ub(57, 82, 110);
  criaElipse(-3.3, 3.3, 0.2, 0.3);
  criaElipse(-2.8, 3.4, 0.4, 0.2);
  // Preenche as crateras
  glColor3ub(190, 242, 236);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2d(-3, 4);
    glVertex2d(-2.5, 3.7);
    glVertex2d(-2.5, 3.4);
  glEnd();
  criaElipse(-3.1, 3.8, 0.2, 0.09);
  criaElipse(-3.6, 3.6, 0.1, 0.1);
  criaSemiElipse(-3.3, 3.3, 0.4, 0.3);
  criaCirculo(-3, 3.3, 0.3);


   //Cria nuvens
  glColor3ub(115, 134, 129);
  criaNuvem(-0.8, 1.4, 0.5, 0.3);
  criaNuvem(-4, 1, 0.5, 0.45);
  criaNuvem(2.8, 0.5, 0.4, 0.3);

  //Cria um planalto
  glColor3ub(100,32,25);
  glBegin(GL_QUADS);
    glVertex2d(-1, 1);
    glVertex2d(-2, 1);
    glColor3ub(80,22,15);
    glVertex2d(-2.5, -0.3);
    glVertex2d(0.9, -0.3);
  glEnd();

  criaTieFighter(3, 3);
  
  glFlush(); ////Executa os comandos OpenGL para renderização
}