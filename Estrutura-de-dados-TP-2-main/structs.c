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

/* Fazer funções que a lista de maquina */
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

/* Função que cria novo paciente */
patient *newPatient(char name[], char cpf[], int age, int id) {

  patient *newPatient = (patient *)malloc(sizeof(patient));  /* Aloca memoria para registro do pacientes */

  strcpy(newPatient->name, name);   /* Define o nome do paciente */
  strcpy(newPatient->cpf, cpf);     /* Define o cpf do paciente */
  newPatient->age = age;            /* Define a idade do paciente */
  newPatient->id = id;              /* Define o ID do paciente */

  return newPatient;
};

/* Função que cria a lista de paciente */
ListPatient *ListPatient_create() {
ListPatient *list = (ListPatient *)malloc(sizeof(ListPatient)); /* Aloca memoria para lista de pacientes */

  list->count = 0;        /* Inicializa o contador com 0 pacientes */
  list->first = NULL;     /* Inicializa o primeiro elemento da lista como vazio */
  list->last = NULL;      /* Inicializa o último elemento da lista como vazio */

  return list;            /* Retorna a lista de pacientes */
};

/* Função que retorna a quantidade de paciente */
int ListPatient_size(ListPatient *list) {
  return list->count; /* retorna tamanho da lista de pacientes */
};

/* Função que verifica se a lista esta vazia */
int ListEmpty(ListPatient *list) { 
  return ListPatient_size(list) == 0; 
}

/* Função que insere um novo paciente a lista */
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

/* Função que remove paciente da lista */
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

/* Função que remove/libera todos os pacientes da memoria */
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

/* Função que cria a fila de exames */
QueueExams *QueueExams_create() {
  QueueExams *q = (QueueExams *)malloc(sizeof(QueueExams));   /* Aloca memoria para a fila de exames */
  q->front = q->rear = NULL;                                  /* Declara o primeiro e o último ID como vazios */
  return q;                                                   /* Retorna a fila de exames */
}

/* Verifica se a fila de exame está vazia */
int QueueEmpty(QueueExams *q) { 
  return q->front == NULL; 
}

/* Colocar um no paciente na fila de exames*/
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

/* Tirar o primeiro paciente da fila de exames */
void QueueDequeue(QueueExams *q) {
  QueueNode *temp = q->front;    /* Armazenamento temporario para nó que será removido */

  if (q->front == q->rear) {
    q->front = q->rear = NULL;   /* Se houver apenas um elemento na fila */
  } else {
    q->front = q->front->next;   /* Move o ponteiro da frente para o próximo elemento */
  }
  free(temp);  /* Libera a memória do nó removido */
}

/* Limpa/libera a fila de exames */
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

/* Fazer funções para máquinas */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                     FUNÇÕES RELATIVAS À FILA DE LAUDOS                                            */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Função que cria a fila de laudos */
QueueReport *QueueReport_create() {
  QueueReport *q = (QueueReport *)malloc(sizeof(QueueReport));
  q->front = q->rear = NULL; /* Fila começa vazia */
  return q;
}

/* Função que verifica se a lista de laudos está vazia */
int QueueReportEmpty(QueueReport *q) { 
  return q->front == NULL; 
}

/* Função que coloca um novo paciente na fila para laudos */
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
  return q;
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

  int numb_random = rand() % 100 + 1;
  char condition[20];

  switch (numb_random) {
  case 1 ... 30:
    return CreatePathologie(strcpy(condition,"Saúde Normal"), 1);
  case 31 ... 50:
    return CreatePathologie(strcpy(condition, "Bronquite"), 2);
  case 51 ... 70:
    return CreatePathologie(strcpy(condition, "Pneumonia"), 3);
  case 71 ... 85:
    return CreatePathologie(strcpy(condition, "Fratura de Fêmur"), 4);
  case 86 ... 100:
    return CreatePathologie(strcpy(condition, "Apendicite"), 4);
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

void machine_print(Machines *machine){
  for(int i =0; i <= MAX_MACHINES; i++){
    printf("%d %d %d", machine[i].examDuration, machine[i].patientID, machine[i].time);
  }
}