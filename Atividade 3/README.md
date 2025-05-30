# 🐉 Atividade 3 – Computação Gráfica

Projeto da disciplina de **Computação Gráfica** – Atividade 3.
O objetivo é desenvolver um Dragonite 2D utilizando **OpenGL** com animações e interações, incluindo movimento, escalonamento, troca de skins (normal e shiny) e controle individual dos dois braços (ombro, cotovelo e mão).

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
- Make (em Windows, recomenda-se MSYS2 ou WSL)

### 🚀 Passos para execução

1. **Abra o terminal**:

- No Linux: terminal padrão.
- No Windows: **MSYS2 MinGW 64-bit** ou **Git Bash**.

2. **Navegue até o diretório do projeto**:

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

### 🔀 Movimentação do Dragonite

| Tecla     | Ação                         |
| --------- | ---------------------------- |
| ⬅️        | Move para a esquerda         |
| ➡️        | Move para a direita          |
| ⬆️        | Move para cima               |
| ⬇️        | Move para baixo              |
| Page Up   | Aumenta o tamanho (zoom in)  |
| Page Down | Diminui o tamanho (zoom out) |

---

### 🎨 Alterar Aparência

| Tecla    | Ação                          |
| -------- | ----------------------------- |
| `t`      | Ativa modo Shiny              |
| `y`      | Ativa modo Normal             |
| `Espaço` | Alterna fundo preto ou branco |

---

### 🦾 Controle dos Braços (independentemente)

#### 🦴 Ombros

| Tecla | Ação                                     |
| ----- | ---------------------------------------- |
| `c`   | Gira ombro esquerdo sentido horário      |
| `v`   | Gira ombro esquerdo sentido anti-horário |
| `z`   | Gira ombro direito sentido horário       |
| `x`   | Gira ombro direito sentido anti-horário  |

#### 💪 Cotovelos

| Tecla | Ação                              |
| ----- | --------------------------------- |
| `d`   | Gira cotovelo esquerdo para cima  |
| `f`   | Gira cotovelo esquerdo para baixo |
| `a`   | Gira cotovelo direito para cima   |
| `s`   | Gira cotovelo direito para baixo  |

#### ✋ Mãos

| Tecla | Ação                                        |
| ----- | ------------------------------------------- |
| `e`   | Rotaciona mão esquerda sentido horário      |
| `r`   | Rotaciona mão esquerda sentido anti-horário |
| `q`   | Rotaciona mão direito sentido horário       |
| `w`   | Rotaciona mão direito sentido anti-horário  |

---

### 💃🏾 Dancinha

| Tecla | Ação                          |
| ----- | ----------------------------- |
| `p`   | Mexer a barriga na horizontal |

---

## ✨ Funcionalidades Extras

- 🦵 Pernas possuem animação de subir/descer simulando caminhada.
- 🦋 Asas possuem animação de bater.
- 🐉 Cauda com animação oscilatória.
- 👁️ Olhos piscam automaticamente após alguns segundos.
- 🎯 Cabeça balança suavemente de um lado para outro.
- 🔗 Braços possuem articulações separadas: ombro, cotovelo e mão com limites realistas.

---

## 👨‍💻 Autor

Gabriel Rosa Galdino
