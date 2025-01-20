#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int largura=1024, altura=768;
GLdouble a[3]={0, 7, 10}; // Matriz da posição da câmera (x, y, z)

// Utilizando coordenadas cilindricas (obrigado afonso :D)
GLdouble r = 10; // Raio da esfera
GLdouble theta; // Ângulo da câmera em relação a x, em radianos

GLfloat const luzAmbiente[] = {0.4, 0.4, 0.4, 1.0};
GLfloat const luzDifusa[] = {0.5, 0.5, 0.5, 1.0};
GLfloat posicaoLuz[] = {10.0, 10.0, 10.0, 1.0};

void up(void);
void Iniciar();
void Mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void atualizarCamera();
void criaCilindro(double x0, double z0, double y0, double y1, double raio);
void criaFace(double x0, double y0, double z0, double scale, double angx, double angy);
void criaCubo(double x0, double y0, double z0, double scale, double angx, double angy);
void criaPrismaTriangular(double x0, double y0, double z0, double scalex, double scaley, double scalez, double angx, double angy);
void criaParalelepipedo(double x0, double y0, double z0, double scalex, double scaley, double scalez, double angx, double angy);
void criaElipsoide(double x0, double y0, double z0, double rx, double ry, double rz);
void criaBaloes(double x0, double y0, double z0, double raioEsfera);


int main(int argc, char** argv) {
   theta = M_PI / 2;
   glutInit(&argc, argv);
   //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize(largura, altura);
   glutInitWindowPosition(1367, 0);
   glutCreateWindow("Atividade 5");
   glClearColor(0.429, 0.708, 0.822, 0.0);
   glutDisplayFunc(up);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}

void Iniciar() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(a[0], a[1], a[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,largura/altura,1, 30);
}

void up(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   // glClear(GL_COLOR_BUFFER_BIT);
    Iniciar();
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LINE_SMOOTH); 
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Ativar iluminação
    glEnable(GL_LIGHTING);

    // Configuração da luz 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat[]){1.0, 1.0, 1.0, 1.0}); // Reflexo especular (brilho)
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glEnable(GL_LIGHT0);

    // Ativar materiais
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); // Configurar cores como ambiente e difusa
    glEnable(GL_NORMALIZE); // Normalizar as normais

    glBegin(GL_LINES); // Eixos cartesianos
        // Eixo x
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 0.0f);
        
        // Eixo y (z no cálculo)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 5.0f, 0.0f);

        // Eixo z (y no cálculo)
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();

    // Cor ao redor
    glColor3ub(135, 206, 235);
    criaCilindro(0, 0, 0, 10, 10);

    // Base da casa
    glColor3ub(238, 232, 109);
    criaCubo(0, 0.5, -0.1, 0.5, 0, 0);

    // Telhado
    glColor3ub(139, 69, 19);
    criaPrismaTriangular(0, 1, 0, 0.6, 0.6, 0.6, 0, 90);

    glColor3ub(0, 46, 56);
    criaPrismaTriangular(0.2, 1, 0, 0.3, 0.6, 0.6, 0, 0);

    // Chaminé
    glColor3ub(70, 46, 56);
    criaParalelepipedo(-0.1, 1.4, 0.1, 0.05, 0.2, 0.05, 0, 0);


    //Balões
    criaBaloes(-0.1, 3.4, 0.1, 5.5);
    criaBaloes(-0.1, 3.2, 0.1, 5.2);
    criaBaloes(-0.1, 3, 0.1, 3.8);

    // Linhas dos balões
    glColor3ub(255, 255, 255);
    glLineWidth(0.1f);
    glBegin(GL_LINES);
        double x, z;
        for (double raio = 0.1; raio < 5.0; raio += 1){
            for (double angulo = 0.0; angulo <= 2 * M_PI; angulo += M_PI / 20) {
                x = raio * cos(angulo) / 10;
                z = raio * sin(angulo) / 10;
                glVertex3f(-0.1, 1.4, 0.1);
                glVertex3f(-0.1 + x , 3.0, 0.1 + z);
            }
        }
    glEnd();



    //Janela
    glColor3ub(121, 85, 72);
    //criaFace2(0.1,0.2,0.5,1.2,0,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScaled(0.35, 0.6, 1);
        criaCubo(0.56,2.0,0.31,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glScaled(0.47, 0.87, 1);
        glColor3ub(117, 232, 111);
        criaCubo(0.40,0.55,0.320,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(121, 85, 72);
        glScaled(0.35, 0.7, 1);
        criaCubo(0.56,0.6,0.321,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(117, 232, 111);
        glScaled(0.35, 0.88, 1);
        criaCubo(0.0,0.54,0.270,0.29,0.0,-20.0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(121, 85, 72);
        glScaled(0.33, 0.7, 1);
        criaCubo(0.0,0.61,0.280,0.29,0.0,-20.0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.26, 0.54, 1);
        criaCubo(-0.1,0.8,0.310,0.29,0.0,-20.0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(117, 232, 111);
        glScaled(0.35, 0.88, 1);
        criaCubo(1.0,0.54,0.64,0.29,0.0,20.0);
    glPopMatrix();


    glPushMatrix();
        glColor3ub(70, 46, 56);
        glScaled(0.25, 0.5, 1);
        criaCubo(0.78,2.4,0.32,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(70, 46, 56);
        glScaled(0.25, 0.54, 1);
        criaCubo(0.78,0.8,0.322,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.2, 0.2, 1);
        criaCubo(0.97,1.8,0.323,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.2, 0.2, 1);
        criaCubo(0.97,2.5,0.323,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.2, 0.2, 1);
        criaCubo(0.97,5.7,0.322,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.2, 0.2, 1);
        criaCubo(0.97,6.3,0.322,0.3,0,0);
    glPopMatrix();



    // Detalhes da casa
    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.495,0.0,0.41);
        glVertex3f(-0.495,1,0.41);
    glEnd();

    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.25,0.0,0.41);
        glVertex3f(-0.25,1,0.41);
    glEnd();

    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.42,0.58,0.41);
        glVertex3f(-0.42,0.75,0.41);
    glEnd();

    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.36,0.58,0.41);
        glVertex3f(-0.36,0.75,0.41);
    glEnd();

    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.3,0.58,0.41);
        glVertex3f(-0.3,0.75,0.41);
    glEnd();

    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.485,0.75,0.41);
        glVertex3f(-0.25,0.75,0.41);
    glEnd();

    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.485,0.58,0.41);
        glVertex3f(-0.25,0.58,0.41);
    glEnd();
    
    for(float i=0 ; i<0.7;i+=0.06){
    glColor3f(0.65f, 0.32f, 0.17f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.18+i,0.00,0.41);
        glVertex3f(-0.18+i,0.17,0.41);
    glEnd();
    }

    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.25,0.17,0.41);
        glVertex3f(0.5,0.17,0.41);
    glEnd();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.38, 0.33, 1);
        glColor3ub(27, 78, 133);
        criaCubo(-0.965,2.75,0.108,0.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(121, 85, 72);
        glScaled(0.29, 0.68, 1);
        criaCubo(1.2,0.62,0.74,0.29,0.0,20.0);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 255, 255);
        glScaled(0.21, 0.51, 1);
        criaCubo(1.8,0.8,0.94,0.29,0.0,20.0);
    glPopMatrix();

    // Porta
    glColor3ub(59, 44, 22);
        glPushMatrix();
        glScaled(0.23, 0.8, 1);
        criaCubo(-1.6,0.3,0.12,0.3,0,0);
    glPopMatrix();



    glFlush();
}


void criaCilindro(double x0, double z0, double y0,double y1, double raio) {
    double angulo;
    double x1, z1;
    glBegin(GL_QUAD_STRIP);
    for (angulo = 0.0; angulo <= 2 * M_PI; angulo += M_PI / 20) {
        x1 = x0 + raio * cos(angulo);
        z1 = y0 + raio * sin(angulo);
        glVertex3d(x1, y0, z1);
        glVertex3d(x1, y1, z1);
    }
    glEnd();
}

void criaFace(double x0, double y0, double z0, double scale, double angx, double angy) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslated(x0, y0, z0);
        glRotated(angx, 1, 0, 0);
        glRotated(angy, 0, 1, 0);
        glScaled(scale, scale, scale);
        glBegin(GL_QUADS);
            glVertex3d(-1, 1, 0);
            glVertex3d(1, 1, 0);
            glVertex3d(1, -1, 0);
            glVertex3d(-1, -1, 0);
        glEnd();
    glPopMatrix();
}


void criaElipsoide(double x0, double y0, double z0, double rx, double ry, double rz) {
    int i, j;
    int numSlices = 40; // Número de fatias ao longo do eixo longitudinal
    int numStacks = 40; // Número de fatias ao longo do eixo latitudinal

    for (i = 0; i <= numStacks; ++i) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / numStacks);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / numStacks);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= numSlices; ++j) {
            double lng = 2 * M_PI * (double) (j - 1) / numSlices;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3d(x * zr0, y * zr0, z0);
            glVertex3d(x0 + rx * x * zr0, y0 + ry * y * zr0, z0 * rz);

            glNormal3d(x * zr1, y * zr1, z1);
            glVertex3d(x0 + rx * x * zr1, y0 + ry * y * zr1, z1 * rz);
        }
        glEnd();
    }
}



void criaCubo(double x0, double y0, double z0, double scale, double angx, double angy){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotated(angx, 1, 0, 0);
        glRotated(angy, 0, 1, 0);
        criaFace(x0, y0, z0 + scale, scale, 0, 0);
        criaFace(x0, y0, z0 - scale, scale, 0, 180);
        criaFace(x0, y0 + scale, z0, scale, 90, 0);
        criaFace(x0, y0 - scale, z0, scale, -90, 0);
        criaFace(x0 + scale, y0, z0, scale, 0, +90);
        criaFace(x0 - scale, y0, z0, scale, 0, -90);
    glPopMatrix();
}

void criaPrismaTriangular(double x0, double y0, double z0, double scalex, double scaley, double scalez, double angx, double angy) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslated(x0, y0, z0);
        glRotated(angx, 1, 0, 0);
        glRotated(angy, 0, 1, 0);
        glScaled(scalex, scaley, scalez);
        glBegin(GL_TRIANGLES);
            // Frente
            glVertex3d(-1, 0, 1);
            glVertex3d(0, 1, 1);
            glVertex3d(1, 0, 1);
            // Fundo
            glVertex3d(-1, 0, -1);
            glVertex3d(0, 1, -1);
            glVertex3d(1, 0, -1);
        glEnd();
        glBegin(GL_QUADS);
            // Lado esquerdo
            glVertex3d(-1, 0, 1);
            glVertex3d(-1, 0, -1);
            glVertex3d(0, 1, -1);
            glVertex3d(0, 1, 1);
            // Lado direito
            glVertex3d(1, 0, 1);
            glVertex3d(1, 0, -1);
            glVertex3d(0, 1, -1);
            glVertex3d(0, 1, 1);
        glEnd();
    glPopMatrix();
}

void criaParalelepipedo(double x0, double y0, double z0, double scalex, double scaley, double scalez, double angx, double angy) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslated(x0, y0, z0);
        glRotated(angx, 1, 0, 0);
        glRotated(angy, 0, 1, 0);
        glScaled(scalex, scaley, scalez);
        glBegin(GL_QUADS);
            // Frente
            glVertex3d(-1, 2, 1);
            glVertex3d(1, 2, 1);
            glVertex3d(1, 0, 1);
            glVertex3d(-1, 0, 1);
            // Fundo
            glVertex3d(-1, 2, -1);
            glVertex3d(1, 2, -1);
            glVertex3d(1, 0, -1);
            glVertex3d(-1, 0, -1);
            // Lado esquerdo
            glVertex3d(-1, 2, 1);
            glVertex3d(-1, 2, -1);
            glVertex3d(-1, 0, -1);
            glVertex3d(-1, 0, 1);
            // Lado direito
            glVertex3d(1, 2, 1);
            glVertex3d(1, 2, -1);
            glVertex3d(1, 0, -1);
            glVertex3d(1, 0, 1);
        glEnd();
        
    glPopMatrix();
}


// Utilizando agora o conceito de coordenadas esféricas, obrigado afonso mais uma vez kkkkkkkk
void criaBaloes(double x0, double y0, double z0, double raioEsfera) {
    int subdivisoesTheta = 38; // Número de divisões em ângulos verticais (latitude)
    int subdivisoesPhi = 46;  // Número de divisões em ângulos horizontais (longitude)
    srand(1);

    // Cores dos balões
    int cores[8][3] = {
        {135, 206, 250}, // Azul Claro
        {255, 69, 58},   // Vermelho Vivo
        {255, 223, 0},   // Amarelo Brilhante
        {50, 205, 50},   // Verde Lima
        {218, 112, 214}, // Roxo Lavanda
        {255, 140, 0},   // Laranja
        {255, 105, 180}, // Rosa
        {64, 224, 208}   // Ciano
    };
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslated(x0, y0, z0); 

    // Percorre as subdivisões da esfera
    for (int i = 0; i <= subdivisoesTheta; i +=2) {
        double theta = i * M_PI / subdivisoesTheta; // Ângulo de latitude (0 a π)

        for (int j = 0; j < subdivisoesPhi; j +=2) {
            double phi = j * 2 * M_PI / subdivisoesPhi; // Ângulo de longitude (0 a 2π)

            // Converte coordenadas esféricas para cartesianas
            double x = raioEsfera * sin(theta) * cos(phi);
            double y = raioEsfera * cos(theta);
            double z = raioEsfera * sin(theta) * sin(phi);

            // Desenha o balão (elipsoide) na posição calculada
            glPushMatrix();
                glScaled(0.1, 0.1, 0.1); // Escala do balão
                glTranslated(x, y, z); // Translada para a posição na esfera
                int cor = rand() % 8; // Escolhe uma cor aleatória
                glColor3ub(cores[cor][0], cores[cor][1], cores[cor][2]); // Define a cor do balão
                criaElipsoide(0, 0, 0, 0.5, 1, 0.5); // Cria a elipsoide
            glPopMatrix();
        }
    }

    glPopMatrix();
}



void Mouse(int button, int state, int x, int y) {
     // Aqui o ângulo incrementa ou decrementa diferente do que seria no geogebra
    // Porque o eixo x é invertido o sinal do que seria no cálculo, aqui ao ir pra "direita" de z, x aumenta
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        theta += 0.1;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
       theta -= 0.1;
    }
    atualizarCamera();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
  printf("*** Tratamento de teclas comuns\n");
	printf(">>> Tecla pressionada: %c\n",key);
  switch (key) {
    // Aqui o ângulo incrementa ou decrementa diferente do que seria no geogebra
    // Porque o eixo x é invertido o sinal do que seria no cálculo, aqui ao ir pra "direita" de z, x aumenta
    case 'a':
            theta += 0.1;
            break;
    case 'd':
            theta -= 0.1;
            break;
    case 'w':
            a[1] += 0.1;
            break;
    case 's':
            a[1] -= 0.1;
            break;
    case 'o':
            r += 0.1;
            break;
    case 'i':
            r -= 0.1;
            break;
    }


    atualizarCamera();
    glutPostRedisplay();
}

void atualizarCamera() {
    a[0] = r * cos(theta);
    a[2] = r * sin(theta);
}