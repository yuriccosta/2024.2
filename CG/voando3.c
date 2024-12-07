// Vânia Cordeiro da Silva

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN -400
#define MAX 400

const GLfloat PI=3.1416;
GLfloat dx=0.0, dy=0.0;

void Desenho(void);
void Animar(int aux);
void Teclado(unsigned char tecla, int x, int y);
void AlteraDeslocamentos(void);

GLfloat aviao[17][2]= {
      50,80, 55,70, 55,55, 100,50, 100,40, 55,40, 55,15, 60,10, 60,0,
      40,0, 40,10, 45,15, 45,40, 0,40, 0,50, 45,55, 45,70 };
GLint desloc_x=0, desloc_y=0;

void Desenha_Bichinho() {
    glLineWidth(40.0);
    glBegin(GL_LINE_LOOP);
		glVertex2f( -1.0,1.0);
		glVertex2f( -0.5, 1.0);
		glVertex2f( -0.5, 0.5);
        glVertex2f( 0.5, 0.5);
        glVertex2f( 0.5, 1.0);
        glVertex2f( 1.0, 1.0);
        glVertex2f( 1.0, -1.0);
        glVertex2f( 0.5, -1.0);
        glVertex2f( 0.5, -0.5);
        glVertex2f( -0.5,-0.5);
        glVertex2f( -0.5,-1.0);
        glVertex2f( -1.0,-1.0);
    glEnd();
}

void Desenho(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(4.0);
  glColor3f (0.0,0.0,0.0);
  glBegin(GL_LINES);
    glVertex2f(MIN,0);
    glVertex2f(MAX,0);
    glVertex2f(0,MIN);
    glVertex2f(0,MAX);
  glEnd();
  glColor3ub(155, 155, 0);
  glPushMatrix();
    glTranslated(-50+dx,-50+dy,0);
    glScaled(30,30,1);
    Desenha_Bichinho();
  glPopMatrix();
  glColor3f (1.0,0.0,0.0);
  glBegin(GL_LINE_LOOP); //Delimitam os vértices de uma primitiva de desenho
    glVertex2f(aviao[0][0],aviao[0][1]); glVertex2f(aviao[1][0],aviao[1][1]);
    glVertex2f(aviao[2][0],aviao[2][1]); glVertex2f(aviao[3][0],aviao[3][1]);
    glVertex2f(aviao[4][0],aviao[4][1]); glVertex2f(aviao[5][0],aviao[5][1]);
    glVertex2f(aviao[6][0],aviao[6][1]); glVertex2f(aviao[7][0],aviao[7][1]);
    glVertex2f(aviao[8][0],aviao[8][1]); glVertex2f(aviao[9][0],aviao[9][1]);
    glVertex2f(aviao[10][0],aviao[10][1]);glVertex2f(aviao[11][0],aviao[11][1]);
    glVertex2f(aviao[12][0],aviao[12][1]);glVertex2f(aviao[13][0],aviao[13][1]);
    glVertex2f(aviao[14][0],aviao[14][1]);glVertex2f(aviao[15][0],aviao[15][1]);
    glVertex2f(aviao[16][0],aviao[16][1]);
  glEnd();
  glutSwapBuffers();
}

void Teclado_Especial(GLint tecla, int x, int y) {
  switch (tecla) { // GLUT_KEY_RIGHT GLUT_KEY_DOWN GLUT_KEY_PAGE_UP GLUT_KEY_PAGE_DOWN GLUT_KEY_F1...
  case GLUT_KEY_RIGHT:       //o programa deverá ser finalizado
              dx=dx+0.5;
             // glutPostRedisplay();
    break;
    case GLUT_KEY_LEFT:       //o programa deverá ser finalizado
              dx=dx-0.5;
             // glutPostRedisplay();
    break;
    case GLUT_KEY_UP:       //o programa deverá ser finalizado
              dy=dy+0.5;
            //  glutPostRedisplay();
    break;
    case GLUT_KEY_DOWN:       //o programa deverá ser finalizado
              dy=dy-0.5;
            //  glutPostRedisplay(); //Manda redesenhar na tela
    break;
   }
}

void Animar(int interacoes) { // Função de animação chamada pela TimerFunc
  int cont;
  double aux;
  aux = fmod(interacoes,10);
  if (aux == 0.0) AlteraDeslocamentos();
     for (cont=0;cont<17;cont++) {
         aviao[cont][0]=aviao[cont][0] + desloc_x;
         aviao[cont][1]=aviao[cont][1] + desloc_y;
  }
  glutPostRedisplay();
  interacoes=interacoes+1;
  glutTimerFunc(30,Animar,interacoes);
}

//Função de tratamento de eventos do teclado
void Teclado(unsigned char tecla, int x, int y){
  switch (tecla) { //quando a tecla ESC (keycode=27) for pressionada
    case 27:       //o programa deverá ser finalizado
         exit(0);
    break;
  }
}

void AlteraDeslocamentos(void) { // Decide os deslocamentos de forma pseudo-aleatória
  GLfloat aux1, aux2;
  aux1 = (GLfloat)rand();
  aux2 = (GLfloat)rand();
  if (aux1 > aux2) desloc_x = -1;
  else desloc_x = 1;
  aux1 = (GLfloat)rand();
  aux2 = (GLfloat)rand();
  if (aux1 > aux2) desloc_y = -1;
  else desloc_y = 1;
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (500, 500); //Dimensões da janela
  glutInitWindowPosition (50, 50);
  glutCreateWindow ("Voando 3"); //Cria uma janela e define seu título
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glOrtho (MIN, MAX, MIN, MAX, -1 ,1);
  glClear(GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(Desenho); //Chama a função de desenho
  glutKeyboardFunc(Teclado); //Trata eventos de teclado
  glutSpecialFunc(Teclado_Especial);
  glutTimerFunc(30,Animar,0); // Chama a função de call back de animação
  glutMainLoop(); //Inicia o loop de processamento de desenhos com GLUT
  return 0;
}
