#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct QueueExams QueueExams; /* Fila de Exames, que armazena somente o ID dos novos pacientes */
typedef struct ExamRecord ExamRecord; /* Registro dos exames */
typedef struct Patient patient; /* Definição da estrutura Patient, relativa aos pacientes */
typedef struct ListOfPatients ListPatient; /* Lista de Pacientes, nosso banco de dados */
typedef struct Machines Machines; /* Estrutura para armazenamento dos aparelhos utilizados nos exames */
typedef struct QueueReport QueueReport; /* Fila de Laudos, que armazena os registros de exames */
typedef struct Pathologies Pathologie;
typedef struct list_node ListNode;
typedef struct Queue_Node QueueNode;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                               # PACIENTES # */


patient *newPatient(char *name, char *cpf, int age, int id); /* Função para criar novo paciente, com ID sequencial */

ListPatient *ListPatient_create(); /* Função que cria uma de lista de pacientes */

int ListPatient_size(ListPatient *list); /* Função para saber o tamanho da lista de pacientes */

int ListEmpty(ListPatient *list); /* Função que verifica se a lista esta vazia */

void ListPatient_insert(ListPatient *list, patient *patients); /* Função que insere um novo paciente à Lista de Pacientes */

int ListPatient_remove(ListPatient *list, patient *patients); /* Função que remove um paciente da Lista de Pacientes */

void ListPatient_free(ListPatient *list); /* Função que libera memória da Lista de Pacientes */


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                            # EXAMES & APARELHOS #                                                 */


QueueExams *QueueExams_create(); /* Função que cria uma fila de exames vazia */
int QueueEmpty(QueueExams *q); /* Função que verifica se a fila de exames está vazia */
void QueueEnqueue(QueueExams *q, int newID); /* Função que insere um novo exame (ou seja, insere um novo ID) no início da fila */
void QueueDequeue(QueueExams *q); /* Função para desenfileirar um elemento da lista, ou seja, remover o nó inicial da lista */
void QueueFree(QueueExams *q); /* Função para liberar memória usada para armazenamento da fila de exames */

void takingExam(QueueExams *examQueue, Machines *machines, int time); /* Função para realizar o exame */

Machines *initializeMachines(); /* Função para iniciar o funcionamento dos aparelhos (todos iniciam disponíveis (0)) */
int checkMachinesAvailability(Machines *machines); /* Função para checar a disponibilidade dos aparelhos */
void releaseMachines(Machines *allMachines, int time); /*Função para liberar todas as máquinas */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                # LAUDOS # */



QueueReport *QueueReport_create(); /* Função que cria uma fila de laudos vazia */
int QueueReportEmpty(QueueReport *q); /* Função que verifica se a fila de laudos está vazia */
void addExamRecord_toQueueReport(QueueReport *q, ExamRecord *record, int time); /* Função que insere um ExamRecord ao final da fila de laudos */
QueueReport *QueueEnqueue_registerRecord(QueueReport *q, int id, int time, Pathologie *path);
Pathologie *Assessing_Pathologies();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                       # PRINTS #                                                  */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void patient_print(ListPatient *l);
void QueueExams_print(QueueExams *exams);

#endif