# CP386-A4
Assignment 4 for CP386 - Section C, Spring 2022

## Features
RQ - Request Memory -> Allocate memory to a requested process using first fit, best fit, or worst fit method

Status -> Display which region of memory has been allocated to which process

RL -> Release Memory -> Release the allocated memory of a given process

Compact -> Compacts set of holes into larger hole

B -> best_fit function. Allocates smallest free block that meets the requirement of requesting process
W -> worst_fit function. Allocates a process to the block which is largest sufficient among the available blocks in the main memory
F -> first_fit function.


## Makefile

Contents of the make file:
CC = gcc
CFLAGS = -std=gnu99
TARGET = allocation  
OBJFILES = allocation.o
all: $(TARGET)

allocation: allocation.c
	$(CC) $(CFLAGS) -o allocation allocation.c
	
run: allocation
	./allocation 1048576
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
  
To run the code in linux, type "make run"

## Test Cases
Requesting memory:  


![image](https://user-images.githubusercontent.com/71409000/180094761-b32f924d-8759-4ba0-94ba-1171a9d75bac.png)

Releasing memory:        


![image](https://user-images.githubusercontent.com/71409000/180095010-95405dab-4890-431c-854e-41c113435f3f.png)


Requesting memory without enough space:

![image](https://user-images.githubusercontent.com/71409000/180095334-0655a589-59f6-47d0-a812-0fb3fba18aad.png)

Compacting:

![image](https://user-images.githubusercontent.com/71409000/180104403-0f547e5f-587d-4a90-ac5c-e2a50a1f71e8.png)

Status:

![image](https://user-images.githubusercontent.com/71409000/180104568-50df4c09-bfc1-4221-9f64-6e15e259602a.png)





## Examples

## About Developers
### Muhammad Rufaid Jugoo

Student ID: 180174860

Email: jugo4860@mylaurier.ca

4th Year BBA Student with CS Minor

### Ruben Halanen
Student ID: 180573480

3rd Year CS Student

Email: hala3480@mylaurier.ca

## Individual Contribution
### Ruben
First Fit

Compact

Release memory

### MUHAMMAD
Best fit

Worst fit

Status

## License
Copyright © 2022 MUHAMMAD RUFAID JUGOO AND RUBEN HALANEN
