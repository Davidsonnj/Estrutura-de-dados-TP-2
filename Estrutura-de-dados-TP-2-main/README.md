# Simulação de Realização de Exames de Raio-X
Este repositório tem por objetivo armazenar os códigos elaborados no Trabalho de Programação 2 da disciplina de Estruturas de Dados [2023/2], ministrada pelo Prof. Thiago M. Paixão ([@thiagopx](https://github.com/thiagopx)).

### Autores

- Davidson Carvalho dos Santos: [@Davidsonnj](https://github.com/Davidsonnj)
- Sofia de Alcantara: [@sofialctv](https://github.com/sofialctv)
<hr>

### Objetivo do Trabalho
O trabalho consiste em simular o processo de realização de exames de raio-X em um hospital, com ênfase na organização da fila para laudo médico. A cada momento, pacientes chegam ao hospital e exames são realizados mediante disponibilidade de aparelhos. A _IA_ (simulada) sugere diagnósticos preliminares e os exames são encaminhados para laudo de acordo com a disponibilidade da equipe de radiologistas. Métricas de desempenho, como tempo médio de laudo e exames realizados fora do prazo, são calculadas. O objetivo é entender o processo e avaliar a eficiência do sistema, contribuindo para futuras otimizações.

As principais competências a serem desenvolvidas neste trabalho incluem:
- Implementação de um sistema de simulação.
- Uso e implementação de filas.
- Implementação de módulos e TADS.

# Instalação e Execução ?????
Certifique-se de conter pré-instalado em seu sistema um **compilador C (por exemplo, GCC)**. 

Para instalar o programa em seu computador, siga os passos a seguir:
1. Clone o repositório em seu Desktop:
```bash
  git clone //COPIAR ENDEREÇO DO REPOSITÓRIO!!!!!!!!!!!!!!!!
```

2. Compile o código e execute:
```bash
  gcc -o tp2ED main.c
  ./T2ED
```

Uma opção alternativa consiste em baixar o .zip com a pasta do projeto, extrair os arquivos, compilar e executar.

⚠️ **Atenção**: Durante a execução do programa, atente-se às orientações dadas no terminal, bem como as mensagens de erro que podem ser apresentadas.

# Funcionamento do programa
Ao executar o programa, o usuário será informado a cada 10 unidades de tempo, o relatório das métricas do sistema, que são as seguintes:
- **Tempo médio de laudo:** Esta métrica calcula o tempo médio que os exames ocupam a fila para laudo. Quanto menor o tempo médio de espera, mais eficiente é o sistema.
- **Tempo médio de laudo por patologia:** Calcula o tempo médio que os exames de uma patologia específica aguardam na fila antes de serem laudados, o que ajuda a identificar se alguma patologia está enfrentando atrasos significativos.
- **Quantidade de exames realizados após o limite de tempo estabelecido:** Esta métrica rastreia quantos exames foram laudados após o limite de tempo aceitável estabelecido pelo hospital (7.200 unidades de tempo). Isso ajuda a avaliar a capacidade do sistema de cumprir prazos críticos.

Vale ressaltar que, no total, a simulação tem tempo máximo de 43.200 unidades de tempo.

## Organização do projeto
O trabalho conta com os principais arquivos:
- `banco.txt`: que contém nosso _banco de dados_ de pacientes


### Principais Estruturas
A seguir, temos a descrições das principais estruturas de dados utilizadas no programa. Utilizamos em nosso trabalho o conceito de listas encadeadas para manipulação das imagens e dos dados extraidos dela. Utilizamos também dois tipos abstratos de dados (TADs): O tipo img e o tipo lista, que descreveremos a seguir.

### ListPatient


### __IMG:__

O TAD img lida com o struct IMG, que é a estrutura que lida com as informações das imagens .pgm utilizadas no programa. O struct IMG possui todas informações do arquivo da imagem e um vetor que armazena o histograma da imagem. O TAD lida principalmente com a leitura e escrita das imagens. 

```
typedef struct {
  char tipo[5];
  int largura, altura;
  int brilhoMax;
  unsigned char **mat;
  unsigned int hist[256];
} IMG;
```

### __Lista:__

O TAD lista é o responsável pelas operações envolvendo listas encadeadas. Ele engloba dois tipos dinstintos de lista, cada uma com uma finalidade e um node próprio. A _Lista_ é composta pelo _ListaNode_, struct que guarda um ponteiro para um IMG. Ela é utilizada na parte _offline_, durante o processo de extração dos histogramas médios.

```
//Node utilizado pela Lista

struct listaNode {
  IMG *img;
  ListaNode *next;
};

```
Já o outro tipo de lista, o _ListaH_, utiliza o _HistNode_. Esse tipo de node armazena o diretório e o histograma médio de um local. Esse tipo de lista é utilizado na parte _online_ do programa, para listar todos os histogramas médios que serão comparados com o histograma da imagem na query.

```
//Node utilizado pela ListaH

struct histNode{
  char * local;
  unsigned int hist[256];
  HistNode *next;
};
```


<hr >

# Decisões tomadas
1. **Padronização de IDs**:
static int nextID = 1000;

2. **Lista de Pacientes é uma fila**

3. **Gestão de Erros por meio de mensagens impressas**: Decidimos adicionar avisos ao usuário em casos de má execução do código para facilitar o entendimento do programa.

