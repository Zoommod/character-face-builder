#include <GL/glut.h>
#include <cmath>

const float PI = 3.1416f;

int olhos = 0;

// Draw half sphere for the R2-D2's head
void drawR2D2Head() {
    glColor3f(0.99f, 0.99f, 0.99f); // Cor da cabeça do R2-D2 (Cinza claro)
  
    // Enable clipping plane to cut the sphere in half
    GLdouble eqn[4] = {0.0, -1.0, 0.0, 0.0}; // Plane equation to clip lower half
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
  
    glutSolidSphere(0.5, 100, 100); // Draw half sphere
  
    glDisable(GL_CLIP_PLANE0); // Disable clipping plane
}

void drawR2D2Eye() {
    switch (olhos){
    case 0:
        glColor3f(0.0f, 0.0f, 0.0f); // Cor do olho do R2-D2 (Preto)
        glPushMatrix();
        glTranslatef(0.0f, 0.75f, 0.4f); // Posição do olho em relação à cabeça
        glutSolidSphere(0.08, 50, 50); // Desenha a esfera do olho
        glPopMatrix();
        break;
    }
}

void drawR2D2BodyDetail(GLUquadric* quad) {
    // Desenha um painel retangular
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.2f, 0.01f); // Canto superior esquerdo
    glVertex3f(0.2f, 0.2f, 0.01f);  // Canto superior direito
    glVertex3f(0.2f, -0.2f, 0.01f); // Canto inferior direito
    glVertex3f(-0.2f, -0.2f, 0.01f); // Canto inferior esquerdo
    glEnd();
}

void drawR2D2Body() {    
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.8f, 0.8f, 0.8f); // Cor do corpo do R2-D2 (Azul)

    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f); // Posiciona o cilindro na parte inferior da cabeça
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona o cilindro em torno do eixo X
    gluCylinder(quad, 0.5f, 0.5f, 1.0f, 50, 50); // Desenha o cilindro
    drawR2D2BodyDetail(quad); // Chama a função para desenhar os detalhes
    glPopMatrix();

    // Desenha o retângulo maior no X e menor no Y
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o retângulo
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.46f, 0.0f); // Canto inferior esquerdo
    glVertex3f(0.2f, 0.46f, 0.0f);  // Canto inferior direito
    glVertex3f(0.2f, 0.5f, 0.0f);   // Canto superior direito
    glVertex3f(-0.2f, 0.5f, 0.0f);  // Canto superior esquerdo
    glEnd();

    // Desenha o losango na ponta esquerda do retângulo
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o losango
    glBegin(GL_POLYGON);
    glVertex3f(-0.2f, 0.485f, 0.0f);  // Centro direito do losango (conectado ao retângulo)
    glVertex3f(-0.22f, 0.44f, 0.0f); // Canto inferior do losango
    glVertex3f(-0.24f, 0.485f, 0.0f);  // Centro esquerdo do losango
    glVertex3f(-0.22f, 0.52f, 0.0f);  // Canto superior do losango
    glEnd();
    glPopMatrix();

    // Desenha o retângulo abaixo do anterior
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o retângulo
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.4f, 0.0f); // Canto inferior esquerdo (ajustado para baixo)
    glVertex3f(0.2f, 0.4f, 0.0f);  // Canto inferior direito (ajustado para baixo)
    glVertex3f(0.2f, 0.44f, 0.0f);  // Canto superior direito (ajustado para baixo)
    glVertex3f(-0.2f, 0.44f, 0.0f); // Canto superior esquerdo (ajustado para baixo)
    glEnd();

    // Desenha o losango na ponta direita do retângulo
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o losango
    glBegin(GL_POLYGON);
    glVertex3f(0.2f, 0.423f, 0.0f);  // Centro esquerdo do losango (conectado ao retângulo)
    glVertex3f(0.22f, 0.38f, 0.0f); // Canto inferior do losango
    glVertex3f(0.24f, 0.423f, 0.0f);  // Centro direito do losango
    glVertex3f(0.22f, 0.46f, 0.0f);  // Canto superior do losango
    glEnd();
    glPopMatrix();

        // Desenha um novo retângulo abaixo com espaço e dimensões ajustadas
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o retângulo
    glBegin(GL_QUADS);
    glVertex3f(-0.15f, -0.3f, 0.0f); // Canto inferior esquerdo (mais para cima e para dentro)
    glVertex3f(0.15f, -0.3f, 0.0f);  // Canto inferior direito (mais para cima e para dentro)
    glVertex3f(0.15f, 0.34f, 0.0f);  // Canto superior direito (mais para cima e para dentro)
    glVertex3f(-0.15f, 0.34f, 0.0f); // Canto superior esquerdo (mais para cima e para dentro)
    glEnd();
    glPopMatrix();

    glPushMatrix();
    // Desenha o círculo inferior e os traços do jogo da velha
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza para os círculos
    glTranslatef(0.0f, -0.1f, 0.0f); // Posiciona o círculo inferior
    gluDisk(quad, 0.0f, 0.1f, 30, 1); // Desenha o círculo inferior

    // Traços do jogo da velha centralizados para o círculo inferior
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para os traços
    glBegin(GL_LINES);
    glVertex3f(-0.05f, 0.0f, 0.01f); // Linha horizontal inferior
    glVertex3f(0.05f, 0.0f, 0.01f);
    glVertex3f(-0.05f, 0.05f, 0.01f); // Linha horizontal superior
    glVertex3f(0.05f, 0.05f, 0.01f);

    glVertex3f(0.0f, -0.05f, 0.01f); // Linha vertical esquerda
    glVertex3f(0.0f, 0.05f, 0.01f);
    glVertex3f(0.05f, -0.05f, 0.01f); // Linha vertical direita
    glVertex3f(0.05f, 0.05f, 0.01f);
    glEnd();

    glPopMatrix();
    // Desenha o círculo superior e os traços do jogo da velha
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza para os círculos
    glTranslatef(0.0f, 0.15f, 0.0f); // Posiciona o círculo superior
    gluDisk(quad, 0.0f, 0.1f, 30, 1); // Desenha o círculo superior

    // Traços do jogo da velha centralizados para o círculo superior
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para os traços
    glBegin(GL_LINES);
    glVertex3f(-0.05f, 0.0f, 0.01f); // Linha horizontal inferior
    glVertex3f(0.05f, 0.0f, 0.01f);
    glVertex3f(-0.05f, 0.05f, 0.01f); // Linha horizontal superior
    glVertex3f(0.05f, 0.05f, 0.01f);

    glVertex3f(0.0f, -0.05f, 0.01f); // Linha vertical esquerda
    glVertex3f(0.0f, 0.05f, 0.01f);
    glVertex3f(0.05f, -0.05f, 0.01f); // Linha vertical direita
    glVertex3f(0.05f, 0.05f, 0.01f);
    glEnd();
    glPopMatrix();
    glPopMatrix();
 
    // Desenha detalhe do retangular esquerdo
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Definindo a cor para cinza
    glBegin(GL_LINE_LOOP);  // Inicia o desenho da linha
    glVertex3f(-0.44f, -0.2f, 0.0f);  // Canto inferior direito espelhado
    glVertex3f(-0.25f, -0.2f, 0.0f);  // Canto inferior esquerdo espelhado
    glVertex3f(-0.25f, 0.5f, 0.0f);   // Canto superior esquerdo espelhado
    glVertex3f(-0.44f, 0.5f, 0.0f);   // Canto superior direito espelhado
    glEnd();  // Termina o desenho da linha
    glPopMatrix();

    // Desenha detalhe do retangular interno esquerdo
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.5f); // Definindo a cor azul
    glBegin(GL_QUADS);  // Inicia o desenho do retângulo
    glVertex3f(-0.42f, -0.18f, 0.01f);  // Canto inferior direito interno
    glVertex3f(-0.27f, -0.18f, 0.01f);  // Canto inferior esquerdo interno
    glVertex3f(-0.27f, 0.48f, 0.01f);   // Canto superior esquerdo interno
    glVertex3f(-0.42f, 0.48f, 0.01f);   // Canto superior direito interno
    glEnd();  // Termina o desenho do retângulo
    glPopMatrix();


    // Desenha detalhe do retangular direito
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Definindo a cor para cinza
    glBegin(GL_LINE_LOOP);  // Inicia o desenho da linha
    glVertex3f(0.25f, -0.2f, 0.0f);  // Canto inferior esquerdo
    glVertex3f(0.44f, -0.2f, 0.0f);   // Canto inferior direito
    glVertex3f(0.44f, 0.5f, 0.0f);    // Canto superior direito
    glVertex3f(0.25f, 0.5f, 0.0f);   // Canto superior esquerdo
    glEnd();  // Termina o desenho da linha
    glPopMatrix();

    // Desenha detalhe do retangular interno direito
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.5f); // Definindo a cor azul
    glBegin(GL_QUADS);  // Inicia o desenho do retângulo
    glVertex3f(0.27f, -0.18f, 0.01f);  // Canto inferior esquerdo interno
    glVertex3f(0.42f, -0.18f, 0.01f);  // Canto inferior direito interno
    glVertex3f(0.42f, 0.48f, 0.01f);   // Canto superior direito interno
    glVertex3f(0.27f, 0.48f, 0.01f);   // Canto superior esquerdo interno
    glEnd();  // Termina o desenho do retângulo
    glPopMatrix();


    gluDeleteQuadric(quad);
}


void drawR2D2Arm() {
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.8f, 0.8f, 0.8f); // Azul

    // Desenha o braço
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.13f, 0.13f, 1.21f, 20, 20);
    glPopMatrix();

    // Desenha o trapézio invertido ajustado
    glPushMatrix();
    glTranslatef(0.01f, -1.46f, 0.6f); // Ajusta a posição para alinhar com o final do braço
    glBegin(GL_QUADS);
    // Coordenadas ajustadas do trapézio
    glVertex3f(-0.19f, 0.3f, -0.1f); // Esticado para a esquerda
    glVertex3f(0.19f, 0.3f, -0.1f);  // Esticado para a direita
    glVertex3f(0.4f, 0.1f, 0.0f);
    glVertex3f(-0.4f, 0.1f, 0.0f);
    glEnd();
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 0.0, 5.0,  // posição da câmera
              0.0, 0.0, 0.0,  // para onde a câmera está olhando
              0.0, 1.0, 0.0); // direção para cima da câmera

    // Desenha a cabeça do R2-D2
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);
    drawR2D2Head();
    glPopMatrix();

    // Desenha o corpo do R2-D2
    drawR2D2Body();
    drawR2D2Eye();

    // Desenhar braço esquerdo
    glPushMatrix();
    glTranslatef(-0.8f, 0.6f, -0.9f); // Posição do braço esquerdo
    drawR2D2Arm(); // Especificar que é o braço esquerdo
    glPopMatrix();

    // Desenhar braço direito
    glPushMatrix();
    glTranslatef(0.8f, 0.6f, -0.9f); // Posição do braço direito
    drawR2D2Arm(); // Especificar que é o braço direito 
    glPopMatrix();

    glutSwapBuffers();
}

// Função callback de teclado
void keyboard(unsigned char key, int x, int y) {
    char keys[] = {'1', '2', '3', '4', '5', '6', 'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
    int* indices[] = {&olhos, &olhos, &olhos, &olhos, &olhos, &olhos};

    for (int i = 0; i < sizeof(keys)/sizeof(char); i++) {
        if (key == keys[i]) {
            *indices[i] = i % 6;
            break;
        }
    }

    if (key == 27) { // Tecla ESC para sair
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("R2-D2");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
