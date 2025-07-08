// Autor: Gabriel Rosa Galdino - Atividade 7 - Computação Gráfica
// Data: 08/07/2025
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

int mouseXAnterior = 0;
int mouseYAnterior = 0;
int arrastando = 0;

int largura = 900, altura = 600;
float angulo = 0.0;
float raioCamera = 7.0; // distância da câmera
float alturaCamera = 2.0;

void DesenharEixos();
void TorreBase();
void TorreGrades(float zProfundidade);
void Plataforma();
void TopoInclinado();
void DesenharTorre();
void DesenharGradesTriangulo(float zFrente);
void DesenharLogoAvengers(float xOffset, float yOffset, float zOffset, float escala);
void EscreverTexto(float x, float y, float z, const char* texto);
void ArrastarMouse(int x, int y);
void Teclado(unsigned char key, int x, int y);
void TeclaEspecial(int key, int x, int y);
void Mouse(int botao, int estado, int x, int y);
void IniciarCamera();

// Eixos cartesianos
void DesenharEixos() {
    glBegin(GL_LINES);
    // Eixo X - azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // Eixo Y - vermelho
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.5f, 0.0f);

    // Eixo Z - verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
}

// Grades diagonais (amarelas)
void TorreGrades(float zProfundidade) {
    glColor3f(1.0f, 1.0f, 0.6f); // amarelo claro
    float y;
    for (y = 0.2f; y < 1.9f; y += 0.15f) {
        glBegin(GL_QUADS);
        glVertex3f(0.0f, y, zProfundidade);
        glVertex3f(0.2f, y - 0.05f, zProfundidade);
        glVertex3f(0.21f, y - 0.01f, zProfundidade);
        glVertex3f(0.01f, y + 0.04f, zProfundidade);
        glEnd();
    }
}

// Base vertical azul inclinada com profundidade
void TorreBase() {
    float profundidade = 0.5f;

    // Bloco azul vertical
    float xOffset = -0.2f;
    float larguraBloco = 0.7f;

    glColor3f(0.0f, 0.0f, 0.6f);
    glBegin(GL_QUADS);
    // Frente
    glVertex3f(xOffset,        0.0f, 0.0f);
    glVertex3f(xOffset + larguraBloco, 0.0f, 0.0f);
    glVertex3f(xOffset + larguraBloco, 3.0f, 0.0f);
    glVertex3f(xOffset,        3.0f, 0.0f);

    // Trás
    glVertex3f(xOffset,        0.0f, profundidade);
    glVertex3f(xOffset + larguraBloco, 0.0f, profundidade);
    glVertex3f(xOffset + larguraBloco, 3.0f, profundidade);
    glVertex3f(xOffset,        3.0f, profundidade);

    // Lado direito
    glVertex3f(xOffset + larguraBloco, 0.0f, 0.0f);
    glVertex3f(xOffset + larguraBloco, 0.0f, profundidade);
    glVertex3f(xOffset + larguraBloco, 3.0f, profundidade);
    glVertex3f(xOffset + larguraBloco, 3.0f, 0.0f);

    // Lado esquerdo
    glVertex3f(xOffset, 0.0f, 0.0f);
    glVertex3f(xOffset, 0.0f, profundidade);
    glVertex3f(xOffset, 3.0f, profundidade);
    glVertex3f(xOffset, 3.0f, 0.0f);
    glEnd();

    // Triângulo com profundidade
    float zFrente = 0.4f;
    float zTras = 0.2f;

    // Pontos da frente
    float ax = 2.5f, ay = 0.0f;
    float bx = 0.0f, by = 2.0f;
    float cx = 0.0f, cy = 0.0f;

    // Frente
    glColor3f(0.2f, 0.2f, 1.0f); // azul claro
    glBegin(GL_TRIANGLES);
    glVertex3f(ax, ay, zFrente);
    glVertex3f(bx, by, zFrente);
    glVertex3f(cx, cy, zFrente);
    glEnd();

    // Trás
    glBegin(GL_TRIANGLES);
    glVertex3f(ax, ay, zTras);
    glVertex3f(bx, by, zTras);
    glVertex3f(cx, cy, zTras);
    glEnd();

    // Lateral 1 (AB)
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.6f, 0.6f); // cinza claro
    glVertex3f(ax, ay, zFrente);
    glVertex3f(ax, ay, zTras);
    glVertex3f(bx, by, zTras);
    glVertex3f(bx, by, zFrente);
    glEnd();

    // Lateral 2 (BC)
    glBegin(GL_QUADS);
    glVertex3f(bx, by, zFrente);
    glVertex3f(bx, by, zTras);
    glVertex3f(cx, cy, zTras);
    glVertex3f(cx, cy, zFrente);
    glEnd();

    // Lateral 3 (CA)
    glBegin(GL_QUADS);
    glVertex3f(cx, cy, zFrente);
    glVertex3f(cx, cy, zTras);
    glVertex3f(ax, ay, zTras);
    glVertex3f(ax, ay, zFrente);
    glEnd();

    // Barras inclinadas intercaladas (amarela e cinza) na frente e atras do triângulo
    DesenharGradesTriangulo(zFrente);
    zFrente = 0.19f;
    DesenharGradesTriangulo(zFrente);

}

void DesenharGradesTriangulo(float zFrente) {
    int n = 18;
    float zGrades = zFrente + 0.002f;

    for (int i = 0; i < n; i++) {
        float y = 0.05f + i * (1.9f / n);

        // Cálculo do limite máximo do triângulo nessa altura Y
        float xMax = 2.5f * (1.0f - y / 2.0f);
        float largura = xMax * 0.8f;
        float x1 = xMax - largura;

        if (i % 2 == 0)
            glColor3f(1.0f, 1.0f, 0.4f); // amarelo
        else
            glColor3f(0.6f, 0.6f, 0.6f); // cinza

        glBegin(GL_QUADS);
        glVertex3f(x1, y - 0.03f, zGrades);
        glVertex3f(xMax, y - 0.03f, zGrades);
        glVertex3f(xMax, y + 0.03f, zGrades);
        glVertex3f(x1, y + 0.03f, zGrades);
        glEnd();
    }
}

// Plataforma saliente com volume
void Plataforma() {
    float x, y, z, largura, altura, profundidade;
    x = 0.4f; // Posição X
    y = 2.0f;  // Posição Y
    z = -0.1f;  // Posição Z
    largura = 1.0f; // Largura da plataforma
    altura = 0.2f; // Altura da plataforma
    profundidade = 0.8f; // Profundidade da plataforma

    // Cor cinza para a plataforma
    glColor3f(0.4f, 0.4f, 0.4f); // cinza

    glBegin(GL_QUADS);
    
    // Topo
    glVertex3f(x,         y,      z);
    glVertex3f(x+largura, y,      z);
    glVertex3f(x+largura, y+altura, z);
    glVertex3f(x,         y+altura, z);

    // Frente
    glVertex3f(x,         y+altura, z);
    glVertex3f(x+largura, y+altura, z);
    glVertex3f(x+largura, y+altura, z+profundidade);
    glVertex3f(x,         y+altura, z+profundidade);

    // Lado direito
    glVertex3f(x+largura, y,      z);
    glVertex3f(x+largura, y+altura, z);
    glVertex3f(x+largura, y+altura, z+profundidade);
    glVertex3f(x+largura, y,      z+profundidade);

    // Lado esquerdo
    glVertex3f(x, y, z);
    glVertex3f(x, y+altura, z);
    glVertex3f(x, y+altura, z+profundidade);
    glVertex3f(x, y, z+profundidade);
    
    // Parte inferior (opcional)
    glVertex3f(x,         y, z+profundidade);
    glVertex3f(x+largura, y, z+profundidade);
    glVertex3f(x+largura, y, z);
    glVertex3f(x,         y, z);
    
    // Traseira (opcional)
    glVertex3f(x,         y, z+profundidade);
    glVertex3f(x+largura, y, z+profundidade);
    glVertex3f(x+largura, y+altura, z+profundidade);
    glVertex3f(x,         y+altura, z+profundidade);

    glEnd();
}

void DesenharLogoAvengers(float xOffset, float yOffset, float zOffset, float escala) {
    glPushMatrix();

    glTranslatef(xOffset, yOffset, zOffset);
    glScalef(escala, escala, 1.0f);

    glColor3f(0.8f, 0.0f, 0.0f);
    float z = 0.01f;

    // Círculo externo
    glLineWidth(6.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float ang = 2.0f * PI * i / 100;
        float x = 0.8f * cos(ang);
        float y = 0.8f * sin(ang);
        glVertex3f(x, y, z);
    }
    glEnd();

    // Letra A
    glLineWidth(12.0f); // <- Aumenta a espessura do A
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.3f, -0.5f, z);
    glVertex3f(0.0f, 0.5f, z);
    glVertex3f(0.3f, -0.5f, z);
    glEnd();

    // Traço interno do A
    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.1f, -0.1f, z);
    glVertex3f(0.15f, -0.1f, z);
    glEnd();

    // Seta
    float deslocamentoY = 0.05f;
    glBegin(GL_TRIANGLES);
    glVertex3f(0.15f, -0.1f + deslocamentoY, z);
    glVertex3f(0.15f, -0.2f + deslocamentoY, z);
    glVertex3f(0.3f,  -0.15f + deslocamentoY, z);
    glEnd();

    glPopMatrix();
}

// Topo inclinado com volume
void TopoInclinado() {
    // Variáveis para movimentar o topo
    float xOffset = 0.1f;
    float yOffset = 0.7f;
    float zOffset = 0.05f;

    // Profundidade do topo (espessura)
    float profundidade = 0.4f;
    float escalaX = 1.5f; // fator de escala para largura

    // Cor
    glColor3f(0.0f, 0.3f, 0.7f); // azul escuro

    // Pontos base com escala em X + offset
    float x1 = 0.0f * escalaX + xOffset, y1 = 2.0f + yOffset;
    float x2 = 0.5f * escalaX + xOffset, y2 = 2.0f + yOffset;
    float x3 = 0.9f * escalaX + xOffset, y3 = 2.3f + yOffset;
    float x4 = 0.1f * escalaX + xOffset, y4 = 2.4f + yOffset;
    float z = zOffset;

    // Frente
    glBegin(GL_POLYGON);
    glVertex3f(x1, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x3, y3, z);
    glVertex3f(x4, y4, z);
    glEnd();

    // Trás
    glBegin(GL_POLYGON);
    glVertex3f(x1, y1, z + profundidade);
    glVertex3f(x2, y2, z + profundidade);
    glVertex3f(x3, y3, z + profundidade);
    glVertex3f(x4, y4, z + profundidade);
    glEnd();

    // Laterais
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z);
    glVertex3f(x1, y1, z + profundidade);
    glVertex3f(x4, y4, z + profundidade);
    glVertex3f(x4, y4, z);

    glVertex3f(x3, y3, z);
    glVertex3f(x3, y3, z + profundidade);
    glVertex3f(x2, y2, z + profundidade);
    glVertex3f(x2, y2, z);
    glEnd();
}


// Desenhar a torre completa
void DesenharTorre() {
    TorreBase();
    TorreGrades(-0.01f);
    Plataforma();
    TorreGrades(0.53f);
    TopoInclinado();
    DesenharLogoAvengers(0.12f, 2.5f, 0.5f, 0.5f);
    DesenharLogoAvengers(0.12f, 2.5f, -0.02f, 0.5f);
}

// Câmera e projeção
void IniciarCamera() {
    float camX = raioCamera * sin(angulo);
    float camZ = raioCamera * cos(angulo);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)largura / altura, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, alturaCamera, camZ, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
}

// Cena principal
void Cena() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    IniciarCamera();

    DesenharEixos();
    DesenharTorre();
    EscreverTexto(-2.0f, 3.5f, 0.0f, "Gabriel Galdino - Torre dos Vingadores");
    glFlush();
}

// Controle de clique do mouse
void Mouse(int botao, int estado, int x, int y) {
    if (estado == GLUT_DOWN) {
        switch (botao) {
            case GLUT_LEFT_BUTTON:
                arrastando = 1;
                mouseXAnterior = x;
                mouseYAnterior = y;
                break;

            case 3: // Scroll up
                raioCamera -= 0.3f; // Aproxima
                if (raioCamera < 2.0f) raioCamera = 3.0f; // Limite mínimo de zoom
                glutPostRedisplay();
                break;

            case 4: // Scroll down
                raioCamera += 0.3f; // Afasta
                if (raioCamera > 15.0f) raioCamera = 15.0f; // Limite máximo de zoom
                glutPostRedisplay();
                break;
        }
    } else if (estado == GLUT_UP && botao == GLUT_LEFT_BUTTON) {
        arrastando = 0;
    }
}


void ArrastarMouse(int x, int y) {
    if (arrastando) {
        int dx = x - mouseXAnterior;
        int dy = y - mouseYAnterior;

        // Sensibilidade
        float sensibilidade = 0.005f;

        // Atualiza o ângulo com o movimento horizontal
        angulo += dx * sensibilidade;

        // Atualiza a altura da câmera com o movimento vertical
        alturaCamera -= dy * sensibilidade;

        // Limites na altura
        if (alturaCamera < 0.5f) alturaCamera = 0.5f;
        if (alturaCamera > 5.0f) alturaCamera = 5.0f;

        mouseXAnterior = x;
        mouseYAnterior = y;

        glutPostRedisplay();
    }
}

void Teclado(unsigned char tecla, int x, int y) {
    const float passoZoom = 0.5f;
    const float minZoom = 3.0f;
    const float maxZoom = 15.0f;

    switch (tecla) {
        case '+':
        case '=': // Teclas + ou = fazem zoom in
            raioCamera -= passoZoom;
            if (raioCamera < minZoom) raioCamera = minZoom;
            glutPostRedisplay();
            break;

        case '-':
        case '_': // Teclas - ou _ fazem zoom out
            raioCamera += passoZoom;
            if (raioCamera > maxZoom) raioCamera = maxZoom;
            glutPostRedisplay();
            break;

        case 27: // tecla ESC
            exit(0);
            break;
    }
}

void TeclaEspecial(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_LEFT:
            angulo -= 0.1f; // gira para esquerda
            break;
        case GLUT_KEY_RIGHT:
            angulo += 0.1f; // gira para direita
            break;
        case GLUT_KEY_UP:
            alturaCamera += 0.2f; // eleva câmera
            if (alturaCamera > 5.0f) alturaCamera = 5.0f; // Limite superior
            break;
        case GLUT_KEY_DOWN:
            alturaCamera -= 0.2f; // abaixa câmera
            if (alturaCamera < 0.5f) alturaCamera = 0.5f; // limite inferior
            break;
    }
    glutPostRedisplay();
}

void EscreverTexto(float x, float y, float z, const char* texto) {
    glColor3f(1.0f, 1.0f, 1.0f); // Cor do texto (branco)
    glRasterPos3f(x, y, z);      // Posição na tela

    for (int i = 0; texto[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(largura, altura);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Torre dos Vingadores em 3D");

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(Cena);
    glutMouseFunc(Mouse);
    glutMotionFunc(ArrastarMouse);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(TeclaEspecial);

    glutMainLoop();
    return 0;
}
