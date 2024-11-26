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
GLdouble xpos = 3, ypos = 3, scale = 0.8;
GLdouble cotovelo = 90, munheca = -90, mao = 90, garra = 10;
GLshort send = 0;
GLdouble xtarget = 0, ytarget = -2, lastX = 0, xdeslocBomb = 0, ydeslocBomb = 0;
GLdouble xini, yini;
double speedX = 0.0;
double launchTime;
GLshort pause = 0;

void display(void);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);
void Animar(int interacoes);

void criarArvore(double x, double y, double altura);
void criaCirculo(double x0, double y0, double raio);
void criaElipse(double x0, double y0, double raioX, double raioY);
void criaOctagono(double x0, double y0, double raio);
void criaEstrelas(int n, int random);
void criaArvoreMedia(double x, double y);
void criarArvoreComprida(double x, double y);
void criaArbusto(double x, double y, double raio);
void criaNuvem(double x0, double y0, double raioX, double raioY);
void criaRio(double x0, double y0, double limx, double limy, int seed, int type);
void criaTieFighter(double x, double y);
void criaBB8();
void sendProjectile();

int main(int argc, char **argv)
{
  glutInit(&argc, argv);                       // Estabelece contato com sistema de janelas
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Cores dos pixels serão expressos em RGB
  //glutInitWindowSize(800, 600);                // Estabelece o tamanho (em pixels) da janela a ser criada
  glutInitWindowSize(1024, 768);   
  glutInitWindowPosition(1367, 00);            // Posição inicial do canto superior esquerdo da janela a ser criada
  glutCreateWindow("Atividade 4");                   // Cria uma nova janela com valor de retorno (não usado)
  // que a identifica, caso tenha mais de uma
  glClearColor(0.047, 0.052, 0.061, 0.0); // selecionar cor de fundo (Branco)
  glOrtho(min, max, min, max, min, max);  // define as coordenadas +do volume de recorte (clipping volume),
  glutDisplayFunc(display);               // Função callback chamada para fazer o desenho
  glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
  glutSpecialFunc(Special_keyboard); // Registra a função para tratamento das teclas NÂO ASCII
  glutTimerFunc(30,Animar,0); // Chama a função de call back de animação
  glutMainLoop();                         // Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  return 0;
}

void criarArvore(double x, double y, double altura)
{
  // Tronco
  glColor3ub(75, 51, 0);
  glBegin(GL_QUADS);
  glVertex2d(x, y);
  glVertex2d(x, y + altura);
  glVertex2d(x + 0.05, y + altura);
  glVertex2d(x + 0.05, y);
  glEnd();

  // Galhos
  glLineWidth(2.0);
  glBegin(GL_LINES);
  for (int c = 0; c <= 10; c++)
  {
    glVertex2d((2 * x + 0.05) / 2, y + altura - 0.1);
    glVertex2d(x - 0.5 + c * 0.1, y + altura + 0.5);
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

void criaArvoreMedia(double x, double y)
{
  // Tronco
  glColor3ub(75, 51, 0);
  glBegin(GL_QUADS);
  glVertex2d(x, y);
  glVertex2d(x, y + ALTURA_ARV_MED);
  glVertex2d(x + LARGURA_ARV_MED, y + ALTURA_ARV_MED);
  glVertex2d(x + LARGURA_ARV_MED, y);
  glEnd();

  // Folhas
  glColor3ub(33, 40, 15);
  criaElipse((2 * x + LARGURA_ARV_MED) / 2, y + ALTURA_ARV_MED, 0.5, 0.2);
  criaElipse((2 * x + LARGURA_ARV_MED) / 2, y + 0.7, 0.6, 0.2);
}

void criarArvoreComprida(double x, double y)
{
  // Tronco
  glColor3ub(75, 51, 0);
  glBegin(GL_QUADS);
  glVertex2d(x, y);
  glVertex2d(x, y + ALTURA_ARV_COMPRIDA);
  glVertex2d(x + LARGURA_ARV_COMPRIDA, y + ALTURA_ARV_COMPRIDA);
  glVertex2d(x + LARGURA_ARV_COMPRIDA, y);
  glEnd();

  // Folhas
  glColor3ub(33, 40, 15);
  criaElipse((2 * x + LARGURA_ARV_COMPRIDA) / 2, y + 1.25, 0.2, 0.4);
  criaElipse((2 * x + LARGURA_ARV_COMPRIDA) / 2, y + 1, 0.2, 0.6);
}

void criaCirculo(double x0, double y0, double raio)
{
  glBegin(GL_TRIANGLE_FAN);
  glVertex2d(x0, y0); // Centro do círculo
  double ang, x, y;
  for (int i = 0; i <= 100; i++)
  {
    ang = 2.0 * M_PI * i / 100; // Ângulo atual
    x = raio * cos(ang);        // Coordenada x
    y = raio * sin(ang);        // Coordenada y
    glVertex2d(x0 + x, y0 + y);
  }
  glEnd();
}

void criaElipse(double x0, double y0, double raioX, double raioY)
{
  glBegin(GL_TRIANGLE_FAN);
  glVertex2d(x0, y0); // Centro do círculo
  double ang, x, y;
  for (int i = 0; i <= 100; i++)
  {
    ang = 2.0 * M_PI * i / 100; // Ângulo atual
    x = raioX * cos(ang);       // Coordenada x
    y = raioY * sin(ang);       // Coordenada y
    glVertex2d(x0 + x, y0 + y);
  }
  glEnd();
}

void criaSemiElipse(double x0, double y0, double raioX, double raioY)
{
  glBegin(GL_TRIANGLE_FAN);
  glVertex2d(x0, y0); // Centro do círculo
  double ang, x, y;
  for (int i = 0; i <= 50; i++)
  {
    ang = 2.0 * M_PI * i / 100; // Ângulo atual
    x = raioX * cos(ang);       // Coordenada x
    y = raioY * sin(ang);       // Coordenada y
    glVertex2d(x0 + x, y0 + y);
  }
  glEnd();
}

void criaOctagono(double x0, double y0, double raio)
{
  glBegin(GL_TRIANGLE_FAN);
  glVertex2d(x0, y0);
  double ang, x, y;
  for (int i = 0; i <= 8; i++)
  {
    ang = 2.0 * M_PI * i / 8;
    x = raio * cos(ang);
    y = raio * sin(ang);
    glVertex2d(x0 + x, y0 + y);
  }
  glEnd();
}

void criaEstrelas(int n, int random)
{
  srand(random);
  glColor3ub(255, 255, 255);
  glBegin(GL_POINTS);
  for (int i = 0; i < n; i++)
  {
    glVertex2d(((double)rand() / RAND_MAX) * 10.0 - 5.0, ((double)rand() / RAND_MAX) * 5.0);
  }
  glEnd();
}

void criaArbusto(double x, double y, double raio)
{
  double ang, x0, y0;
  glColor3ub(33, 40, 15);
  glBegin(GL_LINES);
  for (int i = 0; i <= 25; i++)
  {
    ang = 2.0 * M_PI * i / 50;
    x0 = raio * cos(ang);
    y0 = raio * sin(ang);
    glVertex2d(x + x0, y + y0);
    glVertex2d(x, y);
  }
  glEnd();
}

void criaRio(double x0, double y0, double limx, double limy, int seed, int type)
{
  srand(seed);
  if (type == 1)
  {
    glBegin(GL_QUAD_STRIP);
    double x = x0, y = y0, randx, randy;
    while (1)
    {
      if (x < limx || y > limy)
      {
        break;
      }
      randx = (double)rand() / RAND_MAX * 0.5;
      randy = (double)rand() / RAND_MAX * 0.5;
      glVertex2d(x, y);
      glVertex2d(x - randx, y + randy);
      x -= randx;
      y += randy;
    }
    glEnd();
  }
  else
  {
    glBegin(GL_QUAD_STRIP);
    double x = x0, y = y0, randx, randy;
    while (1)
    {
      if (x > limx || y > limy)
      {
        break;
      }
      randx = (double)rand() / RAND_MAX * 0.5;
      randy = (double)rand() / RAND_MAX * 0.5;
      glVertex2d(x, y);
      glVertex2d(x + randx, y + randy);
      x += randx;
      y += randy;
    }
    glEnd();
  }
}

void criaTieFighter(double x, double y)
{
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
  glVertex2d(x - 1.4, y);
  glVertex2d(x - 0.5, y - 0.3);
  glVertex2d(x - 1.4, y);
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
  glVertex2d(x + 1.4, y);
  glVertex2d(x + 0.5, y - 0.3);
  glVertex2d(x + 1.4, y);
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
  for (int i = 0; i <= 10; i++)
  {
    ang = 2.0 * M_PI * i / 10;
    x1 = 0.60 * cos(ang);
    y1 = 0.65 * sin(ang);
    glVertex2d(x + x1, y + y1);
    glVertex2d(x, y);
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
  for (int i = 0; i <= 8; i++)
  {
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
  criaCirculo(x + 0.25, y - 0.5, 0.045);
  criaCirculo(x - 0.25, y - 0.5, 0.045);

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

void criaNuvem(double x0, double y0, double raioX, double raioY)
{
  criaElipse(x0, y0, raioX, raioY);
  criaElipse(x0 - 0.5, y0, raioX - 0.1, raioY - 0.15);
  criaElipse(x0 + 0.5, y0, raioX - 0.1, raioY - 0.15);
}

void criaBB8(){
  double x = 0 , y = 0;
  // Base
  glColor3ub(255,255,255);
  criaCirculo(x, y, 1.1);
  glColor3ub(231, 132, 0);
  criaCirculo(x, y, 0.6);
  glColor3ub(255,255,255);
  criaCirculo(x, y, 0.45);

  // Faixas da base
  // Faixa de cima
  glColor3ub(231, 132, 0);
  glPushMatrix();
    glTranslated(0,0.9,0);
    criaSemiElipse(x, y, 0.6, 0.2);
    glColor3ub(255,255,255);
    glTranslated(0,0.1,0);
    criaSemiElipse(x, y, 0.5, 0.1);
  glPopMatrix();
  
  // Faixa de baixo
  glPushMatrix();
    glRotated(180, 0, 0, 1);
    glTranslated(0,0.9,0);
    glColor3ub(231, 132, 0);
    criaSemiElipse(x, y, 0.6, 0.2);
    glColor3ub(255,255,255);
    glTranslated(0,0.1,0);
    criaSemiElipse(x, y, 0.5, 0.1);
  glPopMatrix();

  // Faixa da direita
  glPushMatrix();
    glTranslated(0.9,0,0);
    glRotated(-90, 0, 0, 1);
    glColor3ub(231, 132, 0);
    criaSemiElipse(x, y, 0.6, 0.2);
    glColor3ub(255,255,255);
    glTranslated(0,0.1,0);
    criaSemiElipse(x, y, 0.5, 0.1);
  glPopMatrix();

  // Faixa da esquerda
  glPushMatrix();
    glRotated(90, 0, 0, 1);
    glTranslated(0,0.9,0);
    glColor3ub(231, 132, 0);
    criaSemiElipse(x, y, 0.6, 0.2);
    glColor3ub(255,255,255);
    glTranslated(0,0.1,0);
    criaSemiElipse(x, y, 0.5, 0.1);
  glPopMatrix();

  // Detalhes da base
  glColor3ub(231, 132, 0);
  glBegin(GL_QUADS);
  glEnd();

  // Trapezio Superior Esquerdo da Base
  glPushMatrix();
    glRotated(55, 0, 0, 1);
    glTranslated(x,y + 0.2,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.27);
      glVertex2d(x + 0.1,y + 0.27);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  // Trapezio Superior Direito da Base
  glPushMatrix();
    glRotated(-55, 0, 0, 1);
    glTranslated(x,y + 0.2,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.27);
      glVertex2d(x + 0.1,y + 0.27);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  // Trapezio Inferior Esquerdo da Base
  glPushMatrix();
    glRotated(125, 0, 0, 1);
    glTranslated(x,y + 0.2,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.27);
      glVertex2d(x + 0.1,y + 0.27);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  //Trapezio Inferior Direito da Base
  glPushMatrix();
    glRotated(-125, 0, 0, 1);
    glTranslated(x,y + 0.2,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.27);
      glVertex2d(x + 0.1,y + 0.27);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  // Peça de Aço Inferior da Base
  glPushMatrix();
    glTranslated(x - 0.04,y - 0.58,0);
    glBegin(GL_QUADS);
    glColor3ub(169, 169, 169);
    glVertex2d(x - 0.1,y + 0.3);
    glVertex2d(x + 0.2,y + 0.3);
    glVertex2d(x + 0.2,y + 0.2);
    glVertex2d(x - 0.1,y + 0.2);
    glEnd();
  glPopMatrix();

  // Peça de Aço Superior da Base
  glPushMatrix();
    glTranslated(x - 0.04,y + 0.05,0);
    glBegin(GL_QUADS);
    glColor3ub(169, 169, 169);
    glVertex2d(x - 0.1,y + 0.3);
    glVertex2d(x + 0.2,y + 0.3);
    glVertex2d(x + 0.2,y + 0.2);
    glVertex2d(x - 0.1,y + 0.2);
    glEnd();
  glPopMatrix();

  // Peça de Aço Central da Base
  glPushMatrix();
    glRotated(90, 0, 0, 1);
    glColor3ub(169, 169, 169);
    criaSemiElipse(x, y, 0.2, 0.15);
  glPopMatrix();

  

  // Trapezio Inferior da Base
  glPushMatrix();
    glTranslated(x,y - 1.1,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.10);
      glVertex2d(x + 0.1,y + 0.10);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  // Trapezio Direito da Base
  glPushMatrix();
    glRotated(90, 0, 0, 1);
    glTranslated(x + 0.2,y - 1.1,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.10);
      glVertex2d(x + 0.1,y + 0.10);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  glPushMatrix();
    glRotated(90, 0, 0, 1);
    glTranslated(x - 0.2,y - 1.1,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.10);
      glVertex2d(x + 0.1,y + 0.10);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  // Trapezio Superior da Base
  glPushMatrix();
    glRotated(180, 0, 0, 1);
    glTranslated(x,y - 1.1,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.10);
      glVertex2d(x + 0.1,y + 0.10);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();
  
  // Trapezio Esquerdo da Base
  glPushMatrix();
    glRotated(270, 0, 0, 1);
    glTranslated(x + 0.2,y - 1.1,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.10);
      glVertex2d(x + 0.1,y + 0.10);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  glPushMatrix();
    glRotated(270, 0, 0, 1);
    glTranslated(x - 0.2,y - 1.1,0);
      glBegin(GL_QUADS);
      glColor3ub(231, 132, 0);
      glVertex2d(x - 0.06,y);
      glVertex2d(x - 0.1,y + 0.10);
      glVertex2d(x + 0.1,y + 0.10);
      glVertex2d(x + 0.06,y);
      glEnd();
  glPopMatrix();

  // Cabeça
  glColor3ub(255,255,255);
  criaSemiElipse(x, y + 1.1, 0.6, 0.7);
  glColor3ub(0,0,0);
  criaCirculo(x - 0.1, y + 1.45, 0.12);
  glColor3ub(250,0,0);
  criaCirculo(x - 0.1, y + 1.45, 0.03);
  glColor3ub(0,0,0);
  criaCirculo(x + 0.2, y + 1.3, 0.1);
  glColor3ub(0,0,0);

  //Antena
  glBegin(GL_LINES);
    glColor3ub(169,169,169);
    glVertex2d(x + 0.05, y + 2.5);
    glVertex2d(x + 0.05, y + 1.8);
  glEnd();
  
  glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2d(x + 0.05, y + 1.9);
    glVertex2d(x + 0.05, y + 1.8);
    glVertex2d(x + 0.05, y + 2.5);
    glVertex2d(x + 0.05, y + 2.4);
  glEnd();

  //Antena Menor
  glBegin(GL_LINES);
  glColor3ub(169,169,169);
  glVertex2d(x - 0.1, y + 2.1);
  glVertex2d(x - 0.1, y + 1.8);
  glEnd();


    // Faixa cinza acima do olho
    glColor3ub(169, 169, 169);
    glPushMatrix();
      glTranslated(x, y + 1.65, 0);
      criaSemiElipse(x, y, 0.36, 0.09);
    glPopMatrix();

  // Garra mecânica
  // Base
  glColor3ub(172, 174, 175);
  glBegin(GL_QUADS);
    glVertex2d(x + 1.05, y - 0.1);
    glVertex2d(x + 1.05, y + 0.1);
    glVertex2d(x + 1.3, y + 0.1);
    glVertex2d(x + 1.3, y - 0.1);
  glEnd();

  // Articulação do cotovelo
  glPushMatrix();
    glTranslated(1.3,0,0);
    glRotated(-90, 0, 0, 1);
    criaSemiElipse(x, y, 0.1, 0.1);
  glPopMatrix();

  // Antebraço
  glColor3ub(172, 174, 175);
  //glColor3ub(0, 194, 195);
  glPushMatrix();
    glTranslated(1.35,0,0);
    glRotated(cotovelo, 0, 0, 1);
    glTranslated(-1.35,0,0);
    glBegin(GL_QUADS);
      glVertex2d(x + 1.35, y - 0.06);
      glVertex2d(x + 1.35, y + 0.06);
      glVertex2d(x + 1.7, y + 0.06);
      glVertex2d(x + 1.7, y -0.06);
    glEnd();
    //glPopMatrix();

    // Articulação da munheca
    glPushMatrix();
      glTranslated(1.65,0,0);
      glRotated(-90, 0, 0, 1);
      criaSemiElipse(x, y, 0.06, 0.1);
    glPopMatrix();
    //glPopMatrix();

    // Munheca
    glPushMatrix();
      glTranslated(1.7,0,0);
      glRotated(munheca, 0, 0, 1);
      glTranslated(-1.7,0,0);
      glBegin(GL_QUADS);
        glVertex2d(x + 1.7, y - 0.05);
        glVertex2d(x + 1.7, y + 0.05);
        glVertex2d(x + 1.9, y + 0.05);
        glVertex2d(x + 1.9, y -0.05);
      glEnd();
      //glPopMatrix();

      // Articulação da base da mão
      glColor3ub(162, 164, 165);
      glPushMatrix();
        glTranslated(1.84,0,0);
        glRotated(-90, 0, 0, 1);
        criaSemiElipse(x, y, 0.05, 0.1);
      glPopMatrix();

      // Mão
      glPushMatrix();
        glTranslated(1.9,0,0);
        glRotated(mao, 0, 0, 1);
        glTranslated(-1.9,0,0);
        glBegin(GL_QUADS);
          glVertex2d(x + 1.9, y - 0.04);
          glVertex2d(x + 1.9, y + 0.04);
          glVertex2d(x + 2, y + 0.04);
          glVertex2d(x + 2, y -0.04);
        glEnd();
        //glPopMatrix();

        // Articulação da Base da garra
        glPushMatrix();
          glTranslated(1.94,0,0);
          glRotated(-90, 0, 0, 1);
          criaSemiElipse(x, y, 0.02, 0.05);
        glPopMatrix();

        // Garra da esquerda
        glPushMatrix();
          glTranslated(2,0,0);
          glRotated(garra, 0, 0, 1);
          glTranslated(-2,0,0);
          glBegin(GL_QUADS);
            glVertex2d(x + 2, y);
            glVertex2d(x + 2, y + 0.05);
            glVertex2d(x + 2.15, y + 0.05);
            glVertex2d(x + 2.15, y);
          glEnd();
          glTranslated(2.15,0.025,0);
          glRotated(-90, 0, 0, 1);
          criaSemiElipse(x, y, 0.02, 0.04);
        glPopMatrix();

        // Garra da direita
        glPushMatrix();
          glTranslated(2,0,0);
          glRotated(-garra, 0, 0, 1);
          glTranslated(-2,0,0);
          glBegin(GL_QUADS);
            glVertex2d(x + 2, y);
            glVertex2d(x + 2, y - 0.05);
            glVertex2d(x + 2.15, y - 0.05);
            glVertex2d(x + 2.15, y);
          glEnd();
          glTranslated(2.15,-0.025,0);
          glRotated(-90, 0, 0, 1);
          criaSemiElipse(x, y, 0.02, 0.04);
        glPopMatrix();

      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

}

void sendProjectile(){
  // Gera Pokébola
  glColor3ub(170, 0, 0); 
  criaCirculo(0, 0, 0.3);
  glColor3ub(0, 0, 0);

  // Detalhes de Baixo da Pokébola
  glPushMatrix();
    glTranslated(0, 0, 0);
    glRotated(180, 0, 0, 1);
    glColor3ub(255, 255, 255);
    criaSemiElipse(0, 0, 0.3, 0.3);
  glPopMatrix();

  //Detalhes do Centro da Pokébola
  glColor3ub(0,0,0);
  criaCirculo(0, 0, 0.1);
  glColor3ub(255, 255, 255);
  criaCirculo(0, 0, 0.07);
  glColor3ub(0,0,0);
  criaCirculo(0, 0, 0.05);
  glColor3ub(255, 255, 255);
  criaCirculo(0, 0, 0.04);
}

void Animar(int interacoes) {
    // Não atualiza os frames até despausar;
    if (pause) {
        // Quer dizer que acertamos o alvo e pausamos, portanto resetamos o estado
        send = 0;
        glutTimerFunc(30, Animar, interacoes); // Reagendar apenas para verificar pausa
        return;
    }
    double gravity = 9.81; // Gravidade
    double currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    double timeElapsed = ((currentTime - launchTime));
    
    // Verifica se mudamos de posição a cada 5 frames, se sim estamos em movimento
    if (fmod(interacoes, 5) == 0) {
      // Verificamos se o alvo já esta em lançamento
      if (send == 0){
        // Se o alvo não esta sendo lançado salvamos a ultima posição da nave em X e a velocidade para a direita ou esquerda, ou 0 se parado
        if (xpos > lastX){
          lastX = xpos;
          speedX = 2;
        } else if (xpos < lastX){
          lastX = xpos;
          speedX = -2;
        } else{
          speedX = 0;
        }
      }
    }

    // Atualizar o alvo em movimento a cada 15 frames
    double aux = fmod(interacoes, 15);
    if (aux == 0.0) {
        srand(time(NULL));
        double deslocamento = ((double)rand() / RAND_MAX) * 2.0 - 1.0; // Gera um número aleatório entre -1 e 1
        xtarget += (GLdouble)deslocamento;

        // Se chegar próximo do limite da tela, volta para um pouco antes do limite
        if (xtarget < -4.5) xtarget = -4.0;
        if (xtarget > 4.5) xtarget = 4.0;
    }

    
    // Atualizar posição do projétil
    if (send) {
        xdeslocBomb = xini + speedX * timeElapsed;
        ydeslocBomb = yini - (0.5 * gravity * pow(timeElapsed, 2));

        // Verificar se o projétil saiu da tela
        if (xdeslocBomb > 5.0 || ydeslocBomb < -5.0 || xdeslocBomb < -5.0) {
            send = 0; // Reinicia o estado de lançamento
        }

        // Verifica se atingiu a cabeça do BB8, deslocBomb é adicionado com o raio do círculo que o fez
        // target é adicionado com o raio da semielipse que fez a cabeça do  BB8, mas como escalonamos ele, escalonamos tambem o raio de 0.6 para 0.3
        // ja a altura em y é escalonada de 0.7 para 0.35, depois adicionamos com a coordenada do proprio raio do BB8, pois a cabeça está acima dela
        if (xdeslocBomb + 0.3 >= xtarget - 0.3  &&
            xdeslocBomb - 0.3 <= xtarget + 0.3 &&
            ydeslocBomb - 0.3 <= ytarget + 0.8 &&
            ydeslocBomb + 0.3 >= ytarget + 0.55){
            // Pausamos
            pause = 1;
        }

        // Verificar se o projétil atingiu o alvo, target é adicionado com o raio do BB8, mas como escalonamos ele, escalonamos tambem o raio de 1.1 para 0.55
        // e reduzimos um pouco para 0.5 para melhores efeitos visuais
        if (xdeslocBomb + 0.3 >= xtarget - 0.5 &&
            xdeslocBomb - 0.3 <= xtarget + 0.5 && 
            ydeslocBomb - 0.3 <= ytarget + 0.5 &&
            ydeslocBomb + 0.3 >= ytarget - 0.5){
            // Pausamos
            pause = 1;
        } 
    } 

    glutPostRedisplay();
    glutTimerFunc(30, Animar, interacoes + 1); // Reagendar animação
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

  // Cria estrelas
  criaEstrelas(200, 2);

  // Cria rio
  glColor3ub(105, 149, 172);
  criaRio(5, -5, 0, 0, 10, 1);
  criaRio(5, -5, 0, 0, 3, 1);
  criaRio(2, -5, 4, -4, 5, 2);

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

  // Cria nuvens
  glColor3ub(185, 184, 189);
  criaNuvem(-0.8, 1.4, 0.5, 0.3);
  criaNuvem(-4, 1, 0.5, 0.45);
  criaNuvem(2.8, 0.5, 0.4, 0.3);

  // Nuvem Rotacionada e escalonada
  glPushMatrix();
    glTranslated(-4 + 0.5, 1 + 1, 0);
    glScaled(0.5, 0.5, 1.0);
    glRotated(-10, 0, 0, 1);
    glTranslated(4, -1, 0);
  criaNuvem(-4, 1, 0.5, 0.45);
  glPopMatrix();

  // Cria um planalto
  glColor3ub(100, 32, 25);
  glBegin(GL_QUADS);
  glVertex2d(-1, 1);
  glVertex2d(-2, 1);
  glColor3ub(80, 22, 15);
  glVertex2d(-2.5, -0.3);
  glVertex2d(0.9, -0.3);
  glEnd();

  glColor3ub(90, 22, 15);
  glBegin(GL_QUADS);
  glVertex2d(-0.8, 0.8);
  glVertex2d(-1.8, 0.8);
  glColor3ub(80, 22, 15);
  glVertex2d(-2.3, -0.2);
  glVertex2d(0.7, -0.2);
  glEnd();


  glPushMatrix();
    glTranslated(xtarget, ytarget, 0);
    glScaled(0.5, 0.5, 1.0);
    // Hit Box de colisão do corpo do BB8, para efeitos de teste,
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
      glVertex2d(-1.1, 1.1);
      glVertex2d(1.1, 1.1);
      glVertex2d(1.1, 1.1);
      glVertex2d(1.1, -1.1);
      glVertex2d(1.1, -1.1);
      glVertex2d(-1.1, -1.1);
      glVertex2d(-1.1, -1.1);
      glVertex2d(-1.1, 1.1);
    glEnd();
    // Hit Box da cabeça do BB8
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
      glVertex2d(-0.6, 1.1);
      glVertex2d(0.6, 1.1);
      glVertex2d(0.6, 1.1);
      glVertex2d(0.6, 1.8);
      glVertex2d(0.6, 1.8);
      glVertex2d(-0.6, 1.8);
      glVertex2d(-0.6, 1.8);
      glVertex2d(-0.6, 1.1);
    glEnd();

    criaBB8();
  glPopMatrix();

  // Faz o tie fighter se mover e mudar de tamanho
  glPushMatrix();
    //glTranslated(xpos, ypos, 0);

    glTranslated(xpos, ypos, 0);
    glScaled(scale, scale, 1.0);
    
    criaTieFighter(0, 0);
  glPopMatrix();

    if (send){
      glPushMatrix();
        glTranslated(xdeslocBomb,  ydeslocBomb, 0);
          glColor3ub(0, 0, 255);
          // Hit box de colisão para efeito de testes da bomba
          glBegin(GL_LINES);
            glVertex2d(-0.3, -0.3);
            glVertex2d(0.3, -0.3);
            glVertex2d(0.3, -0.3);
            glVertex2d(0.3, 0.3);
            glVertex2d(0.3, 0.3);
            glVertex2d(-0.3, 0.3);
            glVertex2d(-0.3, 0.3);
            glVertex2d(-0.3, -0.3);
          glEnd();

          sendProjectile();
      glPopMatrix();
    }


  //printf(">>> xpos: %lf >>> ypos: %lf >>> scale: %lf\n", xpos, ypos, scale);
  //printf(">>> x: %lf >>> y: %lf\n", 3+xpos, 3+ypos);
  //printf(">>> cotovelo: %lf >>> munheca: %lf >>> mao: %lf >>> garra: %lf\n", cotovelo, munheca, mao, garra);
  

  glutSwapBuffers(); ////Executa os comandos OpenGL para renderização
}

void keyboard(unsigned char key, int x, int y){
  printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",key);
  switch (key) {
    case 104: // h
      cotovelo += 10;
      if (cotovelo > 90) cotovelo -= 10;
      //glutPostRedisplay();
      break;
    case 106: // j
      cotovelo -= 10;
      if (cotovelo < -90) cotovelo += 10;
      //glutPostRedisplay();
      break;
    case 107: // k
      munheca += 10;
      if (munheca > 90) munheca -= 10;
      //glutPostRedisplay();
      break;
    case 108: // l
      munheca -= 10;
      if (munheca < -90) munheca += 10;
      //glutPostRedisplay();
      break;
    case 97: // a
      mao += 10;
      if (mao > 90) mao -= 10;
      //glutPostRedisplay();
      break;
    case 115: // s
      mao -= 10;
      if (mao < -90) mao += 10;
      //glutPostRedisplay();
      break;
    case 100: // d
      garra += 10;
      if (garra > 70) garra -= 10;
      //glutPostRedisplay();
      break;
    case 102: // f
      garra -= 10;
      if (garra < 10) garra += 10;
      //glutPostRedisplay();
      break;
    case ' ':
        if (pause) {
          pause = 0; // Retomar o jogo
        }else if (send == 0) {
          xini = xpos;  // Captura a posição inicial da nave
          yini = ypos - 0.9; // Define a posição vertical inicial do projétil
          xdeslocBomb = xini;
          ydeslocBomb = yini;
          send = 1;
          launchTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Armazena o tempo do lançamento
        }
        break;
  }
  

}

void Special_keyboard(GLint tecla, int x, int y) {
  switch (tecla) { // GLUT_KEY_RIGHT GLUT_KEY_DOWN GLUT_KEY_PAGE_UP GLUT_KEY_PAGE_DOWN GLUT_KEY_F1...
    case GLUT_KEY_UP:
      ypos += 0.1;
      //glutPostRedisplay();
      break;
    case GLUT_KEY_DOWN:
      ypos -= 0.1;
      //glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT:
      xpos -= 0.1;
      //glutPostRedisplay();
      break;
    case GLUT_KEY_RIGHT:
      xpos += 0.1;
      //glutPostRedisplay();
      break;
    case GLUT_KEY_PAGE_UP:
      scale += 0.05;
      //glutPostRedisplay();
      break;
    case GLUT_KEY_PAGE_DOWN:
      scale -= 0.05;
      if (scale < 0.1) scale += 0.05;
      //glutPostRedisplay();
      break;
  }
}