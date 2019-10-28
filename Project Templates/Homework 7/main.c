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
	unsigned long average;
	struct Student STyp[SIZE];

	int i;
	for (i = 0; i < SIZE; ++i) {
		STyp[i].id = i;
		STyp[i].score = 90;
	}

	average = Grades(STyp);

	// do something with average, STyp now has a grade for every Student

	while(1) {
		// forever
	}
}


unsigned long Grades(struct Student STyp[SIZE]) {
	int i;
	unsigned long sumScores = 0;

	for (i = 0; i < SIZE; ++i) {
		struct Student *curr = &STyp[i];               // get a pointer to the address of the current Student
		if (curr->score >= 75)                         // if the value is >= 75, grade is updated to 'P', else 'F'
			curr->grade = 'P';
		else
			curr->grade = 'F';

		sumScores += curr->score;                      // add the current score to the running total
	}

	return sumScores / SIZE;                           // return the average of the scores
}
