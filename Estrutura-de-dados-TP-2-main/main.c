#include "structs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));
  int nextID = 1000;
  int max_time = 50;
  char filename[10];
  patient *patient;

  printf("Digite o nome do arquivo: ");
  scanf("%s", filename);

  ListPatient *list_patient = ListPatient_create();
  QueueExams *exams = QueueExams_create();
  QueueReport *report = QueueReport_create();
  ListMachines *Machine = ListMachines_create();

  FILE *arquivo = fopen(filename, "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n\n");
    return 1;
  }

  initializeMachines(5, Machine);

  for (int time = 1; max_time >= time; time++) {

    if (rand() % 5 + 1 == 1) {
      
      char name[50];
      int age = 0;
      char cpf[20];

      fscanf(arquivo, "%49s\n%d\n%15s\n", name, &age, cpf);
        /* Lista de pacientes */
        patient = newPatient(name, cpf, age, nextID);
        ListPatient_insert(list_patient, patient);
        /* Fila de pacientes */
        QueueEnqueue(exams, nextID);
        nextID++;
    }
    QueueExams_print(exams);
    printf("\n");
    insert_machines(Machine, exams, time);

  }
  printf("\n");
  patient_print(list_patient);
  machine_print(Machine);

  fclose(arquivo);
  return 0;
}