ENES BAŞER - 2020400141  

# Round-Robin CPU Scheduling in C  

## Overview 

The `main.c` file contains the main logic for a process scheduling simulation. It reads process data from a file, populates the process instructions, sorts the processes, and then simulates their execution. 

## Structs 

- ` Process `: Holding fields for processes. It would be a good choice to operaitons with fields of corresponding structs. 

- ` Instruction `: Instruction has some fields like duration name. And also it is useful to use this structure in ` Process ` struct 

- ` enum `: Defined for purpose of type of the process wheter they are ` GOLD,PLATINUM ,SILVER ` 

## Key Variables 

- `procs`: An array of `Proc` structures, each representing a process to be scheduled. 

- `count`: A counter for the number of processes read from the file. 

- `curr_time`: The current time in the simulation. 

- `turnaround`: A variable to hold the turnaround time. 

- `allFinished`: A boolean flag to check if all processes have finished execution. 

- `test`, `temp_count`, `init`: Temporary variables used in the simulation loop. 

## Key Functions 

- `populateProcessInstructions(&procs[i])`: Populates the instructions for the process `procs[i]`. 

- `qsort(procs, count, sizeof(struct Proc), compareProcs)`: Sorts the `procs` array using the `compareProcs` function. 

- `compareProcs`: A function used to compare two `Proc` structures (not shown in the provided code). 

## Program Flow 

1. The program reads process data from a file and stores it in the `procs` array. If more than 10 processes are read, the program only keeps the first 10 and discards the rest. 

2. The program populates the instructions for each process. 

3. The `procs` array is sorted to handle scheduling priority . (Refretence to qsort and custom compareTo function) 

 

4. The program enters a simulation loop where it simulates the execution of the processes. It handles types(defined as enum reference to `enum ` ) priorities, preemption , burst time for each of the process structures. 

5. At the end of the simulation if all process `isFinished ` then exit loop and print `turnaround time` and `waiting time` . 

 

##  Compile and Run 

- `make` 

- `./scheduler` 

- Test with different input changing to input file as `defX.txt` . 

 

 

 

 

 
