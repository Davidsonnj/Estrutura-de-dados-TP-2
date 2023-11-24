# Implementação de um TAD para Manipulação de Imagens no Formato PPM
Este repositório tem por objetivo documentar os códigos elaborados no Trabalho de Programação 1 da disciplina de Estruturas de Dados [2023/2], ministrada pelo Prof. Thiago M. Paixão. 

A tarefa foi desenvolvida em dupla pelos alunos Davidson Carvalho dos Santos ([@Davidsonnj](https://github.com/Davidsonnj)) e Sofia de Alcantara ([@sofialctv](https://github.com/sofialctv)).

### Objetivo do Trabalho
Desenvolver um Tipo Abstrato de Dados (TAD) para a leitura e gravação de imagens no formato PPM (Portable Pix Map), além de realizar a conversão de imagens coloridas em imagens em níveis de cinza (escala de “preto e branco”).

# Passo-a-Passo para Executar o Programa

### Pré-requisitos

Certifique-se de ter os seguintes pré-requisitos instalados no seu sistema:

- Compilador C (por exemplo, GCC),
- Um sistema operacional compatível (Linux, Windows, macOS).

### Compilação

1. Abra o terminal ou prompt de comando.

2. Navegue até o diretório onde os arquivos do programa estão localizados.

3. Compile o programa usando o compilador C. Por exemplo, se o arquivo principal for `main.c`:

   ```bash
   gcc main.c image.c -o programa

4. O programa conta com *Menu interativo* com 3 opções distintas para manipulação do arquivo. É possível:
- Carregar imagem RGB,
- Converter essa imagem para tons de cinza e,
- Gravar imagem convertida, salvando-a em escala de cinza.

> ⚠️ **Atenção**
> 
> Durante a execução do programa, atente-se às orientações dadas no terminal, bem como as mensagens de erro que podem ser apresentadas.

# Decisões tomadas
1. **Padronização de IDs**:
static int nextID = 1000;

2. **Lista de Pacientes é uma fila**

3. **Gestão de Erros por meio de mensagens impressas**: Decidimos adicionar avisos ao usuário em casos de má execução do código para facilitar o entendimento do programa.