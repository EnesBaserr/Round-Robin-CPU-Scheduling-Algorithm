#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    int priority;
    enum Type type;

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
    printf("Process Name\tPriority\tArrival Time\tType\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t\t%d\t\t%d\t\t%s\n", procs[i].name, procs[i].priority, procs[i].arrival_time, typeToString(procs[i].type));
    }
}
int compareProcs(const void *a, const void *b) {
    struct Proc *procA = (struct Proc *)a;
    struct Proc *procB = (struct Proc *)b;

    // Compare arrival time
    if (procA->arrival_time != procB->arrival_time) {
        return procA->arrival_time - procB->arrival_time;
    }

    // If arrival times are the same, compare priorities
    if (procA->priority != procB->priority) {
        return procA->priority - procB->priority;
    }

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

int main() {
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
        count++;
        if (count >= 10) {
            printf("Too many processes in the file. Only the first 10 will be processed.\n");
            break;
        }
    }

    fclose(procFiles);

    printProcs(procs, count);
    for (int i = 0; i < count; i++) {

        populateProcessInstructions(&procs[i]);
    }
    qsort(procs, count, sizeof(struct Proc), compareProcs);
    //TODO : current time 0 dan basla. Koşullara göre instructionları uygula
    // her instructionda sortla ve tekrar isleme al (Arrayin headi !!!).
    // Type dönüstürme kosulunu yaz. Global bi variableda süreleri tut. Last inst indexi tut.

    int curr_time = 70;
    struct Proc procs_temp [20];
    int temp_count = 0;
    for(int i = 0;i< count;i++){

        if(procs[i].arrival_time<curr_time){
            temp_count++;
            procs_temp[i]=procs[i];


        }

    }
    qsort(procs_temp, temp_count, sizeof(struct Proc), compareProcs);
    printProcs(procs, count);
    printProcs(procs_temp, temp_count);



    return 0;
}
