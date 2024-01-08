#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SILVER_QUANTUM 80
#define GOLD_QUANTUM  120
int instruction_times[21];

enum Type {
    PLATINUM,
    GOLD,
    SILVER

};
struct Instr {
    char strValue[100];  // Assuming a maximum length of 100 for the string.
    int duration;
};
struct Proc {
    int index;
    struct Instr process_instructions[100];
    int arrival_time;
    int burst_time;
    int last_instruction;
    char name[20];
    int real_arrival_time;
    int priority;
    enum Type type;
    int isFinished;
    int quantum_number;
    int CPU_time;
    bool is_last;


};
struct Proc procs[10];
enum Type stringToType(const char *str) {
    if (strcmp(str, "GOLD") == 0) {
        return GOLD;
    } else if (strcmp(str, "SILVER") == 0) {
        return SILVER;
    } else if (strcmp(str, "PLATINUM") == 0) {
        return PLATINUM;
    }
    // Handle unknown type or error case
    return -1;  // You can define a default value or handle errors differently
}
const char* typeToString(enum Type type) {
    switch (type) {
        case GOLD:
            return "GOLD";
        case SILVER:
            return "SILVER";
        case PLATINUM:
            return "PLATINUM";
        default:
            return "UNKNOWN";  // or handle error as appropriate
    }
}
void printProcs(struct Proc procs[], int size) {
    printf("Process Name\tPriority\tArrival Time\tType\tIsFinished\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t\t%d\t\t%d\t\t%s\t%d\t\n", procs[i].name, procs[i].priority, procs[i].arrival_time, typeToString(procs[i].type),procs[i].isFinished);
    }
}
void printProcs2(struct Proc *procs[], int size) {
    printf("Process Name\tPriority\tArrival Time\tType\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t\t%d\t\t%d\t\t%s\n", procs[i]->name, procs[i]->priority, procs[i]->arrival_time, typeToString(procs[i]->type));
    }
}
int compareProcs(const void *a, const void *b) {
    struct Proc *procA = (struct Proc *)a;
    struct Proc *procB = (struct Proc *)b;
    if(procA->isFinished != procB->isFinished){
        return procA->isFinished - procB->isFinished;
    }
    if(procA->type==SILVER && procB->type==PLATINUM){
        return 1;
    }
    if(procA->type==PLATINUM && procB->type==SILVER){
        return -1;
    }
    if(procA->type==PLATINUM && procB->type==GOLD){
        return -1;
    }

    if(procA->type==GOLD && procB->type==PLATINUM){
        return 1;
    }
    if (procA->priority != procB->priority) {
        return procB->priority - procA->priority;
    }

    // Compare arrival time
    if (procA->arrival_time != procB->arrival_time) {
        return procA->arrival_time - procB->arrival_time;
    }

    // If arrival times are the same, compare priorities


    // If both arrival times and priorities are the same, compare names
    return strcmp(procA->name, procB->name);
}
int compareProcsForTime(const void *a, const void *b) {
    struct Proc *procA = (struct Proc *)a;
    struct Proc *procB = (struct Proc *)b;

    if(procA->isFinished != procB->isFinished){
        return procA->isFinished - procB->isFinished;
    }
    if (procA->arrival_time != procB->arrival_time) {
        return procA->arrival_time - procB->arrival_time;
    }
    if(procA->type==SILVER && procB->type==PLATINUM){
        return 1;
    }
    if(procA->type==PLATINUM && procB->type==SILVER){
        return -1;
    }
    if(procA->type==PLATINUM && procB->type==GOLD){
        return -1;
    }

    if(procA->type==GOLD && procB->type==PLATINUM){
        return 1;
    }
    if (procA->priority != procB->priority) {
        return procB->priority - procA->priority;
    }

    // Compare arrival time


    // If arrival times are the same, compare priorities


    // If both arrival times and priorities are the same, compare names
    return strcmp(procA->name, procB->name);
}



void readInstructionsFromFile(const char *fileName, struct Instr instructions[], int *instructionCount) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    int count = 0;
    while (count < 100 && fscanf(file, "%49s", instructions[count].strValue) == 1) {
        char copied[25];
        char* token;
        strcpy(copied,instructions[count].strValue);
        token = strtok(copied,"r");
        token = strtok(NULL,"\0");
        printf("Token is : %s\n",token);
        if(token !=NULL){
            int index = atoi(token);
            int time = instruction_times[index-1];
            instructions[count].duration=time;
        }
        else{
            instructions[count].duration=10;
        }

        count++;
    }
    //*instructionCount = count;

    fclose(file);
}

void populateProcessInstructions(struct Proc *proc) {
    char fileName[50]; // Assuming the file name won't exceed 50 characters
    snprintf(fileName, sizeof(fileName), "C:\\Users\\ebaser\\CLionProjects\\p2\\%s.txt", proc->name);
    readInstructionsFromFile(fileName, proc->process_instructions, &proc->last_instruction);
}
int init = 0;

int main() {
    int burst_time_total=0;


    FILE *file = fopen("C:\\Users\\ebaser\\CLionProjects\\p2\\instructions.txt", "r");  // Replace "file.txt" with your file name

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;  // Return with an error code
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char instr[20];
        int time;
        if (strncmp(line, "exit", 4) == 0) {
            instruction_times[20]= 10;

            continue;  // Skip this iteration of the loop
        }
        if (sscanf(line, "%s %d", instr, &time) == 2) {
            // Assuming instruction names are like "instrX"
            int index;
            sscanf(instr, "instr%d", &index);
            instruction_times[index - 1] = time;

        }
    }

    fclose(file);


    // Printing the filled array for verification
    /*for (int i = 1; i <= 21; i++) {
        printf("instr%d %d\n", i, instruction_times[i-1]);
    }*/
    FILE *procFiles = fopen("C:\\Users\\ebaser\\CLionProjects\\p2\\definition.txt", "r");
    if (!procFiles) {
        perror("Unable to open file");
        return 1;
    }

    int count = 0;
    char typeStr[20];  // Temporary buffer to read the type as a string
    while (fscanf(procFiles, "%s %d %d %s", procs[count].name, &procs[count].priority, &procs[count].arrival_time, typeStr) == 4) {
        procs[count].type = stringToType(typeStr);  // Convert string to enum
        procs[count].index = count;
        int real = procs[count].arrival_time;
        procs[count].real_arrival_time=real;
        count++;
        if (count > 10) {
            printf("Too many processes in the file. Only the first 10 will be processed.\n");
            break;
        }
    }

    fclose(procFiles);

   // printProcs(procs, count);
    for (int i = 0; i < count; i++) {

        populateProcessInstructions(&procs[i]);
    }
    qsort(procs, count, sizeof(struct Proc), compareProcs);
    //TODO : current time 0 dan basla. Koşullara göre instructionları uygula
    // her instructionda sortla ve tekrar isleme al (Arrayin headi !!!).
    // Type dönüstürme kosulunu yaz. Global bi variableda süreleri tut. Last inst indexi tut.
   // printProcs(procs, count);
    int curr_time = 0;
    int turnaround=0;

    while(1) {
        bool allFinished = true;
        int test = 0;
        int temp_count = 0;

        init++;
        struct Proc *procs_temp[20];
        struct  Proc *proc_last;
        if(init !=0) {
            for(int i = 0 ; i<count ; i++){
                if(procs[i].is_last){
                    proc_last = &procs[i];
                }
            }

        }





        qsort(procs, count, sizeof(struct Proc), compareProcs);
       // printProcs(procs,count);
        for (int i = 0; i < count; i++) {


            if (procs[i].arrival_time <= curr_time) {
                temp_count++;
                procs_temp[0] = &procs[i];
                break;
            }


        }
        if(strcmp(proc_last->name,procs_temp[0]->name)!=0 && init>1){
            printProcs(procs,count);
            printf("Preemption from %s to %s \n",proc_last->name,procs_temp[0]->name);
            if(proc_last->type==SILVER && proc_last->quantum_number<3&&proc_last->CPU_time!=0 ){
                proc_last->quantum_number++;
                if(proc_last->CPU_time>=SILVER_QUANTUM){
                    proc_last->arrival_time=curr_time;
                }
                if(proc_last->quantum_number==3){
                    proc_last->quantum_number=0;
                    proc_last->type=GOLD;
                    proc_last->CPU_time=0;
                }
                proc_last->arrival_time=curr_time;



            }
            if(proc_last->type==GOLD && proc_last->quantum_number<5 &&proc_last->CPU_time!=0){
                proc_last->quantum_number++;
                if(proc_last->CPU_time>=GOLD_QUANTUM){
                    proc_last->arrival_time=curr_time;
                }
                if(proc_last->quantum_number==5){
                    proc_last->quantum_number=0;
                    proc_last->type=PLATINUM;
                    proc_last->CPU_time=0;
                }
                proc_last->arrival_time=curr_time;


            }
        }
        for(int i = 0 ; i<count;i++){
            if(!procs[i].isFinished){
                allFinished=false;
            }
        }
        printf("temp_count is %d \n",temp_count);
        printf("count is %d \n",count);
        if(procs_temp[0]->isFinished && !allFinished ){
            qsort(procs, count, sizeof(struct Proc), compareProcsForTime);
            printf("arr %d \n",procs[0].arrival_time);
            curr_time=procs[0].real_arrival_time;
            continue;
        }

        if(!procs_temp[0]->is_last && !allFinished){
            printf("Context switch here \n");
            curr_time+=10;
        }
        //printProcs2(procs_temp, temp_count);
        if(procs_temp[0]->isFinished){
            for(int k = 0 ; k<count;k++){
                burst_time_total+=procs[k].burst_time;
            }

            printf("AVG Turnaround  time is : %.1f\n", (float) turnaround / (float) count);
            printf("Waiting time is : %.1f\n", ((float) turnaround - (float) burst_time_total)/ (float) count);
            printf("Current time is : %d",curr_time);
            break;
        }
        //curr_time+=10; // Context switch.


        if(procs_temp[0]->type==PLATINUM){
            int time_elapsed=0;
            int counter_for_last_instr=0;
            for(int i = procs_temp[0]->last_instruction ; i<sizeof(procs_temp[0]->process_instructions)/sizeof(procs_temp[0]->process_instructions[0]);i++){
                time_elapsed+=procs_temp[0]->process_instructions[i].duration;
                procs_temp[0]->burst_time+=procs_temp[0]->process_instructions[i].duration;
                counter_for_last_instr++;

            }

            for(int i = 0 ; i<count ; i++){
                procs[i].is_last=false;
            }
            procs_temp[0]->is_last=true;
            procs_temp[0]->last_instruction=counter_for_last_instr;
            procs_temp[0]->isFinished=1;
            curr_time+=time_elapsed;
            turnaround+=curr_time-procs_temp[0]->real_arrival_time;
            printf("IN PLATINUM BLOCK and P--name is %s and Current time is : %d\n",procs_temp[0]->name,curr_time);
            continue;
        }
        else if(procs_temp[0]->type==SILVER){

            if(!procs_temp[0]->is_last){

                procs_temp[0]->CPU_time=0;
            }
            if(procs_temp[0]->CPU_time<SILVER_QUANTUM) {
                int index = procs_temp[0]->last_instruction;

                for(int i = 0 ; i<count ; i++){
                    procs[i].is_last=false;
                }
                procs_temp[0]->is_last=true;
                if (strncmp(procs_temp[0]->process_instructions[index].strValue, "exit", 4) == 0) {
                        printf("EXIT HIT IN SILVER BLOCK !!! \n");
                        curr_time += procs_temp[0]->process_instructions[index].duration;
                    turnaround += curr_time-procs_temp[0]->real_arrival_time;
                    procs_temp[0]->last_instruction++;
                    procs_temp[0]->burst_time+=procs_temp[0]->process_instructions[index].duration;
                    procs_temp[0]->isFinished = 1;
                } else {
                    curr_time += procs_temp[0]->process_instructions[index].duration;
                    procs_temp[0]->last_instruction++;
                    procs_temp[0]->burst_time+=procs_temp[0]->process_instructions[index].duration;
                }



                procs_temp[0]->CPU_time+=procs_temp[0]->process_instructions[index].duration;
                printf("IN SILVER BLOCK and P--name is %s and Current time is : %d AND INST : %s \n", procs_temp[0]->name, curr_time,procs_temp[0]->process_instructions[index].strValue);
                continue;
            }
            else{
                procs_temp[0]->quantum_number++;
                if(procs_temp[0]->quantum_number==3){
                    procs_temp[0]->quantum_number=0;
                    procs_temp[0]->type=GOLD;
                }
                procs_temp[0]->CPU_time=0;
                procs_temp[0]->arrival_time=curr_time;
                continue;

            }
        }
        // GOLD BLOCK
        else{
            if(!procs_temp[0]->is_last){
                procs_temp[0]->CPU_time=0;
            }
            //Üst taraf yeni eklendi. 11.49
            if(procs_temp[0]->CPU_time<GOLD_QUANTUM) {
                int index = procs_temp[0]->last_instruction;

                for(int i = 0 ; i<count ; i++){
                    procs[i].is_last=false;
                }
                procs_temp[0]->is_last=true;
                if (strncmp(procs_temp[0]->process_instructions[index].strValue, "exit", 4) == 0) {
                    printf("EXIT HIT IN GOLD BLOCK !!! \n");
                    curr_time += procs_temp[0]->process_instructions[index].duration;
                    turnaround+=curr_time-procs_temp[0]->real_arrival_time;
                    procs_temp[0]->last_instruction++;
                    procs_temp[0]->burst_time+=procs_temp[0]->process_instructions[index].duration;
                    procs_temp[0]->isFinished = 1;
                } else {
                    curr_time += procs_temp[0]->process_instructions[index].duration;
                    procs_temp[0]->burst_time+=procs_temp[0]->process_instructions[index].duration;
                    procs_temp[0]->last_instruction++;
                }


                procs_temp[0]->CPU_time+=procs_temp[0]->process_instructions[index].duration;

                printf("IN GOLD BLOCK and P--name is %s and Current time is : %d AND INST : %s \n", procs_temp[0]->name, curr_time,procs_temp[0]->process_instructions[index].strValue);
                continue;
            }
            else{
                procs_temp[0]->quantum_number++;
                if(procs_temp[0]->quantum_number==5){
                    procs_temp[0]->quantum_number=0;
                    procs_temp[0]->type=PLATINUM;
                }
                procs_temp[0]->CPU_time=0;
                printf("here is %s \n",procs_temp[0]->name);
                procs_temp[0]->arrival_time=curr_time;
                continue;

            }



        }

    }



    return 0;
}
