#include <stdio.h>
#include <string.h>
#include "Terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	ST_terminalData_t LocalNew_TermData;
	uint8_t numOfTermDate_dig;

	printf("Please Enter The Transaction Date\n");
	gets(LocalNew_TermData.transactionDate);
	

	numOfTermDate_dig = getnumOfTermDateChar(&LocalNew_TermData);

	if ((numOfTermDate_dig == Invalid) || (numOfTermDate_dig != TRANSACTION_DATE_CHAR))
	{

		return WRONG_DATE;

	}
	else
	{

	    memcpy(termData->transactionDate, &LocalNew_TermData.transactionDate,
	    sizeof(LocalNew_TermData.transactionDate));

	    return OK_ter;
	}
	
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint8_t cardData_month ;
	uint8_t cardData_year  ;
	uint8_t termData_month ;
	uint8_t termData_year  ;
	
	
	cardData_month =((cardData.cardExpirationDate[0]-48) * 10) + (cardData.cardExpirationDate[1] - 48);
	cardData_year = ((cardData.cardExpirationDate[3] - 48) * 1000) +
					((cardData.cardExpirationDate[4] - 48) * 100) +
					((cardData.cardExpirationDate[5] - 48) * 10)+
					(cardData.cardExpirationDate[6] - 48);

	termData_month =((termData.transactionDate[3]- 48) * 10) + (termData.transactionDate[4]-48);
	termData_year = ((termData.transactionDate[6]- 48) * 1000) +
					((termData.transactionDate[7] - 48) * 100) +
					((termData.transactionDate[8] -48) * 10) +
					(termData.transactionDate[9]- 48 );

	if (cardData_year < termData_year)
	{

		printf("Expired Card\n");
		return EXPIRED_CARD;
		
	}
	else if ((cardData_year == termData_year) && (cardData_month < termData_month))
	{
		printf("Expired Card\n");
		return EXPIRED_CARD;
		
	}
	else
	{
		printf("======================================================\n");
		printf("=            Your Card Date Is Okay                  = \n");
		printf("======================================================\n");
		printf("CARD OKAY\n");
		return OK_ter;
	}
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	ST_terminalData_t LocalNew_TermData;

	printf("Please Enter The Transaction Amount \n");
	scanf_s("%f", &LocalNew_TermData.transAmount);


	if (LocalNew_TermData.transAmount <= Invalid)
	{

		
		return INVALID_AMOUNT;
	}
	else
	{
	    termData->transAmount = LocalNew_TermData.transAmount;
		return OK_ter;
	}


}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	

	if (termData->transAmount > termData->maxTransAmount)
	{
		printf("===========================================================\n");
		printf("= SORRY YOU EXCEEDED THE MAX AMOUNT FOR TODAY TRANSCATION = \n");
		printf("===========================================================\n");
		printf("EXCEED_MAX_AMOUNT \n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		printf("Amount is valid \n");
		return OK_ter;
	}
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	ST_terminalData_t LocalNew_TermData;

	printf("Please Enter The Transaction Max Amount \n");
	scanf_s("%f" ,&LocalNew_TermData.maxTransAmount);
	getchar();


	if (LocalNew_TermData.maxTransAmount <= Invalid)
	{


		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = LocalNew_TermData.maxTransAmount;
		return OK_ter;
	}

}

uint8_t getnumOfTermDateChar(ST_terminalData_t* termData) {

	uint8_t count = 0;
	uint8_t i = 0;
	while (termData->transactionDate[i] != Null_OF_CHAR)
	{


		count++;
		i++;

	}
	return count;
}
