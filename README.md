# CP386-A4
Assignment 4 for CP386 - Section C, Spring 2022

## Features
RQ - Request Memory -> Allocate memory to a requested process using first fit, best fit, or worst fit method

Status -> Display which region of memory has been allocated to which process

RL -> Release Memory -> Release the allocated memory of a given process

Compact -> Compacts set of holes into larger hole

B -> best_fit function. Finds smallest free 


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




## Examples

## About Developers
### Muhammad Rufaid Jugoo

Student ID: 180174860

Email: jugo4860@mylaurier.ca

4th Year BBA Student with CS Minor

### Ruben Halanen
Student ID: 180573480

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
