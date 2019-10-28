// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7


#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

#define SIZE 64

struct Student {
	unsigned long id;
	unsigned long score;
	unsigned char grade;
};

unsigned long Grades(struct Student STyp[SIZE]);

int main() {
	unsigned long grades;
	struct Student STyp[SIZE];
	int j;
	for (j = 0; j < SIZE; ++j) {
		STyp[j].id = j;
		STyp[j].score = 90;
	}
	
	grades = Grades(STyp);
	
	// do something with grades
	
	while(1) {
		// forever
	}
}


unsigned long Grades(struct Student STyp[SIZE]) {
	int j;
	unsigned long sumScores = 0;
	
	for (j = 0; j < SIZE; ++j) {
		struct Student curr = STyp[j];
		if (curr.score >= 75)
			curr.grade = 'P';
		else
			curr.grade = 'F';
		
		sumScores += curr.score;
	}
	
	
	return sumScores / SIZE;
}
