/*
 * --------------------------------------------------------
 Name: Ruben Halanen and Muhammad Jugoo
 Student ID: 180573480 180174860
 Student Email: hala3480@mylaurier.ca and jugo4860@mylaurier.ca
 * ----------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

//Global Variable
char request[3];
char process[3];
char algorithm[2];
int memory_requested;
int last_memory_address;

//Memory structure
struct Memory {
	char process_id[5];
	int available_memory;
	int start_address;
	int end_address;
	struct Memory *next;
};

struct Memory *head;
struct Memory *block_of_memory;
struct Memory *temp;

//Functions
void first_fit(char process[3], int memory_requested);
void best_fit(char process[3], int memory_requested);
void worst_fit(char process[3], int memory_requested);
void release_memory(char process_id[3]);
void status();
void compact();

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	//Get and print initial
	int initial_memory = atoi(argv[1]);
	printf("Allocated %d bytes of memory\n", initial_memory);

	//Declare variables
	char user_input[128];

	//Initialize head and blocks of memory
	head = (struct Memory*) malloc(sizeof(struct Memory));
	block_of_memory = (struct Memory*) malloc(sizeof(struct Memory));

	strcpy(head->process_id, "Head");
	head->start_address = 0;
	head->end_address = initial_memory - 1;
	head->available_memory = initial_memory;
	head->next = block_of_memory;

	strcpy(block_of_memory->process_id, "Unused");
	block_of_memory->start_address = 0;
	block_of_memory->end_address = initial_memory - 1;
	block_of_memory->available_memory = block_of_memory->end_address
			- block_of_memory->start_address + 1;
	block_of_memory->next = NULL;

	last_memory_address = initial_memory - 1;

	//Ask for user input
	printf("allocator>");
	fgets(user_input, sizeof(user_input), stdin);
	user_input[strlen(user_input) - 1] = '\0';

	//Loop until user inputs "Exit"
	while (strncmp(user_input, "Exit", 4) != 0) {
		//Split user input into appropriate variables
		sscanf(user_input, "%s %s %d %s", request, process, &memory_requested,
				algorithm);

		if (strncmp(request, "RQ", 2) == 0) { //Request memory
			//Check algorithm type
			if (strncmp("F", algorithm, 1) == 0) { //First fit
				first_fit(process, memory_requested);
			} else if (strncmp("B", algorithm, 1) == 0) { //Best fit
				best_fit(process, memory_requested);
			} else if (strncmp("W", algorithm, 1) == 0) { //Worst fit
				worst_fit(process, memory_requested);
			} else {
				printf("Invalid algorithm type, try again.\n");
			}
		} else if (strncmp(request, "RL", 2) == 0) { //Release memory
			release_memory(process);
		} else if (strncmp(request, "C", 1) == 0) { //Compact memory
			compact();
		} else if (strncmp(request, "Status", 5) == 0) { //Memory status
			status();
		} else {
			printf("Invalid input, try again.\n");
		}

		//Ask for user input
		printf("allocator>");
		fgets(user_input, sizeof(user_input), stdin);
		user_input[strlen(user_input) - 1] = '\0';
	}

	printf("Program exited\n");
	return 0;
}

//Allocate to first unused block of memory
void first_fit(char process[3], int memory_requested) {
	int leftover_memory;
	temp = head;

	//Traverse through linked list of blocks of memory to find first unused block of memory
	while (temp->next != NULL) {
		//Check if block is unused and big enough
		if (strncmp(temp->next->process_id, "Unused", 6) == 0
				&& temp->next->available_memory >= memory_requested) {
			//Update block of memory
			strcpy(temp->next->process_id, process);
			temp->next->end_address = temp->next->start_address
					+ memory_requested - 1;

			//Check for leftover memory
			leftover_memory = temp->next->available_memory - memory_requested;
			//If there is leftover memory, create a new block of memory
			if (leftover_memory > 0) {
				struct Memory *newMemory = (struct Memory*) malloc(
						sizeof(struct Memory));
				strcpy(newMemory->process_id, "Unused");
				newMemory->available_memory = leftover_memory;
				temp->next->available_memory = memory_requested;
				newMemory->start_address = temp->next->end_address + 1;
				newMemory->end_address = newMemory->start_address
						+ leftover_memory - 1;
				newMemory->next = temp->next->next;
				temp->next->next = newMemory;
			}
			//Update total available memory
			head->available_memory = head->available_memory - memory_requested;
			printf("Successfully allocated %d to process %s\n",
					memory_requested, process);
			return;
		}
		//Next block of memory
		temp = temp->next;
	}

	//No hole of sufficient size found
	printf("No hole of sufficient size\n");
	return;
}

//Allocate to smallest unused block of memory that is big enough
void best_fit(char process[3], int memory_requested) {
	int leftover_memory;
	temp = head;
	int smallest = last_memory_address + 1;

	//Traverse through linked list of blocks of memory to find first smallest block of memory big enough
	while (temp->next != NULL) {
		//If block of memory is unused and still big enough
		if (strncmp(temp->next->process_id, "Unused", 6) == 0
				&& temp->next->available_memory >= memory_requested) {
			//If block of memory is smaller
			if (temp->next->available_memory < smallest) {
				//Update smallest
				smallest = temp->next->available_memory;
			}
		}
		temp = temp->next;
	}

	//Allocate memory
	temp = head;
	while (temp->next != NULL) {
		if (strncmp(temp->next->process_id, "Unused", 6) == 0
				&& temp->next->available_memory == smallest) {
			//Update block of memory
			strcpy(temp->next->process_id, process);
			temp->next->end_address = temp->next->start_address
					+ memory_requested - 1;

			//Check for leftover memory
			leftover_memory = temp->next->available_memory - memory_requested;
			//If there is leftover memory, create a new block of memory
			if (leftover_memory > 0) {
				struct Memory *newMemory = (struct Memory*) malloc(
						sizeof(struct Memory));
				strcpy(newMemory->process_id, "Unused");
				newMemory->available_memory = leftover_memory;
				temp->next->available_memory = memory_requested;
				newMemory->start_address = temp->next->end_address + 1;
				newMemory->end_address = newMemory->start_address
						+ leftover_memory - 1;
				newMemory->next = temp->next->next;
				temp->next->next = newMemory;
			}
			//Update total available memory
			head->available_memory = head->available_memory - memory_requested;
			printf("Successfully allocated %d to process %s\n",
					memory_requested, process);
			return;
		} else {
			//Next block of memory
			temp = temp->next;
		}
	}

	//No hole of sufficient size found
	printf("No hole of sufficient size\n");
	return;
}

//Allocate to biggest unused block of memory
void worst_fit(char process[3], int memory_requested) {

	int leftover_memory;
	temp = head;
	int biggest = 0;

	//Traverse through linked list of blocks of memory to find first biggest block of memory big enough
	while (temp->next != NULL) {
		//If block of memory is unused and still big enough
		if (strncmp(temp->next->process_id, "Unused", 6) == 0
				&& temp->next->available_memory >= memory_requested) {
			//If block of memory is smaller
			if (temp->next->available_memory > biggest) {
				//Update smallest
				biggest = temp->next->available_memory;
			}
		}
		temp = temp->next;
	}

	//Allocate memory
	temp = head;
	while (temp->next != NULL) {
		if (strncmp(temp->next->process_id, "Unused", 6) == 0
				&& temp->next->available_memory == biggest) {
			//Update block of memory
			strcpy(temp->next->process_id, process);
			temp->next->end_address = temp->next->start_address
					+ memory_requested - 1;

			//Check for leftover memory
			leftover_memory = temp->next->available_memory - memory_requested;
			//If there is leftover memory, create a new block of memory
			if (leftover_memory > 0) {
				struct Memory *newMemory = (struct Memory*) malloc(
						sizeof(struct Memory));
				strcpy(newMemory->process_id, "Unused");
				newMemory->available_memory = leftover_memory;
				temp->next->available_memory = memory_requested;
				newMemory->start_address = temp->next->end_address + 1;
				newMemory->end_address = newMemory->start_address
						+ leftover_memory - 1;
				newMemory->next = temp->next->next;
				temp->next->next = newMemory;
			}
			//Update total available memory
			head->available_memory = head->available_memory - memory_requested;
			printf("Successfully allocated %d to process %s\n",
					memory_requested, process);
			return;
		} else {
			//Next block of memory
			temp = temp->next;
		}
	}

	//No hole of sufficient size found
	printf("No hole of sufficient size\n");
	return;
}

void release_memory(char process[3]) {
	printf("releasing memory for process %s\n", process);
	temp = head;

	//Traverse through linked list of blocks of memory
	while (temp->next != NULL) {
		//Check if block of memory is being used by the process we are looking for
		if (strncmp(temp->next->process_id, process, 2) == 0) {
			//Release memory
			head->available_memory = head->available_memory
					+ temp->next->available_memory;
			strcpy(temp->next->process_id, "Unused");
			printf("Successfully released memory for process %s\n", process);
			return;
		}
	}
	//If the process is not found
	printf("Memory release for process %s was unsuccessful", process);
	return;
}

void status() {
	//Print allocated memory
	temp = head;
	printf("Partitions [Allocated memory: %d]:\n",
			last_memory_address - head->available_memory + 1);
	//Traverse through linked list of blocks of memory
	while (temp->next != NULL) {
		if (strncmp(temp->next->process_id, "Unused", 6) != 0) { //If block of memory is being used
			printf("Address [%d : %d] Process %s\n", temp->next->start_address,
					temp->next->end_address, temp->next->process_id);
		}
		temp = temp->next;
	}

	//Print unallocated memory
	temp = head;
	printf("\nHoles [Free memory: %d]:\n", head->available_memory);
	//Traverse through linked list of blocks of memory
	while (temp->next != NULL) {
		if (strncmp(temp->next->process_id, "Unused", 6) == 0) { //If block of memory is unused
			printf("Address [%d : %d] len = %d\n", temp->next->start_address,
					temp->next->end_address, temp->next->available_memory);
		}
		temp = temp->next;
	}
	return;
}

//Compact memory
void compact() {
	temp = head;
	int address = 0;
	int unused_memory = 0;
	struct Memory *delete;

	// Combine holes
	while (temp != NULL && temp->next != NULL) {
		if (strncmp(temp->next->process_id, "Unused", 6) == 0) {
			unused_memory += temp->next->available_memory;
			delete = temp->next;
			temp->next = delete->next;
			free(delete);
		}
		temp = temp->next;
	}

	struct Memory *newMemory = (struct Memory*) malloc(sizeof(struct Memory));
	strcpy(newMemory->process_id, "Unused");
	newMemory->available_memory = unused_memory;
	newMemory->next = NULL;

	temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newMemory;

	//Update addresses
	temp = head;
	while (temp->next != NULL) {
		temp->next->start_address = address;
		temp->next->end_address = temp->next->start_address
				+ temp->next->available_memory - 1;
		address += temp->next->available_memory;
		temp = temp->next;
	}

	printf("Compaction process is successful\n");
	return;
}
