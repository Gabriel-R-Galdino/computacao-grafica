// Autor: Gabriel Rosa Galdino - Atividade 3 - Computação Gráfica
// Data: 27/05/2025
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Definições do cenário
#define SCENE_LEFT -0.5f
#define SCENE_RIGHT 0.5f
#define SCENE_TOP 1.0f
#define SCENE_BOTTOM -0.5f

// Aproximação do tamanho do Pokémon (ajustável se necessário)
#define POKEMON_WIDTH 0.7f
#define POKEMON_HEIGHT 1.0f

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Variáveis de cor
int R = 255, G = 165, B = 0;
float R_Asa = 25.5, G_Asa = 178.5, B_Asa = 76.5;
int backgroundColor = 0;
GLubyte textoR = 255, textoG = 255, textoB = 255;

// Título do Pokémon
char *titulo = "Dragonite - Gabriel Galdino";

// Variáveis de transformação
float translateX = 0.0f, translateY = 0.0f;
float scaleFactor = 0.8f;
float maxOffsetX, maxOffsetY;

// Definições de ângulos e limites
// Ombro
const float OMBRO_MIN = -60.0f;
const float OMBRO_MAX = 60.0f;

// Cotovelo
const float COTOVELO_MIN = 0.0f;      // Não dobra para trás
const float COTOVELO_MAX = 130.0f;    // Limite de dobra normal

// Mão
const float MAO_MIN = -40.0f;
const float MAO_MAX = 180.0f;

// Variáveis de animação
float animacaoPerna = 0.0f;
int direcaoPerna = 1;
float animacaoAsa = 0.0f;
int direcaoAsa = 1;
float animacaoCauda = 0.0f;
int direcaoCauda = 1;
float olhoAberto = 1.0f; 
int piscando = 0;        
float tempoPiscar = 0.0f; 
float anguloChifre = 0.0f;
int direcaoChifre = 1;
float anguloCabeca = 0.0f;
int direcaoCabeca = 1;  
int pausaCabeca = 0; 
// Braço esquerdo
float rotOmbroEsq = 0.0f;
float rotCotoveloEsq = 0.0f;
float rotMaoEsq = 0.0f;
// Braço direito
float rotOmbroDir = 0.0f;
float rotCotoveloDir = 0.0f;
float rotMaoDir = 0.0f;
// Rebolado da barriga
float animacaoRebolado = 0.0f;
int direcaoRebolado = 1;
int ativarRebolado = 0;

// Prototipos das funcoes
void DesenhaCirculo(float x, float y, float radius, int segments, int filled, int outlined);
void DesenhaElipse(float x, float y, float rx, float ry, int segments, int filled);
void DesenhaArcHorizontal(float x, float y, float rx, float ry, int segments);
void DesenhaBarriga(void);
void DesenhaAsa(int lado);
void DesenhaBraco(int lado);
void DesenhaPerna(int lado);
void DesenhaCalda(void);
void DesenhaCabeca(void);
void DesenhaPokemon(void);
void DesenhaPokemonEscalado(void);
void DesenhaCenario(void);
void reshape(int w, int h);
void init(void);
void DesenhaTexto(char *string);
void display(void);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void AtualizaAnimacao(void);
void AtualizaPiscar(void);
void AtualizaChifre(void);
void AtualizaCabeca(void);
void Dancinha(void);
float clamp(float valor, float min, float max);

// Função para desenhar círculo preenchido
void DesenhaCirculo(float x, float y, float radius, int segments, int filled, int outlined) {
    if (filled) {
        float angleIncrement = 2.0f * M_PI / segments;
        glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = angleIncrement * i;
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }

    if (outlined) {
        glBegin(GL_LINE_LOOP);
        float angleIncrement = 2.0f * M_PI / segments;
        for (int i = 0; i < segments; i++) {
            float theta = angleIncrement * i;
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }
}

// Função para desenhar elipse preenchida
void DesenhaElipse(float x, float y, float rx, float ry, int segments, int filled) {
    if (filled) glBegin(GL_POLYGON);
    else glBegin(GL_LINE_LOOP);

    float angleIncrement = 2.0f * M_PI / segments;
    for (int i = 0; i < segments; i++) {
        float theta = angleIncrement * i;;
        float dx = rx * cosf(theta);
        float dy = ry * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Desenha um arco horizontal (metade superior de uma elipse)
void DesenhaArcHorizontal(float x, float y, float rx, float ry, int segments) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = M_PI * i / segments;  // de 0 a PI (metade do círculo)
        float dx = rx * cosf(theta);
        float dy = ry * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void DesenhaBarriga() {
    glPushMatrix();
    glTranslatef(animacaoRebolado, 0.0f, 0.0f);
    // Cor do corpo parte externa
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    DesenhaElipse(0.0f, -0.5f, 0.3f, 0.55f, 100, 1);

    // Cor da barriga
    glColor3f(1.0f, 0.9f, 0.7f);

    // Parte central 
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, -0.75f);  
        glVertex2f(0.2f, -0.75f);   
        glVertex2f(0.2f, -0.25f);   
        glVertex2f(-0.2f, -0.25f);  
    glEnd();

    // Semicírculo superior
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++) {
        float theta = M_PI * i / 100;
        float x = 0.2f * cosf(theta);
        float y = 0.1f * sinf(theta);
        glVertex2f(x, -0.25f + y);
    }
    glEnd();
    

    // Semicírculo inferior
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++) {
        float theta = M_PI * i / 100;
        float x = 0.2f * cosf(theta);
        float y = 0.1f * sinf(theta);
        glVertex2f(x, -0.75f - y);
    }
    glEnd();

    // Listras arqueadas
    glColor3f(0.6f, 0.4f, 0.2f); 
    float yBase = -0.45f;
    float yStep = -0.10f;
    int totalStripes = 4;
    for (int i = 0; i < totalStripes; i++) {
        DesenhaArcHorizontal(0.0f, yBase + i * yStep, 0.18f, 0.05f, 50);
    }
    glPopMatrix();
}

void DesenhaAsa(int lado) {
    float s = (lado == 0) ? -1.0f : 1.0f;
    float scale = 1.2f;
    float offsetY = -0.05f + animacaoAsa;     // mover na vertical
    float offsetX = 0.2f;      // mover na horizontal 

    float wing[][2] = {
        {0.0f, -0.21f},   // [0] Base da asa, perto do corpo (parte inferior)
        {0.05f, -0.1f},  // [1] Começa a subir suavemente
        {0.15f, -0.1f},   // [2] Leve descida curva
        {0.3f, -0.1f},    // [3] Continuação da base da asa, ainda na parte inferior
        {0.45f, -0.1f},    // [4] Começa a subir para o topo externo da asa
        {0.6f, 0.1f},    // [5] Continuação da subida
        {0.7f, 0.1f},    // [6] Extremo superior da asa (mais distante do corpo)
        {0.55f, 0.15f},   // [7] Topo mais curvado da asa
        {0.4f, 0.2f},     // [8] Começa a voltar em direção ao corpo
        {0.2f, 0.18f},    // [9] Quase fechando o topo
        {0.05f, -0.1f}    // [10] Retorna à base inferior para fechar o polígono
    };

    // Parte verde
    glColor3f(R_Asa / 255.0f, G_Asa / 255.0f, B_Asa / 255.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 11; i++) {
        float x = s * wing[i][0] * scale + s * offsetX;  // desloca no eixo X
        float y = wing[i][1] * scale + offsetY;          // desloca no eixo Y
        glVertex2f(x, y);
    }
    glEnd();

    // Contorno laranja
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(5.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 6; i <= 10; i++) {
        float x = s * wing[i][0] * scale + s * offsetX;
        float y = wing[i][1] * scale + offsetY;
        glVertex2f(x, y);
    }
    float x0 = s * wing[0][0] * scale + s * offsetX;
    float y0 = wing[0][1] * scale + offsetY;
    glVertex2f(x0, y0);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
}

void DesenhaBraco(int lado) {
    float s = (lado == 0) ? -1.0f : 1.0f;
    float rotOmbroAtual = (lado == 0) ? rotOmbroEsq : rotOmbroDir;
    float rotCotoveloAtual = (lado == 0) ? rotCotoveloEsq : rotCotoveloDir;
    float rotMaoAtual = (lado == 0) ? rotMaoEsq : rotMaoDir;

    // Posição base
    float ombroX = s * 0.25f;
    float ombroY = -0.2f;

    glPushMatrix();
    glTranslatef(ombroX, ombroY, 0.0f);
    glRotatef(s * rotOmbroAtual, 0.0f, 0.0f, 1.0f);

    // Ombro 
    glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);
    DesenhaElipse(0.0f, 0.0f, 0.12f, 0.09f, 50, 1);

    //Antebraço 
    glTranslatef(s * 0.18f, 0.0f, 0.0f);
    glRotatef(s * rotCotoveloAtual, 0.0f, 0.0f, 1.0f);

    glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);
    DesenhaElipse(0.0f, 0.0f, 0.18f, 0.09f, 50, 1);

    // Contorno
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaElipse(0.0f, 0.0f, 0.18f, 0.09f, 50, 0);

    // Mão 
    glTranslatef(s * 0.2f, 0.0f, 0.0f);
    glRotatef(s * rotMaoAtual, 0.0f, 0.0f, 1.0f);

    glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);
    DesenhaElipse(0.0f, 0.0f, 0.07f, 0.1f, 50, 1);

    // Contorno da mão
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaElipse(0.0f, 0.0f, 0.07f, 0.1f, 50, 0);

    // Garras 
    float clawBaseY = -0.08f;
    float clawHeight = 0.05f;
    float clawWidth = 0.015f;

    float clawXOffsets[3] = { -0.03f, 0.0f, 0.03f };
    float clawTilt[3] = { -0.01f, 0.0f, 0.01f };

    for (int i = 0; i < 3; i++) {
        float cx = clawXOffsets[i];
        float cy = clawBaseY;

        float tipX = cx + clawTilt[i];
        float tipY = cy - clawHeight;

        // Preenchimento branco
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(cx - clawWidth, cy);
        glVertex2f(cx + clawWidth, cy);
        glVertex2f(tipX, tipY);
        glEnd();

        // Contorno
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(cx - clawWidth, cy);
        glVertex2f(cx + clawWidth, cy);
        glVertex2f(tipX, tipY);
        glEnd();
    }

    glPopMatrix();
}



void DesenhaPerna(int lado) {
    float s = (lado == 0) ? -1.0f : 1.0f;
    float offsetX = 0.29f;
    float offsetY = -0.7f;
    float scale = 1.1f;

    // Aplique a animação: pernas sobem e descem um pouco
    float animOffsetY = (lado == 0) ? animacaoPerna : -animacaoPerna;

    float leg[][2] = {
        {0.00f,  0.00f},
        {0.05f, -0.05f},
        {0.08f, -0.12f},
        {0.09f, -0.20f},
        {0.07f, -0.28f},
        {0.04f, -0.32f},
        {0.00f, -0.34f},
        {-0.04f, -0.32f},
        {-0.07f, -0.28f},
        {-0.09f, -0.22f},
        {-0.08f, -0.15f},
        {-0.05f, -0.07f}
    };

    // Parte laranja 
    glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 12; i++) {
        float x = s * leg[i][0] * scale + s * offsetX;
        float y = leg[i][1] * scale + offsetY + animOffsetY;
        glVertex2f(x, y);
    }
    glEnd();

    // Contorno preto
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 12; i++) {
        float x = s * leg[i][0] * scale + s * offsetX;
        float y = leg[i][1] * scale + offsetY + animOffsetY;
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1.0f);

    // Garras triangulares (mesma animação nas garras)
    float clawBaseY = -0.28f + animOffsetY;
    float clawHeight = 0.04f;
    float clawWidth = 0.015f;

    float clawXOffsets[3] = {0.04f, 0.0f, -0.04f};
    float clawTilt[3] = {0.015f, 0.0f, -0.015f};

    for (int i = 0; i < 3; i++) {
        float cx = s * clawXOffsets[i] * scale + s * offsetX;
        float cy = clawBaseY * scale + offsetY;
        float tipX = cx + s * clawTilt[i];
        float tipY = cy - clawHeight * scale;

        // Preenchimento branco
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(cx - s * clawWidth, cy);
        glVertex2f(cx + s * clawWidth, cy);
        glVertex2f(tipX, tipY);
        glEnd();

        // Contorno preto
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(cx - s * clawWidth, cy);
        glVertex2f(cx + s * clawWidth, cy);
        glVertex2f(tipX, tipY);
        glEnd();
    }
}

void DesenhaCalda() {
    float offsetX = -0.10f;  
    float offsetY = -0.75f + animacaoCauda; // animação vertical
    float s = 1.0f;         

    // Vértices do triângulo 
    float baseX = 0.0f;
    float baseHeight = 0.18f;
    float length = 1.0f;

    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX * s + offsetX, 0.0f * s + offsetY);                      
        glVertex2f(baseX * s + offsetX, -baseHeight * s + offsetY);             
        glVertex2f((baseX + length) * s + offsetX, -baseHeight/2 * s + offsetY); 
    glEnd();

    // Contorno preto
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(baseX * s + offsetX, 0.0f * s + offsetY);
        glVertex2f(baseX * s + offsetX, -baseHeight * s + offsetY);
        glVertex2f((baseX + length) * s + offsetX, -baseHeight/2 * s + offsetY);
    glEnd();
}


void DesenhaCabeca() {
    glPushMatrix();
    glRotatef(anguloCabeca, 0.0f, 0.0f, 1.0f); // Rotaciona no eixo Z
    // Cabeça principal
    glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);
    DesenhaCirculo(0.0f, 0.0f, 0.25f, 100, 1, 0);

    // Focinho
    DesenhaCirculo(0.0f, -0.20f, 0.2f, 100, 1, 0);

    // Narinas
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaCirculo(-0.05f, -0.20f, 0.015f, 50, 1, 0);
    DesenhaCirculo(0.05f, -0.20f, 0.015f, 50, 1, 0);

    // Parte branca dos olhos 
    glColor3f(1.0f, 1.0f, 1.0f);
    DesenhaElipse(-0.1f, 0.05f, 0.05f, 0.08f * olhoAberto, 100, 1);
    DesenhaElipse(0.1f, 0.05f, 0.05f, 0.08f * olhoAberto, 100, 1);

    // Contorno preto dos olhos
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaElipse(-0.1f, 0.05f, 0.05f, 0.08f * olhoAberto, 100, 0);
    DesenhaElipse(0.1f, 0.05f, 0.05f, 0.08f * olhoAberto, 100, 0);

    // Pupilas pretas 
    DesenhaElipse(-0.1f, 0.05f, 0.02f, 0.04f * olhoAberto, 100, 1);
    DesenhaElipse(0.1f, 0.05f, 0.02f, 0.04f * olhoAberto, 100, 1);

    // Brilho 
    if (olhoAberto > 0.5f) {
        glColor3f(1.0f, 1.0f, 1.0f);
        DesenhaElipse(-0.085f, 0.05f, 0.01f, 0.015f, 100, 1);
        DesenhaElipse(0.085f, 0.05f, 0.01f, 0.015f, 100, 1);
    }

    // Chifrinho central
    glColor3f(R / 255.0f, G / 255.0f, B / 255.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(-0.05f, 0.23f);
        glVertex2f(0.05f, 0.23f);
    glEnd();

    // Chifres laterais
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glColor3f(0.9f, 0.9f, 0.7f);
    glLineWidth(5.0f);

    // Chifre esquerdo
    glPushMatrix();
    glTranslatef(-0.1f, 0.21f, 0.0f); // Move para origem do chifre
    glRotatef(anguloChifre, 0.0f, 0.0f, 1.0f); // Rotaciona
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.19f);
        glVertex2f(-0.2f, 0.14f);
    glEnd();
    glPopMatrix();

    // Chifre direito
    glPushMatrix();
    glTranslatef(0.1f, 0.21f, 0.0f);
    glRotatef(-anguloChifre, 0.0f, 0.0f, 1.0f); // Inverte ângulo para lado oposto
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.1f, 0.19f);
        glVertex2f(0.2f, 0.14f);
    glEnd();
    glPopMatrix();

    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
    glPopMatrix();
}

void DesenhaPokemon() {
    DesenhaAsa(0);  // Asa esquerda
    DesenhaAsa(1); // Asa direita
    DesenhaBraco(0);  // Braço esquerdo
    DesenhaBraco(1); // Braço direito
    DesenhaCalda();
    DesenhaBarriga();
    DesenhaPerna(0);  // Perna esquerda
    DesenhaPerna(1); // Perna direita
    DesenhaCabeca(); 
}

void DesenhaPokemonEscalado() {
    glPushMatrix(); 

    glTranslatef(translateX, translateY, 0.0f); // Centraliza
    glScalef(scaleFactor, scaleFactor, 0.8f);     // Reduz o tamanho pela metade

    DesenhaPokemon(); 

    glPopMatrix(); 
}

void DesenhaCenario() {
    // Cor do fundo (céu)
    glColor3f(0.53f, 0.81f, 0.98f);  
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f);  
    glVertex2f(1.0f, 1.0f);  
    glVertex2f(1.0f, 0.0f);  
    glVertex2f(-1.0f, 0.0f);  
    glEnd();

    // nuvens
    glColor3f(1.0f, 1.0f, 1.0f);  
    DesenhaCirculo(-0.7f, 0.7f, 0.1f, 30, 1, 0);  
    DesenhaCirculo(-0.5f, 0.75f, 0.12f, 30, 1, 0); 
    DesenhaCirculo(0.3f, 0.6f, 0.15f, 30, 1, 0);   
    DesenhaCirculo(0.5f, 0.65f, 0.1f, 30, 1, 0);   

    // Cor do chão 
    glColor3f(0.56f, 0.93f, 0.56f); 
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);  
    glVertex2f(1.0f, 0.0f);   
    glVertex2f(1.0f, -1.0f);  
    glVertex2f(-1.0f, -1.0f); 
    glEnd();

    // montanhas 
    glColor3f(0.5f, 0.35f, 0.05f);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(-0.5f, 0.4f);
    glVertex2f(0.0f, 0.0f);
    
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    // Arbustos
    // Arbusto 1
    glColor3f(0.0f, 0.5f, 0.0f); 
    DesenhaCirculo(-0.75f, -0.35f, 0.05f, 20, 1, 0);
    DesenhaCirculo(-0.80f, -0.33f, 0.06f, 20, 1, 0);
    DesenhaCirculo(-0.85f, -0.35f, 0.05f, 20, 1, 0);

    DesenhaCirculo(-0.4f, -0.87f, 0.05f, 20, 1, 0);
    DesenhaCirculo(-0.35f, -0.85f, 0.06f, 20, 1, 0);
    DesenhaCirculo(-0.3f, -0.87f, 0.05f, 20, 1, 0);

    // Arbusto 3
    DesenhaCirculo(0.3f, -0.58f, 0.05f, 20, 1, 0);
    DesenhaCirculo(0.35f, -0.56f, 0.06f, 20, 1, 0);
    DesenhaCirculo(0.4f, -0.58f, 0.05f, 20, 1, 0);

    // Arbusto 4
    DesenhaCirculo(0.7f, -0.46f, 0.05f, 20, 1, 0);
    DesenhaCirculo(0.75f, -0.44f, 0.06f, 20, 1, 0);
    DesenhaCirculo(0.8f, -0.46f, 0.05f, 20, 1, 0);
    

    DesenhaPokemonEscalado(); 
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    AtualizaPiscar();       // Piscar automático
    AtualizaChifre();
    AtualizaCabeca();
    Dancinha();         // Animação de rebolado
    
    glPushMatrix();
    glScalef(0.8f, 0.8f, 0.8f);

    DesenhaCenario();       // Chama o cenário + Pokémon

    glPopMatrix();

    DesenhaTexto(titulo);
    glFlush();
}

void DesenhaTexto(char *string) {
    glColor3ub(textoR, textoG, textoB);
    glRasterPos2f(-0.7f, 0.9f);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0); // ESC
        case 't': // Versao shiny
            R = 25.5; G = 178.5; B = 76.5;
            R_Asa = 82; G_Asa = 37; B_Asa = 72;
            titulo = "Shiny Dragonite - Gabriel Galdino"; 
            glutPostRedisplay(); 
            break;
        case 'y': // Versao Normal
            R = 255, G = 165, B = 0;
            R_Asa = 25.5, G_Asa = 178.5, B_Asa = 76.5; 
            titulo = "Dragonite - Gabriel Galdino";
            glutPostRedisplay(); 
            break;
        case ' ': // Muda a cor de fundo
            if(backgroundColor == 0) {
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Preto
                textoR = 255; textoG = 255; textoB = 255;
                backgroundColor = 1;
            } else {
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Branco
                textoR = 0; textoG = 0; textoB = 0;
                backgroundColor = 0;
            }
            glutPostRedisplay();
            break;
        case 'q': // mao direita rotaciona 90 graus
            rotMaoDir += 5.0f;
            rotMaoDir = clamp(rotMaoDir, MAO_MIN, MAO_MAX);
            break;
        case 'w': // mao direita rotaciona -90 graus
            rotMaoDir -= 5.0f;
            rotMaoDir = clamp(rotMaoDir, MAO_MIN, MAO_MAX);
            break;
        case 'e': // mao esquerda rotaciona 90 graus
            rotMaoEsq += 5.0f;
            rotMaoEsq = clamp(rotMaoEsq, MAO_MIN, MAO_MAX);
            break;
        case 'r': // mao esquerda rotaciona -90 graus
            rotMaoEsq -= 5.0f;
            rotMaoEsq = clamp(rotMaoEsq, MAO_MIN, MAO_MAX);
            break;
        case 'a': // cotovelo direito rotaciona 90 graus
            rotCotoveloDir += 5.0f;
            rotCotoveloDir = clamp(rotCotoveloDir, COTOVELO_MIN, COTOVELO_MAX);
            break;
        case 's': // cotovelo direito rotaciona -90 graus
            rotCotoveloDir -= 5.0f;
            rotCotoveloDir = clamp(rotCotoveloDir, COTOVELO_MIN, COTOVELO_MAX);
            break;
        case 'd': // cotovelo esquerdo rotaciona 90 graus
            rotCotoveloEsq += 5.0f;
            rotCotoveloEsq = clamp(rotCotoveloEsq, COTOVELO_MIN, COTOVELO_MAX);
            break;
        case 'f': // cotovelo esquerdo rotaciona -90 graus
            rotCotoveloEsq -= 5.0f;
            rotCotoveloEsq = clamp(rotCotoveloEsq, COTOVELO_MIN, COTOVELO_MAX);
            break;
        case 'z': // ombro direito rotaciona 90 graus
            rotOmbroDir += 5.0f;
            rotOmbroDir = clamp(rotOmbroDir, OMBRO_MIN, OMBRO_MAX);
            break;
        case 'x': // ombro direito rotaciona -90 graus
            rotOmbroDir -= 5.0f;
            rotOmbroDir = clamp(rotOmbroDir, OMBRO_MIN, OMBRO_MAX);
            break;
        case 'c': // ombro esquerdo rotaciona 90 graus
            rotOmbroEsq += 5.0f;
            rotOmbroEsq = clamp(rotOmbroEsq, OMBRO_MIN, OMBRO_MAX);
            break;
        case 'v': // ombro esquerdo rotaciona -90 graus
            rotOmbroEsq -= 5.0f;
            rotOmbroEsq = clamp(rotOmbroEsq, OMBRO_MIN, OMBRO_MAX);
            break;
        case 'p': // Ativa/desativa rebolado
            ativarRebolado = !ativarRebolado;
            break;
    }
}

void specialKeyboard(int key, int x, int y) {
    float halfWidth = (POKEMON_WIDTH * scaleFactor) / 2.0f;
    float halfHeight = (POKEMON_HEIGHT * scaleFactor) / 2.0f;

    switch (key) {
        case GLUT_KEY_LEFT:
            if (translateX - 0.05f > SCENE_LEFT + halfWidth){
                translateX -= 0.05f;
                AtualizaAnimacao();
            }
            break;
        case GLUT_KEY_RIGHT:
            if (translateX + 0.05f < SCENE_RIGHT - halfWidth){
                translateX += 0.05f;
                AtualizaAnimacao();
            }
            break;
        case GLUT_KEY_UP:
            if (translateY + 0.05f < SCENE_TOP - halfHeight){
                translateY += 0.05f;
                AtualizaAnimacao();
            }
            break;
        case GLUT_KEY_DOWN:
            if (translateY - 0.05f > SCENE_BOTTOM + halfHeight){
                translateY -= 0.05f;
                AtualizaAnimacao();
            }
            break;

        case GLUT_KEY_PAGE_UP:
            if (scaleFactor < 0.9f) {
                scaleFactor += 0.05f;
                // Recentralizar se ultrapassou limite após escalar
                translateX = fminf(fmaxf(translateX, SCENE_LEFT + (POKEMON_WIDTH * scaleFactor) / 2.0f),
                                                SCENE_RIGHT - (POKEMON_WIDTH * scaleFactor) / 2.0f);
                translateY = fminf(fmaxf(translateY, SCENE_BOTTOM + (POKEMON_HEIGHT * scaleFactor) / 2.0f),
                                                SCENE_TOP - (POKEMON_HEIGHT * scaleFactor) / 2.0f);
                
                AtualizaAnimacao();
            }
            break;

        case GLUT_KEY_PAGE_DOWN:
            if (scaleFactor > 0.2f) {
                scaleFactor -= 0.05f;
                maxOffsetX = 1.0f - 0.4f * scaleFactor;
                maxOffsetY = 1.0f - 0.5f * scaleFactor;
                AtualizaAnimacao();
            }
            break;

        case GLUT_KEY_F1: // Versao shiny
            R = 25.5; G = 178.5; B = 76.5;
            R_Asa = 82; G_Asa = 37; B_Asa = 72;
            titulo = "Shiny Dragonite"; 
            glutPostRedisplay(); 
            break; 
        case GLUT_KEY_F2: // Versao Normal
            R = 255, G = 165, B = 0;
            R_Asa = 25.5, G_Asa = 178.5, B_Asa = 76.5;
            titulo = "Dragonite";  
            glutPostRedisplay(); 
            break;
    }
    AtualizaAnimacao();
    glutPostRedisplay();
}

void AtualizaAnimacao() {
    // Pernas
    animacaoPerna += direcaoPerna * 0.02f; 
    if (animacaoPerna > 0.03f || animacaoPerna < -0.03f) {
        direcaoPerna *= -1;
    }

    // Asas
    animacaoAsa += direcaoAsa * 0.005f;
    if (animacaoAsa > 0.03f || animacaoAsa < -0.03f) {
        direcaoAsa *= -1;
    }

    // Cauda
    animacaoCauda += direcaoCauda * 0.005f;
    if (animacaoCauda > 0.03f || animacaoCauda < -0.03f) {
        direcaoCauda *= -1;
    }
}

void Dancinha() {
    // Animação de dancinha
    if (ativarRebolado) {
        animacaoRebolado += direcaoRebolado * 0.005f;
        if (animacaoRebolado > 0.04f || animacaoRebolado < -0.04f) {
            direcaoRebolado *= -1;
        }
    } else {
        animacaoRebolado = 0.0f;  // reseta se estiver desligado
    }
}

void AtualizaPiscar() {
    tempoPiscar += 0.01f;

    if (!piscando && tempoPiscar > 5.0f) { // pisca a cada ~2s
        piscando = 1;
        tempoPiscar = 0.0f;
    }

    if (piscando) {
        olhoAberto -= 0.1f;
        if (olhoAberto <= 0.0f) {
            olhoAberto = 0.0f;
            piscando = 0; // para de piscar, volta a abrir
        }
    } else if (olhoAberto < 1.0f) {
        olhoAberto += 0.05f;
        if (olhoAberto > 1.0f) olhoAberto = 1.0f;
    }
}

void AtualizaChifre() {
    anguloChifre += 0.3f * direcaoChifre;

    if (anguloChifre > 10.0f) {
        direcaoChifre = -1;
    }
    if (anguloChifre < -10.0f) {
        direcaoChifre = 1;
    }
}

void AtualizaCabeca() {
    if (pausaCabeca > 0) {
        pausaCabeca--;
        return;  // Enquanto pausa, não atualiza o ângulo
    }

    anguloCabeca += direcaoCabeca * 0.1f;  

    if (anguloCabeca >= 8.0f) {
        direcaoCabeca = -1;
        pausaCabeca = 100;  // Pausa quando chega no máximo 
    }
    if (anguloCabeca <= -8.0f) {
        direcaoCabeca = 1;
        pausaCabeca = 100;
    }
}

// Função para limitar o valor entre um mínimo e um máximo
float clamp(float valor, float min, float max) {
    if (valor < min) return min;
    if (valor > max) return max;
    return valor;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Define a área de desenho

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;

    if (w >= h) {
        // Janela mais larga
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    } else {
        // Janela mais alta
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
}

void init(void) {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Inicializa os limites de movimento baseados no scaleFactor inicial
    maxOffsetX = 1.0f - 0.4f * scaleFactor;
    maxOffsetY = 1.0f - 0.5f * scaleFactor;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dragonite 2D com OpenGL");

    init();
    rotMaoDir = 90.0f; // Inicializa a rotação da mão
    rotMaoEsq = 90.0f; // Inicializa a rotação da mão
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(display); 
    glutMainLoop();

    return 0;
}
