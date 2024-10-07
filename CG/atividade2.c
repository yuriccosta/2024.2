#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int R = 0, G=0, B = 0;
GLdouble min = -5, max = 5;

void display(void);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);
void DesenhaTexto(char *string);

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
  glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
  glutSpecialFunc(Special_keyboard); // Registra a função para tratamento das teclas NÂO ASCII
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  printf("\nTestando... \n");
  return 0;
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
  //DesenhaTexto("Exemplo de texto para a atividade 2");

  //glBegin(GL_POINTS);
  //glBegin(GL_LINES);
  //glBegin(GL_LINE_STRIP);
  //glBegin(GL_LINE_LOOP);

  // Cria o terreno
  glColor3ub(67, 79, 23);
  glBegin(GL_QUADS);
    glVertex2d(min, min);
    glVertex2d(max, min);
    glColor3ub(74, 90, 36);
    glVertex2d(max, 1);
    glVertex2d(min, 1);
  glEnd();

  // Cria uma arvóre
  // Tronco
  glColor3ub(85, 89, 48);
  glBegin(GL_QUADS);
    glVertex2d(-4, -4);
    glVertex2d(-4, -3);
    glVertex2d(-3.95, -3);
    glVertex2d(-3.95, -4);
  glEnd();

  // Galhos
  glLineWidth(2.0);
  glBegin(GL_LINES);
    for (int c = 0; c <= 10; c++){
      glVertex2d(-3.975, -3.1);
      glVertex2d(-4.5 + c *0.1, -2.5);
    }
  glEnd();

  // Folhas
  glColor3ub(33, 40, 15);
  glBegin(GL_POLYGON);
    glVertex2d(-4.5, -2.5);
    glVertex2d(-4.25, -2.3);
    glVertex2d(-3.75, -2.3);
    glVertex2d(-3.5, -2.5);
  glEnd();

  // Cria a lua
  glColor3ub(179, 229, 226);
  glBegin(GL_TRIANGLE_FAN);
      glVertex2d(-3, 3.5); // Centro do círculo
      double raio = sqrt(0.5); // Raio do círculo
      for (int i = 0; i <= 100; i++) {
          double ang = 2.0 * M_PI * i / 100; // Ângulo atual
          double x = raio * cos(ang); // Coordenada x
          double y = raio * sin(ang); // Coordenada y
          glVertex2d(-3 + x, 3.5 + y); // Adiciona o vértice
      }
  glEnd();

  // Crateras na lua
  glColor3ub(59, 93, 120);
  glBegin(GL_TRIANGLE_FAN);
      glVertex2d(-3.25, 3.5); // Centro do círculo
      raio = sqrt(0.01); // Raio do círculo
      for (int i = 0; i <= 100; i++) {
          double ang = 2.0 * M_PI * i / 100; // Ângulo atual
          double x = raio * cos(ang); // Coordenada x
          double y = raio * sin(ang); // Coordenada y
          glVertex2d(-3.25 + x, 3.5 + y); // Adiciona o vértice
      }
  glEnd();

  //glBegin(GL_QUAD_STRIP);
  //glBegin(GL_TRIANGLES);
  //glBegin(GL_TRIANGLE_STRIP);
  //glBegin(GL_TRIANGLE_FAN);
  /*glBegin(GL_POLYGON); // toda função começa com um begin
     glColor3ub (R, G, B); // função que muda a cor
    glVertex2f(-1,0.0); // criar um ponto
    glColor3ub (100,100, 100);
    glVertex2f(-1,1);
    glColor3ub (200,200, 200);
    glVertex2f(1,1);
    glColor3ub (255, 255, 255);
    glVertex2f(1,0);
  glEnd(); // termina com um end

  glBegin(GL_POINT);
    glPointSize(40.0f);
    glColor3ub (255, 0, 255);
    glVertex2f(-0.5,0.5);
  glEnd(); */



  glFlush(); ////Executa os comandos OpenGL para renderização
}

void keyboard(unsigned char key, int x, int y){
  printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",key);
  switch (key) {
    case 27: exit(0);
    case 32: R = 0; G = 0; B = 0;
            glutPostRedisplay();
    break;
  }
}

void Special_keyboard(GLint tecla, int x, int y) {
  switch (tecla) { // GLUT_KEY_RIGHT GLUT_KEY_DOWN GLUT_KEY_PAGE_UP GLUT_KEY_PAGE_DOWN GLUT_KEY_F1...
    case GLUT_KEY_F12: R = 0; G = 200; B = 200;
        glutPostRedisplay();
         break;
    case GLUT_KEY_F10: R = 0; G = 100; B = 200;
     glutPostRedisplay();
      break;
  }
}

void DesenhaTexto(char *string) {
  	glColor3ub(150,200,250);
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(-0.4,-0.4);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
	glColor3ub(255,255,255);
}