# 🏢 Atividade 7 – Computação Gráfica

Projeto da disciplina de **Computação Gráfica** – Atividade 7.  
O objetivo é desenvolver uma **Torre 3D dos Vingadores**, utilizando **OpenGL (GLUT)** com profundidade, interatividade via mouse e teclado, zoom e rotação.

---

## 🗂️ Estrutura de Pastas

```
.
├── build/       # Pasta que armazena o executável
│   └── main     # Arquivo executável
├── main.c       # Código-fonte principal
├── Makefile     # Script de compilação
└── README.md    # Instruções do projeto
```

---

## ▶️ Como Compilar e Executar

### ✅ Requisitos

- GCC instalado (Linux, WSL, MinGW ou Git Bash no Windows)
- Biblioteca OpenGL (`freeglut` ou `glut`)
- Make (recomendado uso de MSYS2 ou WSL no Windows)

### 🚀 Passos

1. **Abra o terminal**:

   - No Linux: terminal padrão.
   - No Windows: **MSYS2 MinGW 64-bit** ou **Git Bash**.

2. **Vá até o diretório do projeto**:

```bash
cd caminho/para/seu/projeto
```

3. **Compile com `make`**:

```bash
make
```

4. **Execute com `make run`**:

```bash
make run
```

---

## 🎮 Controles

### 🖱️ Mouse

| Ação                    | Descrição                            |
| ----------------------- | ------------------------------------ |
| Clique e arraste (⬅➡⬆⬇) | Rotaciona a câmera ao redor da torre |
| Scroll (subir/descer)   | Zoom in / Zoom out na cena           |

---

### ⌨️ Teclado

#### 🔼 Teclas Especiais

| Tecla         | Ação                               |
| ------------- | ---------------------------------- |
| Seta esquerda | Rotaciona a câmera para a esquerda |
| Seta direita  | Rotaciona a câmera para a direita  |
| Seta cima     | Aumenta a altura da câmera         |
| Seta baixo    | Diminui a altura da câmera         |

#### 🔡 Teclas Comuns

| Tecla | Ação               |
| ----- | ------------------ |
| `+`   | Aproxima (zoom in) |
| `-`   | Afasta (zoom out)  |
| `ESC` | Encerra o programa |

---

## 🧱 Estrutura 3D da Torre

A torre é composta por:

- **Base Azul** com profundidade
- **Grades Amarelas** nas laterais e triângulo frontal
- **Plataforma** com volume 3D
- **Topo Inclinado** azul escuro com profundidade
- **Logo dos Vingadores** estilizado (círculo com A e seta)
- **Texto flutuante** com o nome do autor

---

## ✨ Funcionalidades Extras

- Câmera interativa com rotação, zoom e elevação
- Limites para impedir zoom exagerado ou ângulo de câmera irreal
- Interação fluida via mouse + teclado
- Logo dos Vingadores desenhado com OpenGL (sem texturas)

---

## 👨‍💻 Autor

Gabriel Rosa Galdino – 08/07/2025
