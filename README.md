# Goblin Jump!

Um jogo simples de plataforma feito em C++ utilizando [SFML 3.0.0](https://www.sfml-dev.org/) e compilado com MinGW-w64 via MSYS2.

---

## 🚀 Tutorial: Instalando e Configurando SFML 3.0.0 com MSYS2 e MinGW-w64

### 1. Instale o [MSYS2](https://www.msys2.org/)

Baixe e instale o MSYS2 conforme o site oficial. Após instalar, abra o terminal **MSYS2 MinGW 64-bit**.

### 2. Atualize os pacotes do MSYS2

```sh
pacman -Syu
# Feche o terminal se for solicitado e abra novamente, então:
pacman -Su
```

### 3. Instale o MinGW-w64 (compilador g++)

```sh
pacman -S mingw-w64-x86_64-gcc
```

### 4. Instale o SFML 3.0.0 para MinGW-w64

> **Atenção:**  
> O pacote do SFML deve ser **da mesma arquitetura** do seu compilador!  
> Se você usa `mingw-w64-x86_64-gcc`, instale `mingw-w64-x86_64-sfml`.

```sh
pacman -S mingw-w64-x86_64-sfml
```

### 5. Configure as variáveis de ambiente

Adicione o caminho do MinGW-w64 do MSYS2 ao seu `PATH` do Windows para poder usar o `g++` e as DLLs do SFML fora do terminal MSYS2:

- Caminho típico:
  ```
  C:\msys64\mingw64\bin
  ```
- Para adicionar:
  1. Pesquise por "variáveis de ambiente" no Windows.
  2. Edite a variável `Path` do usuário ou do sistema.
  3. Adicione o caminho acima.

### 6. Compile o projeto

No terminal (cmd, PowerShell ou MSYS2 MinGW 64-bit), execute:

```sh
g++ -fdiagnostics-color=always -g main.cpp -o main.exe -I"C:/msys64/mingw64/include" -L"C:/msys64/mingw64/lib" -lsfml-graphics -lsfml-window -lsfml-system
```

Ou simplesmente:

```sh
make
```
(se estiver usando o Makefile incluso)

### 7. Execute o jogo

```sh
main.exe
```

---

## 🕹️ Sobre a Implementação

O jogo é um "infinite jumper" simples, onde um goblin pula automaticamente de plataforma em plataforma.

### Principais blocos lógicos do código:

#### **1. Inicialização e carregamento de recursos**
```cpp
Texture tx_player, tx_bg, tx_plat;
if (!tx_player.loadFromFile("assets/goblin.png")) { ... }
if (!tx_bg.loadFromFile("assets/background_1.png")) { ... }
if (!tx_plat.loadFromFile("assets/platform_1.png")) { ... }
```
Carrega as texturas do jogador, fundo e plataformas. Se algum arquivo não for encontrado, o jogo encerra.

#### **2. Criação das plataformas**
```cpp
point plat[20];
for (int i = 0; i < 10; i++) {
    plat[i].x = rand()%400;
    plat[i].y = rand()%533;
}
```
Gera posições aleatórias para as plataformas.

#### **3. Controle do jogador**
```cpp
if (Keyboard::isKeyPressed(Keyboard::Key::Right)) { x+=3; }
if (Keyboard::isKeyPressed(Keyboard::Key::Left))  { x-=3; }
```
Permite mover o goblin para a esquerda e direita.

#### **4. Lógica de câmera**
```cpp
if (y < h) {
    for (int i = 0; i < 10; i++) {
        y = h;
        plat[i].y = plat[i].y - dir_y;
        if (plat[i].y > 533) {
            plat[i].y = 0;
            plat[i].x = rand()%400;
        }
    }
}
```
Quando o jogador sobe, as plataformas descem, simulando uma câmera que acompanha o goblin.

#### **5. Gravidade e pulo automático**
```cpp
dir_y += 0.2f;
y += dir_y;
if (y > 500) {
    dir_y = -10;
}
```
Aplica gravidade e faz o goblin pular automaticamente ao atingir o chão.

#### **6. Colisão com plataformas**
```cpp
for (int i = 0; i < 10; i++) {
    if ((x + 48 > plat[i].x) &&
        (x < plat[i].x + 69) &&
        (y + 48 >= plat[i].y) &&
        (y + 48 <= plat[i].y + 5) &&
        (dir_y > 0)) {
        dir_y = -10;
        y = plat[i].y - 48;
    }
}
```
Detecta se o goblin está pousando sobre uma plataforma e faz ele pular novamente.

#### **7. Renderização**
```cpp
sPlayer.setPosition(Vector2f(x, y));
app.draw(sBackground);
app.draw(sPlayer);
for (int i = 0; i < 10; i++) {
    sPlatform.setPosition(Vector2f(static_cast<float>(plat[i].x), static_cast<float>(plat[i].y)));
    app.draw(sPlatform);
}
app.display();
```
Desenha o fundo, o jogador e todas as plataformas na tela.

---

## 📦 Estrutura de Pastas Recomendada

```
stu-goblin-jump/
├── assets/
│   ├── goblin.png
│   ├── background_1.png
│   └── platform_1.png
├── .vscode/
│   ├── tasks.json
│   ├── launch.json
│   └── c_cpp_properties.json
├── main.cpp
├── makefile
└── README.md
```

---

## 🎮 Controles

- **Seta Direita (→)**: Move o goblin para a direita
- **Seta Esquerda (←)**: Move o goblin para a esquerda
- **Pulos**: Automáticos quando o goblin toca uma plataforma ou o chão

---

## 🛠️ Desenvolvimento no VS Code

O projeto inclui configurações para VS Code:

- **Build**: `Ctrl+Shift+B` ou use "Tasks: Run Build Task"
- **Debug**: `F5` para compilar e debugar
- **Run**: Use a task "Build and Run" para compilar e executar

### Configuração dos arquivos VS Code

Para configurar o projeto no VS Code, crie uma pasta `.vscode` no diretório raiz e adicione os seguintes arquivos:

#### **1. `.vscode/c_cpp_properties.json`**
Configura o IntelliSense e as ferramentas de análise de código:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/msys64/mingw64/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/msys64/mingw64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

#### **2. `.vscode/tasks.json`**
Define as tarefas de compilação:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "C/C++: g++ build active file",
            "command": "C:/msys64/mingw64/bin/g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I",
                "C:/msys64/mingw64/include",
                "-L",
                "C:/msys64/mingw64/lib",
                "-lsfml-graphics",
                "-lsfml-window",
                "-lsfml-system"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": ["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Compilar com SFML usando g++"
        },
        {
            "type": "shell",
            "label": "Build and Run",
            "command": "C:/msys64/mingw64/bin/g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I",
                "C:/msys64/mingw64/include",
                "-L",
                "C:/msys64/mingw64/lib",
                "-lsfml-graphics",
                "-lsfml-window",
                "-lsfml-system",
                "&&",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": ["$gcc"],
            "group": "build",
            "detail": "Compilar e executar com SFML"
        }
    ]
}
```

#### **3. `.vscode/launch.json`**
Configura o debugger:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C/C++: g++ build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/msys64/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "Habilitar pretty-printing para gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++ build active file"
        }
    ]
}
```

### Como usar as configurações:

1. **Compilar**: Pressione `Ctrl+Shift+B` e escolha "C/C++: g++ build active file"
2. **Compilar e Executar**: Use `Ctrl+Shift+P` → "Tasks: Run Task" → "Build and Run"
3. **Debugar**: Pressione `F5` para compilar e iniciar o debugger
4. **Breakpoints**: Clique na margem esquerda do editor para adicionar pontos de interrupção

> **Nota**: Certifique-se de que os caminhos para o MSYS2 (`C:/msys64/mingw64/`) estejam corretos no seu sistema.

---

## 📝 Observações

- Certifique-se de que as DLLs do SFML estejam acessíveis (no mesmo diretório do `.exe` ou no PATH).
- O código foi testado com SFML 3.0.0, MinGW-w64 (MSYS2) e Windows 10/11.
- Para dúvidas sobre SFML: [Documentação Oficial](https://www.sfml-dev.org/documentation/3.0.0/)

---

## 🎯 Dimensões do Jogo

- **Janela**: 400x533 pixels
- **Player (Goblin)**: 48x48 pixels
- **Plataformas**: 69x22 pixels
- **Framerate**: 60 FPS

---
