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

> 📰 _A especificação completa do trabalho pode ser lida acessando o arquivo specification.pdf_

# Instalação e Execução
Certifique-se de conter pré-instalado em seu sistema um **compilador C (por exemplo, GCC)**. 
 
Para instalar o programa em seu computador, siga os passos a seguir:
1. Clone o repositório em seu Desktop e salve-o no local desejado:
```bash
git clone https://github.com/Davidsonnj/Estrutura-de-dados-TP-2
```

2. Abra seu terminal, escreva ```cd``` e cole o caminho no qual o repositório está salvo, como no exemplo:
```
cd C:\Users\ThiagoPX\Documents\Estrutura-de-dados-TP-2\TP2_ED
```
3. Compile o código e execute-o digitando o seguinte comando:
```
make
```
Como resultado, serão gerados os arquivos ```hospital.exe```, ```main.o``` e ```simulation.o```. 

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
- **`data.txt`**: contém nosso _banco de dados_ de pacientes, com seus respectivos nomes, CPF e idade;
- **`simulation.c`**: contém as principais funções e structs que viabilizam a simulação do exame de raio-X;
- **`simulation.h`**: contém o cabeçalho das funções utilizadas;
- **`main.c`**: onde as funções e structs da simulação são implementadas; 

### Principais Estruturas & Decisões de Implementação
A seguir, temos a descrições das principais estruturas de dados utilizadas no programa, bem como as principais decisões tomadas durante a implementação

### __ListPatient__

1. **Padronização de IDs**:
static int nextID = 1000;
2. struct Patient

### __QueueExam__

### __QueueReport__

### __ListPatient__
- é uma lista

### __ExamRecord__

### __Pathologies__