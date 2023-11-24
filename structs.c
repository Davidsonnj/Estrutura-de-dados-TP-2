#include "structs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Quantidade máxima de aparelhos disponíveis */
#define MAX_MACHINES 4

struct Patient {

  char name[50]; /* Nome do paciente */
  char cpf[20];  /* CPF do paciente */
  int age;       /* Idade do paciente */
  int id;        /* Identificador do paciente */
};

struct ListOfPatients {
  int count;       /* Contador de pacientes */
  ListNode *first; /* Ponteiro para o primeiro paciente da lista */
  ListNode *last;  /* Ponteiro para o último paciente da lista */
};

struct list_node {
  patient *patients; /* Registro do paciente */
  ListNode *next;    /* Ponteiro para o próximo paciente */
  ListNode *prev;    /* Ponteiro para o paciente anterior */
};

struct QueueExams {

  QueueNode *front; /* Ponteiro para o primeiro exame da fila */
  QueueNode *rear;  /* Ponteiro para o último exame da fila */
};

struct Queue_Node {
  int id;          /* Identificador dos pacientes da fila */
  QueueNode *next; /* Ponteiro para o próximo paciente da fila */
};

struct Machines {
  int examDuration; /* Duração de exame do aparelho */
  int patientID;    /* ID do paciente que está ocupando a máquina */
  int time;
};

struct ExamRecord {
  int id;
  int finishTime;   /* Paciente sai da máquina    */
  Pathologie *path;
  ExamRecord *next;
};

struct QueueReport {
  ExamRecord *front;       /* Ponteiro para o primeiro registro de exame na fila de laudos */
  ExamRecord *rear;        /* Ponteiro para o último registro de exame na fila de laudos */
};

struct Pathologies {

  char condition[20]; /* Condição do Paciente */
  int urgency;        /* Gravidade da condição */
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                     FUNÇÕES RELATIVAS AO BANCO DE DADOS (LISTA) DE PACIENTES                                      */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

patient *newPatient(char name[], char cpf[], int age, int id) {

  patient *newPatient = (patient *)malloc(sizeof(patient));  /* Aloca memoria para registro do pacientes */

  strcpy(newPatient->name, name);   /* Define o nome do paciente */
  strcpy(newPatient->cpf, cpf);     /* Define o cpf do paciente */
  newPatient->age = age;            /* Define a idade do paciente */
  newPatient->id = id;              /* Define o ID do paciente */

  return newPatient;
};

ListPatient *ListPatient_create() {
ListPatient *list = (ListPatient *)malloc(sizeof(ListPatient)); /* Aloca memoria para lista de pacientes */

  list->count = 0;        /* Inicializa o contador com 0 pacientes */
  list->first = NULL;     /* Inicializa o primeiro elemento da lista como vazio */
  list->last = NULL;      /* Inicializa o último elemento da lista como vazio */

  return list;            /* Retorna a lista de pacientes */
};

int ListPatient_size(ListPatient *list) {
  return list->count; /* retorna tamanho da lista de pacientes */
};

int ListEmpty(ListPatient *list) { 
  return ListPatient_size(list) == 0; 
}

void ListPatient_insert(ListPatient *list, patient *patients) {

  ListNode *node = (ListNode *)malloc(sizeof(ListNode));     /* Aloca memoria para cada nó de pacientes */
  node->patients = patients;                                 /* Atribui o paciente ao nó */
  node->next = list->first;                                  /* O próximo nó recebe o primeiro nó */
  node->prev = NULL;                                         /* O nó anterior aponta para NULL */

  /* Verifica se não lista está vazia */
  if (!ListEmpty(list))
    list->first->prev = node;   /* O nó anterior do primeiro elemento da lista (que é um nó) recebe o nó criado */
  else
    list->last = node;          /* Lista recebe o último nó recebe */

  list->first = node;           /* Primeiro elemento da lista pacientes recebe o nó criado */
  list->count++;                /* Quantidade de registro aumentam */
}

int ListPatient_remove(ListPatient *list, patient *patients) {

  ListNode *node = list->first;      /* Cria nó auxiliar para percorrer a lista */
  ListNode *prev = NULL;             /* Aponta para o nó anterior */

  while (node != NULL) {
    if (node->patients == patients)  /* Se o atual nó contém o elemento a ser removido... */
    {
      if (prev == NULL)              /* Se o elemento a ser removido está no começo da lista... */
      {
        list->first = node->next;
      } 
      else /* Caso o elemento esteja no meio ou fim da lista... */
        prev->next = node->next;

      free(node);
      return 1; /* Sucesso ao remover paciente */
    } 
    else 
    {
      prev = node;
      node = node->next;
    }
  }

  return 0; /* Sucesso ao remover paciente */
}

void ListPatient_free(ListPatient *list) {
  ListNode *node = list->first;

  while (node != NULL) {
    ListNode *temp = node->next;
    free(node);
    node = temp;
  }
  free(list);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                     FUNÇÕES RELATIVAS À FILA DE EXAMES                                            */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QueueExams *QueueExams_create() {
  QueueExams *q = (QueueExams *)malloc(sizeof(QueueExams));   /* Aloca memoria para a fila de exames */
  q->front = q->rear = NULL;                                  /* Declara o primeiro e o último ID como vazios */
  return q;                                                   /* Retorna a fila de exames */
}

int QueueEmpty(QueueExams *q) { 
  return q->front == NULL; 
}

void QueueEnqueue(QueueExams *q, int newID) {
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode)); /* Aloca memoria para um novo ID */
  node->id = newID;       /* Atribui o identificador (ID) ao novo nó da fila */
  node->next = NULL;      /* O próximo nó da fila fica vazio */

  if (QueueEmpty(q))
    q->front = node;      /* Novo nó vai para frente da fila */
  else
    q->rear->next = node; /* Novo nó vai para o último lugar da fila */

  q->rear = node;         /* Novo nó vai para o último lugar da fila */
}

void QueueDequeue(QueueExams *q) {
  QueueNode *temp = q->front;    /* Armazenamento temporario para nó que será removido */

  if (q->front == q->rear) {
    q->front = q->rear = NULL;   /* Se houver apenas um elemento na fila */
  } else {
    q->front = q->front->next;   /* Move o ponteiro da frente para o próximo elemento */
  }
  free(temp);  /* Libera a memória do nó removido */
}

void QueueFree(QueueExams *q) {
  QueueNode *p = q->front;

  while (p != NULL) {          /* Enquanto houver elementos na fila... */
    QueueNode *temp = p->next; /* Libera a memória do nó removido */
    free(p);
    p = temp;
  }
  free(q);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                            FUNÇÕES RELATIVAS AOS APARELHOS                                        */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que inicializa o array de máquinas */
Machines *initializeMachines() {
  Machines *allMachines = (Machines *)malloc(5 * sizeof(Machines)); /* Array da struct Machine. Cada índice do array corresponde a uma máquina */
  for (int i = 0; i <= MAX_MACHINES; i++) {
    allMachines[i].examDuration = 0;
    allMachines[i].patientID = 0;     /* Nenhum paciente no começo */
    allMachines[i].time = 0;
  }
  return allMachines;
}

void CheckMachines(Machines* machines, int time){
  for (int i = 0; i <= MAX_MACHINES; i++){
    if ((machines[i].examDuration + machines[i].time) == time) {
        // fazer funcao que faz laudo
        machines[i].examDuration = 0;
        machines[i].patientID = 0;
        return i;
    }
  }
}

void *limpar_Maquinas(Machines *mach){
  free(mach);
}

/* Função que checa a existência de alguma máquina livre */
int checkMachinesAvailability(Machines *machines) {
  for (int i = 0; i <= MAX_MACHINES; i++) {
    if (machines[i].examDuration == 0)
      return i; /* Retorna o índice da primeira máquina disponível */
    }
  return -1; /* Em caso de todas as máquinas ocupadas */
}

void takingExam(QueueExams *examQueue, Machines *machines, int time) {

    int availableMachineIndex = checkMachinesAvailability(machines);

    /* Se houver pelo menos uma máquina ocupada */
    if (availableMachineIndex != -1) {
      int patientID = examQueue->front->id;  /* Recebe o ID do primeiro paciente da fila */
      QueueDequeue(examQueue);               /* Remove o paciente da fila de exames */

      /* Tempo de duração do exame: nº inteiro pseudo-aleatório entre 5 e 10 */
      int examDuration = rand() % 6 + 5;

      machines[availableMachineIndex].examDuration = examDuration; /* Máquina fica ocupada */
      machines[availableMachineIndex].patientID = patientID;       /* O paciente de ID x está usando a máquina */
    }
}

void releaseMachines(Machines *allMachines) { 
  free(allMachines); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                     FUNÇÕES RELATIVAS À FILA DE LAUDOS */

QueueReport *QueueReport_create() {
  QueueReport *q = (QueueReport *)malloc(sizeof(QueueReport));
  q->front = q->rear = NULL; /* Fila começa vazia */
  return q;
}

int QueueReportEmpty(QueueReport *q) { 
  return q->front == NULL; 
}

QueueReport *QueueEnqueue_registerRecord(QueueReport *q, int id, int time, Pathologie *path){

  ExamRecord *r_record = (ExamRecord *)malloc(sizeof(ExamRecord)); /* Aloca memoria para um novo ID */
  r_record->id = id;          /* Atribui o identificador (ID) ao novo nó da fila */
  r_record->finishTime = time;
  r_record->path = path;
  r_record->next = NULL;      /* O próximo nó da fila fica vazio */

  if (QueueReportEmpty(q))
    q->front = r_record;      /* Novo nó vai para frente da fila */
  else
    q->rear->next = r_record; /* Novo nó vai para o último lugar da fila */

  q->rear = r_record;         /* Novo nó vai para o último lugar da fila */
}


void addExamRecord_toQueueReport(QueueReport *q, ExamRecord *record, int time) {

  /* Em caso de registro inválido */
  if (q == NULL || record == NULL) {
    return;
  }

  /* Se a fila de laudos estiver vazia, o primeiro e o último elemento devem ser o novo registro */
  if (QueueReportEmpty(q)) {
    q->front = q->rear = record;

  } else {
    q->rear->next = record;
    q->rear = record;
  }
  record->next = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                # PATOLOGIAS #                                                     */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Pathologie *CreatePathologie(char condition[20], int severity) {
  Pathologie *p = (Pathologie *)malloc(sizeof(Pathologie));
  strcpy(p->condition, condition);
  p->urgency = severity;
  return p;
}

Pathologie *Assessing_Pathologies() {
  srand(time(NULL));

  int numero_aleatorio = rand() % 100 + 1;

  switch (numero_aleatorio) {
  case 1 ... 30:
    return CreatePathologie("Saúde Normal", 1);
  case 31 ... 50:
    return CreatePathologie("Bronquite", 2);
  case 51 ... 70:
    return CreatePathologie("Pneumonia", 3);
  case 71 ... 85:
    return CreatePathologie("Fratura de Fêmur", 4);
  case 86 ... 100:
    return CreatePathologie("Apendicite", 4);
  default:
    return NULL;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                # PRINTS #                                                         */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void patient_print(ListPatient *l){
   for (ListNode *p = l->first; p != NULL; p = p->next)
   {
    printf("Name: %s\n", p->patients->name);
    printf("CPF: %s\n", p->patients->cpf);
    printf("Age: %d\n", p->patients->age);
    printf("ID: %d\n", p->patients->id);
    printf("\n");
   }
   printf("\n");
}

void QueueExams_print(QueueExams *exams){
  
  for(QueueNode *patient = exams->front; patient != NULL; patient = patient->next  ){
    printf("%d ", patient->id);
  }

}