#include <GL/glut.h>
#include <cmath>

const float PI = 3.1416f;


void drawR2D2Head() {
    glColor3f(0.8f, 0.8f, 0.8f); // Cor da cabeça do R2-D2 (Cinza claro)
  
    
    GLdouble eqn[4] = {0.0, -1.0, 0.0, 0.0}; 
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
  
    glutSolidSphere(0.5, 100, 100); 
  
    glDisable(GL_CLIP_PLANE0); 
}

void drawR2D2Eye() {
    glColor3f(0.0f, 0.0f, 0.0f); // Cor do olho do R2-D2 (Preto)
  
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.4f); // Posição do olho em relação à cabeça
    glutSolidSphere(0.08, 50, 50); // Desenha a esfera do olho
    glPopMatrix();
}

void drawR2D2Body() {    
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.3f, 0.3f, 0.8f); // Cor do corpo do R2-D2 (Azul)
 
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f); // Posiciona o cilindro na parte inferior da cabeça
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona o cilindro em torno do eixo X
    gluCylinder(quad, 0.5f, 0.5f, 1.0f, 50, 50); // Draw cylinder
    glPopMatrix();
    
    gluDeleteQuadric(quad);
}
void drawR2D2Arm() {
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.3f, 0.3f, 0.8f); // Azul

    // Desenha o braço
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona segundo o eixo X
    gluCylinder(quad, 0.11f, 0.11f, 1.21f, 20, 20); // Desenha um cilindro
    glPopMatrix();

    // Desenha o trapézio para simular a mão
    glPushMatrix();
    glTranslatef(0.0f, -1.25f, 0.6f); // Move para a extremidade do cilindro
    glBegin(GL_QUADS);
    glVertex3f(-0.1f, 0.1f, 0.0f); // Vértice superior esquerdo
    glVertex3f(0.17f, 0.1f, 0.0f);  // Vértice superior direito
    glVertex3f(0.15f, -0.1f, 0.0f); // Vértice inferior direito
    glVertex3f(-0.15f, -0.1f, 0.0f); // Vértice inferior esquerdo
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

    glPushMatrix();
    glTranslatef(0.8f, 0.6f, -0.9f); // Posição do braço direito
    drawR2D2Arm();
    glPopMatrix();

    // Desenhar braço esquerdo
    glPushMatrix();
    glTranslatef(-0.8f, 0.6f, -0.9f); // Posição do braço esquerdo
    drawR2D2Arm();
    glPopMatrix();

    glutSwapBuffers();
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
    glutMainLoop();
    return 0;
}
