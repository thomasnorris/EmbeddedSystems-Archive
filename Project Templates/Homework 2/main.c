/*******************************************************************
 *  main.c
 *  This is an embedded program template.
 *  
 *  Author: Thomas Norris
 *  Date: Date: 09/10/19
 *
 *  
 *******************************************************************/

// Called by startup assembly code, start of C code

void updateCreditRatingAlice(int opCode);
int rewardsOrAlarm(int index);

// Note: I prepend globals with _
int _creditStatus;
int _creditRatingAlice = 750;
int _maxCreditRating = 800;
int _minCreditRating = 700;
int _monthlyPaymentHistoryAlice[24] = {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1};
	
int main(void) {
	int index = 0;
	int arraySize = sizeof(_monthlyPaymentHistoryAlice) / sizeof(int);
	while (1) {
		if (index == arraySize)
			index = 0;
		_creditStatus = rewardsOrAlarm(index);
		index++;
	}
}

void updateCreditRatingAlice(int opCode) {
	if (opCode == 1 && _creditRatingAlice != _maxCreditRating)
		_creditRatingAlice += 10;
	else if (_creditRatingAlice != _minCreditRating)
		_creditRatingAlice -= 10;
}

int rewardsOrAlarm(int index) {
	int currentOpCode = _monthlyPaymentHistoryAlice[index];
	int previousCreditRating = _creditRatingAlice;
	int newCreditRating;
	
	updateCreditRatingAlice(currentOpCode);
	newCreditRating = _creditRatingAlice;
	
	if (newCreditRating == previousCreditRating) {
		if (newCreditRating == _maxCreditRating)
			return 1;
		else if (newCreditRating == _minCreditRating)
			return 0;
	}
	
	return 2;
}
