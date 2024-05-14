#include <GL/glut.h>
#include <cmath>

const float PI = 3.1416f;

int olhos = 0;
int chapeus = 0;
int corpo = 0;

void drawTriangle(float centerX, float centerY, float size, bool inverted) {
    float height = size * sqrt(3) / 2; // Altura do triângulo equilátero
    // Define a cor da estrela (RGB)
    glColor3f(1.0, 1.0, 0.0); // Amarelo
    glBegin(GL_TRIANGLES);
    if (!inverted) {
        glVertex2f(centerX - size / 2, centerY - height / 3);
        glVertex2f(centerX + size / 2, centerY - height / 3);
        glVertex2f(centerX, centerY + height * 2 / 3);
    } else {
        glVertex2f(centerX - size / 2, centerY + height / 3);
        glVertex2f(centerX + size / 2, centerY + height / 3);
        glVertex2f(centerX, centerY - height * 2 / 3);
    }
    glEnd();
}

void drawStarOfDavid(float centerX, float centerY, float size) {
    // Ajuste o valor de 'size' para alterar o tamanho da estrela
    size = size / 7; // Reduz o tamanho pela metade

    // Ajuste o valor de 'centerY' para deslocar a estrela para baixo
    centerY -= size; // Desloca a estrela para baixo pelo valor de 'size'

    // Desenha o triângulo com a ponta para cima
    drawTriangle(centerX, centerY, size, false);

    // Desenha o triângulo com a ponta para baixo
    drawTriangle(centerX, centerY, size, true);

    // Desenha a esfera no centro da estrela
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(centerX, centerY, 0); // Move o centro da esfera para o centro da estrela
    // Define a cor da esfera (RGB)
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    glutSolidSphere(size / 3, 20, 20); // Desenha a esfera com um terço do tamanho da estrela
    glPopMatrix(); // Restaura a matriz de transformação anterior
}

void drawR2D2Head() {
    GLdouble eqn[4];
    switch (chapeus) {
    case 0:
        glColor3f(0.99f, 0.99f, 0.99f); // Cor da cabeça do R2-D2 (Cinza claro)
        // Enable clipping plane to cut the sphere in half
        eqn[0] = 0.0;
        eqn[1] = -1.0;
        eqn[2] = 0.0;
        eqn[3] = 0.0; // Plane equation to clip lower half
        glClipPlane(GL_CLIP_PLANE0, eqn);
        glEnable(GL_CLIP_PLANE0);
        glutSolidSphere(0.5, 100, 100); // Draw half sphere
        glDisable(GL_CLIP_PLANE0); // Disable clipping plane
        break;
    case 1:
        glColor3f(0.99f, 0.99f, 0.99f); // Cor da cabeça do R2-D2 (Cinza claro)
        // Enable clipping plane to cut the sphere in half
        eqn[0] = 0.0;
        eqn[1] = -1.0;
        eqn[2] = 0.0;
        eqn[3] = 0.0; // Reset plane equation to clip lower half
        glClipPlane(GL_CLIP_PLANE0, eqn);
        glEnable(GL_CLIP_PLANE0);
        glutSolidSphere(0.5, 100, 100); // Draw half sphere
        glDisable(GL_CLIP_PLANE0); // Disable clipping plane

        // Desenhar o chapéu de Papai Noel
        glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, -1.2f); // Vértice inferior
        glVertex2f(-0.2f, -0.6f); // Vértice superior esquerdo
        glVertex2f(0.2f, -0.6f); // Vértice superior direito
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f); // Cor branca
        glBegin(GL_QUADS);
        glVertex2f(0.2f, -0.6f); // Vértice inferior esquerdo
        glVertex2f(0.2f, -0.5f); // Vértice superior esquerdo
        glVertex2f(-0.2f, -0.5f); // Vértice superior direito
        glVertex2f(-0.2f, -0.6f); // Vértice inferior direito
        glEnd();
        glTranslatef(0.0f, -1.3f, -0.1f); // Mover para cima para desenhar o pompom
        glColor3f(1.0f, 1.0f, 1.0f); // Branco
        glutSolidSphere(0.05, 100, 100); // Desenhar o pompom do chapéu
        break;
    case 2:
        glColor3f(0.99f, 0.99f, 0.99f); // Cor da cabeça do R2-D2 (Cinza claro)
        // Enable clipping plane to cut the sphere in half
        eqn[0] = 0.0;
        eqn[1] = -1.0;
        eqn[2] = 0.0;
        eqn[3] = 0.0; // Reset plane equation to clip lower half
        glClipPlane(GL_CLIP_PLANE0, eqn);
        glEnable(GL_CLIP_PLANE0);
        glutSolidSphere(0.5, 100, 100); // Draw half sphere
        glDisable(GL_CLIP_PLANE0); // Disable clipping plane

             // Definir cores para os círculos interno e externo
        glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha para o círculo externo
        float outerRadius = 0.8f; // Raio do círculo externo

        glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o círculo interno
        float innerRadius = 0.5f; // Raio do círculo interno

        // Número de segmentos para desenhar os círculos
        int numSegments = 20;

        // Desenhar o círculo externo
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // Centro do círculo
        for (int i = 0; i <= numSegments; ++i) {
            float theta = 4.0f * 3.1415926f * float(i) / float(numSegments);
            float x = outerRadius * cosf(theta);
            float y = outerRadius * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();

        // Desenhar o círculo interno
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // Centro do círculo
        for (int i = 0; i <= numSegments; ++i) {
            float theta = 4.0f * 3.1415926f * float(i) / float(numSegments);
            float x = innerRadius * cosf(theta);
            float y = innerRadius * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();



    }
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
    case 1:
        glColor3f(0.0f, 0.0f, 0.0f); // Cor do olho (Preto)
        glPushMatrix();
        glTranslatef(-0.05f, 0.78f, 0.4f); // Posição do olho esquerdo em relação à cabeça
        glutSolidSphere(0.04, 50, 50); // Desenha a esfera do olho esquerdo
        glTranslatef(0.1f, 0.0f, 0.0f); // Mover para a posição do olho direito
        glutSolidSphere(0.04, 50, 50); // Desenha a esfera do olho direito
        glPopMatrix();
        // Desenha as sobrancelhas
        glColor3f(1.0f, 0.5f, 0.0f); // Cor da sobrancelha (Laranja)
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex3f(-0.1f, 0.82f, 0.41f); // Sobrancelha esquerda
        glVertex3f(-0.0f, 0.84f, 0.41f);
        glVertex3f(0.1f, 0.82f, 0.41f); // Sobrancelha direita
        glVertex3f(0.0f, 0.84f, 0.41f);
        glEnd();
        break;
    case 2:
        glColor3f(0.0f, 0.0f, 0.0f); // Cor do olho (Preto)
        glPushMatrix();
        glTranslatef(0.0f, 0.75f, 0.4f); // Posição do olho em relação à cabeça
        glutSolidSphere(0.08, 50, 50); // Desenha a esfera do olho
        glColor3f(1.0f, 1.0f, 1.0f); // Cor da pupila (Branco)
        glutSolidSphere(0.04, 50, 50); // Desenha a pupila
        // Desenha os cílios acima do olho
        glColor3f(0.0f, 0.0f, 0.9f); // Cor dos cílios (Preto)
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex3f(-0.1f, -0.03f, 0.41f); // Cílio esquerdo
        glVertex3f(-0.16f, 0.05f, 0.41f);
        glVertex3f(0.0f, 0.016f, 0.41f); // Cílio do meio
        glVertex3f(0.0f, 0.088f, 0.41f);
        glVertex3f(0.1f, -0.03f, 0.41f); // Cílio direito
        glVertex3f(0.16f, 0.05f, 0.41f);
        glEnd();
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
    switch (corpo){
    case 0:

        // Define a cor cinza para o retângulo
        glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza

        // Desenha o retângulo que conecta os braços ao corpo
        glPushMatrix();
        glTranslatef(0.0f, 0.4f, 0.0f); // Ajuste a posição conforme necessário
        glScalef(1.2f, 0.3f, 1.0f); // Ajuste a escala para ser maior no X e menor no Y
        glRectf(-0.5f, -0.1f, 0.5f, 0.1f); // Coordenadas para um retângulo centralizado
        glPopMatrix();

        glColor3f(0.8f, 0.8f, 0.8f); // Cor do corpo do R2-D2 Cinza fraco

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
        break;
    case 1:

    // Define a cor cinza para o retângulo
    glColor3f(0.5f, 0.5f, 0.5f); // Cor cinza

    // Desenha o retângulo que conecta os braços ao corpo
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f); // Ajuste a posição conforme necessário
    glScalef(1.2f, 0.3f, 1.0f); // Ajuste a escala para ser maior no X e menor no Y
    glRectf(-0.5f, -0.1f, 0.5f, 0.1f); // Coordenadas para um retângulo centralizado
    glPopMatrix();

    glColor3f(0.8f, 0.8f, 0.8f); // Cor do corpo do R2-D2 Cinza fraco

    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f); // Posiciona o cilindro na parte inferior da cabeça
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotaciona o cilindro em torno do eixo X
    gluCylinder(quad, 0.5f, 0.5f, 1.0f, 50, 50); // Desenha o cilindro
    drawR2D2BodyDetail(quad); // Chama a função para desenhar os detalhes
    glPopMatrix();

    

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde
    glVertex2f(0.1f, -0.1f); // Topo
    glVertex2f(0.1f, -0.05f); // Direita
    glVertex2f(0.51f, -0.44f); // Ponta Direita
    glVertex2f(-0.5f, 0.57f); // Ponta Esquerda
    glEnd();

    // Desenha o segundo losango, deslocado para baixo
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.77f, 0.0f); // Amarelo
    glVertex2f(0.1f, -0.1f); // 
    glVertex2f(0.5f, -0.44f); // Ponta Direita
    glVertex2f(-0.05f, -0.04f); // 
    glVertex2f(-0.5f, 0.55f); // Ponta Esquerda
    glEnd();

    // Desenha o terceiro losango, deslocado ainda mais para baixo
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde
    glVertex2f(0.14f, -0.19f); // Topo
    glVertex2f(0.5f, -0.45f); // Ponta Direita
    glVertex2f(0.05f, -0.19f); // Base
    glVertex2f(-0.5f, 0.54f); // Ponta Esquerda
    glEnd();

    drawStarOfDavid(-0.02f, 0.15f, 1.0f);

    

    break;
}  
}

void drawR2D2Arm() {
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza

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


// Função callback de teclado
void keyboard(unsigned char key, int x, int y) {
    char keys[] = {'1', '2', '3', '4', '5', '6', 'a', 's', 'd', 'f', 'g', 'h'};
    int* indices[] = {&olhos, &olhos, &olhos, &olhos, &olhos, &olhos,
                      &corpo, &corpo, &corpo, &corpo, &corpo, &corpo};

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

void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1: case GLUT_KEY_F2: case GLUT_KEY_F3: 
        case GLUT_KEY_F4: case GLUT_KEY_F5: case GLUT_KEY_F6: // Chapéus: F1...F6
            chapeus = key - GLUT_KEY_F1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void displayString(float x, float y, void *font, const char *string) {
    glColor3f(1.0f, 1.0f, 1.0f); // Define a cor do texto para branco
    glRasterPos2f(x, y); // Posiciona o texto na tela
    while (*string) {
        glutBitmapCharacter(font, *string++);
    }
}

void displayControls() {
    // Escreve as instruções na tela
    displayString(-1.99f, 1.9f, GLUT_BITMAP_HELVETICA_18, "Corpo: A, S, D, F, G, H");
    displayString(-1.99f, 1.8f, GLUT_BITMAP_HELVETICA_18, "Olhos: 1, 2, 3, 4, 5, 6");
    displayString(-1.99f, 1.7f, GLUT_BITMAP_HELVETICA_18, "Chapeu: F1, F2, F3, F4, F5, F6");
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

    displayControls();
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
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    return 0;
}