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

void updateCreditRatingAlice(int opcode);
int rewardsOrAlarm(void);

// Note: I prepend globals with _
int _creditStatus;
int _creditRatingAlice = 750;
int _maxCreditRating = 800;
int _minCreditRating = 700;
int _monthlyPaymentHistoryAlice[24] = {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1};
	
int main(void) {
	while (1) {
		_creditStatus = rewardsOrAlarm();
	}
}

void updateCreditRatingAlice(int opcode) {
	if (opcode == 1 && _creditRatingAlice != _maxCreditRating)
		_creditRatingAlice += 10;
	else if (_creditRatingAlice != _minCreditRating)
		_creditRatingAlice -= 10;
}

int rewardsOrAlarm(void) {
	return 1;
}
