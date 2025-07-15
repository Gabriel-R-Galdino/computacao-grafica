// Autor: Gabriel Rosa Galdino - Atividade 7 - Computação Gráfica
// Data: 08/07/2025 // Alterações: 15/07/2025
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

void DesenhaCirculo(float x, float y, float z, float radius, int segments, int filled, int outlined);
void DesenhaCirculoHorizontal(float x, float y, float z, float radius, int segments, int filled, int outlined);
void DesenharCilindro(float raio, float altura, int fatias);
void DesenharCilindroDiagonal(float raio, float altura, int fatias, float offsetX, float offsetY, float offsetZ);
void DesenharChao();
void TorreBase();
void TorreGrades(float zProfundidade);
void Plataforma();
void TopoInclinado();
void DesenharTorre();
void DesenharGradesTriangulo(float zFrente,float deslocamentoY);
void DesenharLogoAvengers(float xOffset, float yOffset, float zOffset, float escala);
void EscreverTexto(float x, float y, float z, const char* texto);
void ArrastarMouse(int x, int y);
void Teclado(unsigned char key, int x, int y);
void TeclaEspecial(int key, int x, int y);
void Mouse(int botao, int estado, int x, int y);
void IniciarCamera();

// Função para desenhar círculo preenchido
void DesenhaCirculo(float x, float y, float z, float radius, int segments, int filled, int outlined) {
    float angleIncrement = 2.0f * M_PI / segments;

    if (filled) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = angleIncrement * i;
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex3f(x + dx, y + dy, z);
        }
        glEnd();
    }

    if (outlined) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float theta = angleIncrement * i;
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex3f(x + dx, y + dy, z);
        }
        glEnd();
    }
}

void DesenhaCirculoHorizontal(float x, float y, float z, float radius, int segments, int filled, int outlined) {
    float angleIncrement = 2.0f * M_PI / segments;

    if (filled) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = angleIncrement * i;
            float dx = radius * cosf(theta);
            float dz = radius * sinf(theta);
            glVertex3f(x + dx, y, z + dz); // y constante, varia x e z
        }
        glEnd();
    }

    if (outlined) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float theta = angleIncrement * i;
            float dx = radius * cosf(theta);
            float dz = radius * sinf(theta);
            glVertex3f(x + dx, y, z + dz); // y constante, varia x e z
        }
        glEnd();
    }
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

void DesenharGradesTriangulo(float zFrente, float deslocamentoY) {
    int n = 18;
    float zGrades = zFrente + 0.002f;

    // Altura e largura máxima do triângulo
    float altura = 2.5f;
    float larguraBase = 1.9f;

    for (int i = 0; i < n; i++) {
        // y variando entre 0 + deslocamento até 2.5 + deslocamento (altura do triângulo)
        float y = i * (altura / n) + deslocamentoY;

        float yRelativo = y - deslocamentoY; // sem deslocamento
        float xMax = larguraBase * (1.0f - (yRelativo / altura));

        // Largura da faixa da grade: pode ser uma fração de xMax
        float largura = xMax * 0.8f;
        float x1 = xMax - largura;

        // Alterna cor para dar o efeito de grade
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

void DesenharCilindro(float raio, float altura, int fatias) {
    float anguloIncremento = 2.0f * 3.14159265f / fatias;

    // Desenha base inferior (círculo em z=0)
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.7f, 0.7f, 0.7f); // cinza
    glVertex3f(0.0f, 0.0f, 0.0f); // centro da base
    for (int i = 0; i <= fatias; i++) {
        float angulo = i * anguloIncremento;
        float x = raio * cos(angulo);
        float y = raio * sin(angulo);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    // Desenha base superior (círculo em z=altura)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, altura); // centro topo
    for (int i = 0; i <= fatias; i++) {
        float angulo = i * anguloIncremento;
        float x = raio * cos(angulo);
        float y = raio * sin(angulo);
        glVertex3f(x, y, altura);
    }
    glEnd();

    // Desenha lateral (tira de quads)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= fatias; i++) {
        float angulo = i * anguloIncremento;
        float x = raio * cos(angulo);
        float y = raio * sin(angulo);

        glVertex3f(x, y, 0.0f);       // base
        glVertex3f(x, y, altura);    // topo
    }
    glEnd();
}

void DesenharCilindroDiagonal(float raio, float altura, int fatias, float offsetX, float offsetY, float offsetZ) {
    float ax = 0.0f, ay = 2.5f, az = 0.3f;
    float cx = 1.9f, cy = 0.0f, cz = 0.3f;

    // Vetor da hipotenusa AC
    float dx = cx - ax;
    float dy = cy - ay;
    float dz = cz - az;

    float comprimento = sqrt(dx*dx + dy*dy + dz*dz);
    comprimento *= 0.8f; // reduz o comprimento do cilindro

    // Meio do segmento (posição do cilindro)
    float mx = (ax + cx) / 2.0f + offsetX;
    float my = (ay + cy) / 2.0f + offsetY;
    float mz = (az + cz) / 2.0f + offsetZ;

    // Vetor unitário da hipotenusa
    float vx = dx / comprimento;
    float vy = dy / comprimento;
    float vz = dz / comprimento;

    // Calcula eixo e ângulo para rotacionar eixo z para vetor da hipotenusa
    float rx = -vy;
    float ry = vx;
    float rz = 0;

    float cosA = vz;
    float angulo = acos(cosA) * 180.0f / 3.14159265f;

    glPushMatrix();

    glTranslatef(mx, my, mz);

    if (!(rx == 0 && ry == 0 && rz == 0)) {
        glRotatef(angulo, rx, ry, rz);
    }

    // Desenha o cilindro manual
    DesenharCilindro(raio, comprimento, fatias);

    glPopMatrix();
}

void DesenharChao() {
    float raio = 2.5f;
    float espessura = 0.2f;
    int segmentos = 100;
    float x = 0.5f, z = 0.25f; // centralizado com a torre
    float y = -0.01f; // Abaixo da base da torre

    glColor3f(0.3f, 0.3f, 0.3f); // cinza escuro (concreto)

    // Parte superior
    DesenhaCirculoHorizontal(x, y + espessura, z, raio, segmentos, 1, 0);

    // Parte inferior
    DesenhaCirculoHorizontal(x, y, z, raio, segmentos, 1, 0);

    // Lateral da plataforma (como um cilindro horizontal)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segmentos; i++) {
        float theta = 2.0f * M_PI * i / segmentos;
        float dx = raio * cosf(theta);
        float dz = raio * sinf(theta);

        glVertex3f(x + dx, y, z + dz);                 // ponto na base
        glVertex3f(x + dx, y + espessura, z + dz);     // ponto no topo
    }
    glEnd();
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
    glVertex3f(xOffset, 0.0f, 0.0f);
    glVertex3f(xOffset + larguraBloco, 0.0f, 0.0f);
    glVertex3f(xOffset + larguraBloco, 3.0f, 0.0f);
    glVertex3f(xOffset, 3.0f, 0.0f);

    // Trás
    glVertex3f(xOffset, 0.0f, profundidade);
    glVertex3f(xOffset + larguraBloco, 0.0f, profundidade);
    glVertex3f(xOffset + larguraBloco, 3.0f, profundidade);
    glVertex3f(xOffset, 3.0f, profundidade);

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

    // Triângulo com profundidade elevado
    float zFrente = 0.4f;
    float zTras = 0.2f;

    float deslocamentoY = 0.0f; // Altura do deslocamento para elevar o triângulo

    // Pontos da frente (elevados)
    float ax = 0.0f, ay = 2.5f + deslocamentoY;
    float bx = 0.0f, by = 0.0f + deslocamentoY;
    float cx = 1.9f, cy = 0.0f + deslocamentoY;

    // Frente do triângulo
    glColor3f(0.2f, 0.2f, 1.0f); // azul claro
    glBegin(GL_TRIANGLES);
    glVertex3f(ax, ay, zFrente);
    glVertex3f(bx, by, zFrente);
    glVertex3f(cx, cy, zFrente);
    glEnd();

    // Trás do triângulo
    glBegin(GL_TRIANGLES);
    glVertex3f(ax, ay, zTras);
    glVertex3f(bx, by, zTras);
    glVertex3f(cx, cy, zTras);
    glEnd();

    // Lateral 1 (AB)
    glBegin(GL_QUADS);
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

    // Grades inclinadas (frente e atrás)
    DesenharGradesTriangulo(zFrente, deslocamentoY);
    DesenharGradesTriangulo(0.19f, deslocamentoY);
    DesenharCilindroDiagonal(0.05f, 0.05f, 30, -0.5f, 0.7f, 0.0f);
}


// Plataforma saliente com volume
void Plataforma() {
    float x = 1.0f;          // Centro em X
    float y = 2.0f;          // Base Y da plataforma
    float z = 0.2f;          // Centro em Z
    float altura = 0.2f;     // Espessura (altura) da plataforma
    float raio = 0.7f;       // Raio da plataforma
    int segmentos = 100;

    glColor3f(0.7f, 0.7f, 0.7f); // cinza

    // Topo da plataforma (em y + altura)
    DesenhaCirculoHorizontal(x, y + altura, z, raio, segmentos, 1, 0);

    // Base da plataforma (em y)
    DesenhaCirculoHorizontal(x, y, z, raio, segmentos, 1, 0);

    // Lateral da plataforma (faixa entre topo e base)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segmentos; i++) {
        float theta = 2.0f * M_PI * i / segmentos;
        float dx = raio * cosf(theta);
        float dz = raio * sinf(theta);

        glVertex3f(x + dx, y, z + dz);           // ponto na base
        glVertex3f(x + dx, y + altura, z + dz);  // ponto no topo
    }
    glEnd();
}

void DesenharLogoAvengers(float xOffset, float yOffset, float zOffset, float escala) {
    glPushMatrix();

    glTranslatef(xOffset, yOffset, zOffset);
    glScalef(escala, escala, 1.0f);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glColor3f(0.8f, 0.8f, 0.8f);
    float z = 0.01f;

    // Círculo externo utilizando DesenhaCirculo
    glLineWidth(6.0f);
    DesenhaCirculo(0.0f, 0.0f, z, 0.8f, 100, 0, 1); // apenas contorno

    glScalef(1.5f, 1.5f, 1.5f);
    // Letra A
    glLineWidth(12.0f);
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
    DesenharChao();
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

    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

    glutDisplayFunc(Cena);
    glutMouseFunc(Mouse);
    glutMotionFunc(ArrastarMouse);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(TeclaEspecial);

    glutMainLoop();
    return 0;
}
