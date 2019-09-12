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
// Note: I am assuming that alice starts with a rating of 750, and _monthlyPaymentHistoryAlice[0] is for the next month
int _creditStatus;
int _creditRatingAlice = 750;
int _maxCreditRating = 800;
int _minCreditRating = 700;
int _monthlyPaymentHistoryAlice[24] = {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1};
	
int main(void) {
	int index = 0;
	int arraySize = sizeof(_monthlyPaymentHistoryAlice) / sizeof(int);
	
	while (1) {
		if (index == arraySize)                                      // reset the index back to zero to restart the cycle
			index = 0;
		
		_creditStatus = rewardsOrAlarm(index);
		
		index++;
	}
}

void updateCreditRatingAlice(int opCode) {
	if (opCode == 1 && _creditRatingAlice != _maxCreditRating)       // only add 10 to the credit rating if it isn't already max
		_creditRatingAlice += 10;
	else if (_creditRatingAlice != _minCreditRating)                 // only subtract 10 from the credit rating if it isn't already min
		_creditRatingAlice -= 10;
}

int rewardsOrAlarm(int index) {
	int currentOpCode = _monthlyPaymentHistoryAlice[index];
	int previousCreditRating = _creditRatingAlice;                   // previous credit rating is the same as her credit rating before updating
	int newCreditRating;
	
	updateCreditRatingAlice(currentOpCode);
	newCreditRating = _creditRatingAlice;                            // now, _creditRatingAlice has been updated to the new rating
	
	if (newCreditRating == previousCreditRating) {                   // if the credit didn't change from the previous month
		if (newCreditRating == _maxCreditRating)                     // if the credit rating is at maximum, return 1 (reward)
			return 1;
		else if (newCreditRating == _minCreditRating)                // if the credit rating is at minimum, return 0 (alarm)
			return 0;
	}
	
	return 2;                                                        // needed a status for the case where she doesn't receive an alarm or a reward
}
