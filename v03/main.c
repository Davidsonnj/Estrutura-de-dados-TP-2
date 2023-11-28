#include "simulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  srand(time(NULL));
  int cont = 0;
  int cont2 = 0;
  int time_report_med = 0;
  int qtd_patient_report = 0;
  int calc_metric1= 0;
  int relatorio = 11; 
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
  ListRadiologist *Radio = Radiologist_create();

  FILE *arquivo = fopen(filename, "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo.\n\n");
    return 1;
  }

  initializeMachines(5, Machine);
  initializeRadiologist(3, Radio);

  for(int time=1; time <= max_time; time++) {

    if (rand() % 5 + 1 == 1) {
      
      char name[50];
      int age = 0;
      char cpf[20];

      fscanf(arquivo, "%49s\n%15s\n%d\n", name, cpf, &age);

        /* Lista de pacientes */
        patient = newPatient(name, cpf, age, nextID);
        ListPatient_insert(list_patient, patient);
        
        /* Fila de pacientes */
        QueueEnqueue(exams, nextID);
        nextID++;
    }

    insert_machines(Machine, exams, time);
    Exam_Record(report, Machine, time);

    /* Tempo que o paciente saí da QueueReport (fila de laudo) e é alocado para o Radiologista */
    cont = insert_radio(Radio, report, time); 
    cont2 = remove_radio(Radio,time);

    time_report_med = time_report_med + cont;
    qtd_patient_report = qtd_patient_report + cont2;

    calc_metric1 = (qtd_patient_report != 0) ? (time_report_med / qtd_patient_report) : 0;


    /* RELATÓRIO DE MÉTRICAS */
    if((relatorio % 10) == 0){
      printf("\nRELATÓRIO DE MÉTRICAS - Unidade de Tempo: %d\n", time);
      printf("TML (Tempo médio de laudo): %d\n", calc_metric1);
      printf("TMP (Tempo médio de laudo por patologia): %d\n", (cont/7200));
      printf("QEL (Quantidade de exames realizados após o limite de tempo estabelecido): %d\n\n", (cont/7200));
    }
    
    relatorio = relatorio + 1;
  }
  printf("\n");
  //patient_print(list_patient);

  fclose(arquivo);
  return 0;
}