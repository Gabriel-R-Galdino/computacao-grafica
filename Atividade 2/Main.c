#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int R = 255, G = 165, B = 0;
int R_Asa = 25.5, G_Asa = 178.5, B_Asa = 76.5;
int backgroundColor = 0;
GLubyte textoR = 255, textoG = 255, textoB = 255;
char *titulo = "Dragonite";

void display(void);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void DesenhaTexto(char *string);
void DesenhaPokemon(void);

// Função para desenhar círculo preenchido
void DesenhaCirculo(float x, float y, float radius, int segments, int filled, int outlined) {
    if (filled) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * 3.1415926f * i / segments;
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }

    if (outlined) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * 3.1415926f * i / segments;
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
    }
}

void DesenhaElipse(float x, float y, float rx, float ry, int segments, int filled) {
    if (filled) glBegin(GL_POLYGON);
    else glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * i / segments;
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
}

void DesenhaAsa(int lado) {
    float s = (lado == 0) ? -1.0f : 1.0f;
    float scale = 1.2f;
    float offsetY = -0.05f;     // mover na vertical
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
    float s = (lado == 0) ? -1.0f : 1.0f; // espelha se for o braço esquerdo
    float offsetX = 0.25f;         // distância do centro
    float offsetY = -0.2f;         // altura em relação ao centro
    float scale = 1.1f;

    float arm[][2] = {
        {0.0f, 0.0f},
        {0.05f, -0.05f},
        {0.10f, -0.10f},
        {0.15f, -0.15f},
        {0.18f, -0.25f},
        {0.15f, -0.30f},
        {0.10f, -0.32f},
        {0.05f, -0.28f},
        {0.0f, -0.20f},
        {-0.02f, -0.10f}
    };

    // Parte laranja 
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 10; i++) {
        float x = s * arm[i][0] * scale + s * offsetX;
        float y = arm[i][1] * scale + offsetY;
        glVertex2f(x, y);
    }
    glEnd();

    // Contorno preto
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++) {
        float x = s * arm[i][0] * scale + s * offsetX;
        float y = arm[i][1] * scale + offsetY;
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1.0f);

      // Garras triangulares diagonais
      float clawBaseY = -0.25f;
      float clawHeight = 0.04f;
      float clawWidth = 0.015f;
  
      float clawXOffsets[3] = {0.11f, 0.15f, 0.18f}; 
      float clawTilt[3] = {0.015f, 0.0f, -0.015f};   
  
      float clawShiftX = -0.02f; 
  
      for (int i = 0; i < 3; i++) {
          float cx = s * (clawXOffsets[i] + clawShiftX) * scale + s * offsetX;
          float cy = clawBaseY * scale + offsetY;
  
          float tipX = cx + s * clawTilt[i];
          float tipY = cy - clawHeight * scale;
  
          glColor3f(1.0f, 1.0f, 1.0f); 
          glBegin(GL_TRIANGLES);
          glVertex2f(cx - s * clawWidth, cy);
          glVertex2f(cx + s * clawWidth, cy);
          glVertex2f(tipX, tipY);
          glEnd();
  
          // Contorno preto da garra
          glColor3f(0.0f, 0.0f, 0.0f);
          glBegin(GL_LINE_LOOP);
          glVertex2f(cx - s * clawWidth, cy);
          glVertex2f(cx + s * clawWidth, cy);
          glVertex2f(tipX, tipY);
          glEnd();
      }
}

void DesenhaPerna(int lado) {
    float s = (lado == 0) ? -1.0f : 1.0f;
    float offsetX = 0.29f;
    float offsetY = -0.7f;
    float scale = 1.1f;

    // Formato da perna 
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
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 12; i++) {
        float x = s * leg[i][0] * scale + s * offsetX;
        float y = leg[i][1] * scale + offsetY;
        glVertex2f(x, y);
    }
    glEnd();

    // Contorno preto
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 12; i++) {
        float x = s * leg[i][0] * scale + s * offsetX;
        float y = leg[i][1] * scale + offsetY;
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1.0f);

    // Garras triangulares 
    float clawBaseY = -0.28f;
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
    float offsetY = -0.75f; 
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
    // Cabeça principal
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    DesenhaCirculo(0.0f, 0.0f, 0.25f, 100, 1, 0);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Focinho 
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    DesenhaCirculo(0.0f, -0.20f, 0.2f, 100, 1, 0);

    // Narinas
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaCirculo(-0.05f, -0.20f, 0.015f, 50, 1, 0);
    DesenhaCirculo(0.05f, -0.20f, 0.015f, 50, 1, 0);

    glColor3f(1.0f, 1.0f, 1.0f);
    DesenhaElipse(-0.1f, 0.05f, 0.05f, 0.08f, 100, 1);  
    DesenhaElipse(0.1f, 0.05f, 0.05f, 0.08f, 100, 1);

    // Contorno preto
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaElipse(-0.1f, 0.05f, 0.05f, 0.08f, 100, 0);  
    DesenhaElipse(0.1f, 0.05f, 0.05f, 0.08f, 100, 0);

    // Pupila preta
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaElipse(-0.1f, 0.05f, 0.02f, 0.04f, 100, 1);
    DesenhaElipse(0.1f, 0.05f, 0.02f, 0.04f, 100, 1);

    // Brilho (reflexo)
    glColor3f(1.0f, 1.0f, 1.0f);
    DesenhaElipse(-0.085f, 0.05f, 0.01f, 0.015f, 100, 1);
    DesenhaElipse(0.085f, 0.05f, 0.01f, 0.015f, 100, 1);

    // Chifrinho central
    glColor3f(R / 255.0f, G / 255.0f, B/ 255.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(-0.05f, 0.23f);
        glVertex2f(0.05f, 0.23f);
    glEnd();

    glEnable(GL_LINE_SMOOTH); // Ativa suavização de linhas
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Define o melhor modo de suavização
    // Chifres laterais
    glColor3f(0.9f, 0.9f, 0.7f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.1f, 0.21f);
        glVertex2f(-0.2f, 0.4f);
        glVertex2f(-0.3f, 0.35f);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.1f, 0.21f);
        glVertex2f(0.2f, 0.4f);
        glVertex2f(0.3f, 0.35f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
    
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

    glTranslatef(0.0f, 0.0f, 0.0f); // Centraliza
    glScalef(0.8f, 0.8f, 0.8f);     // Reduz o tamanho pela metade (ajuste esse valor)

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

    glColor3f(R / 255.0f, G / 153.0f, B / 0.0f);
    glColor3f(R_Asa / 255.0f, G_Asa / 153.0f, B_Asa / 0.0f);
    glPushMatrix();
    glScalef(0.8f, 0.8f, 1.0f);
    
    DesenhaCenario();
    
    glPopMatrix();

    DesenhaTexto(titulo);
    glFlush();
}

void DesenhaTexto(char *string) {
    glColor3ub(textoR, textoG, textoB);
    glRasterPos2f(-0.1f, 0.9f);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: exit(0); // ESC
        case 'r': // Versao shiny
            R = 25.5; G = 178.5; B = 76.5;
            R_Asa = 82; G_Asa = 37; B_Asa = 72;
            titulo = "Shiny Dragonite"; 
            glutPostRedisplay(); break;
        case 't': // Versao Normal
            R = 255, G = 165, B = 0;
            R_Asa = 25.5, G_Asa = 178.5, B_Asa = 76.5; 
            titulo = "Dragonite";
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
    }
}

void specialKeyboard(int key, int x, int y) {
    switch (key) {
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
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dragonite 2D com OpenGL");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(display); 
    glutMainLoop();

    return 0;
}
