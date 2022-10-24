#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	ST_cardData_t LocalNew_CardData;
	uint8_t numOfChar;
	
    
	printf("Please Enter Card Holder Name\n");
	gets(LocalNew_CardData.cardHolderName);
	
	numOfChar = getnumOfNameChar(&LocalNew_CardData);  
	

	
	if ((numOfChar == Invalid) || (numOfChar >= MAX_CARD_NAME) || (numOfChar <= MIN_CARD_NAME))
	{
		return WRONG_NAME;
	}
	else
	{
	printf("==============================================\n");
	printf("= Your Name Has Been Entered Successfully    = \n");
	printf("==============================================\n");

	memcpy(cardData->cardHolderName, &LocalNew_CardData.cardHolderName,
	sizeof(LocalNew_CardData.cardHolderName));
		
	return OK_card;
	}
	
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

    ST_cardData_t LocalNew_CardData;
	uint8_t numOfDate_dig;

	printf("Please Enter Card Expiry Date\n");
	gets(LocalNew_CardData.cardExpirationDate);

	numOfDate_dig = getnumOfDateChar(&LocalNew_CardData);

	if ((numOfDate_dig == Invalid) || (numOfDate_dig != CARD_EXP_DATE) )
	{
		
		
		return WRONG_EXP_DATE;
	}
	else
	{
	printf("======================================================\n");
	printf("= Your Expiray Date Has Been Entered Successfully    = \n");
	printf("======================================================\n");

	memcpy(cardData->cardExpirationDate, &LocalNew_CardData.cardExpirationDate,
	sizeof(LocalNew_CardData.cardExpirationDate));

	return OK_card;
	}
}
                  

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	ST_cardData_t LocalNew_CardData;
    uint8_t numOfPan_dig;

	printf("Please Enter Card PAN Number\n");
	gets(LocalNew_CardData.primaryAccountNumber);
	
	numOfPan_dig = getnumOfPanChar(&LocalNew_CardData);

	if ((numOfPan_dig == Invalid) || (numOfPan_dig > MAX_PAN_NUM) || (numOfPan_dig < MIN_PAN_NUM))
	{
		return WRONG_PAN;
	}
	else
	{
	memcpy(cardData->primaryAccountNumber, &LocalNew_CardData.primaryAccountNumber,
	sizeof(LocalNew_CardData.primaryAccountNumber));

	return OK_card;
	}


}


uint8_t getnumOfNameChar(ST_cardData_t* cardData) {

	uint8_t count = 0;
	uint8_t i = 0;
	while (cardData->cardHolderName[i] != Null_OF_CHAR)
	{
		
		
		count++;
		i++;
		
	}
	return count;
}



uint8_t getnumOfDateChar(ST_cardData_t* cardData) {

	uint8_t count = 0;
	uint8_t i = 0;
	while (cardData->cardExpirationDate[i] != Null_OF_CHAR)
	{
		
		count++;
		i++;

	}
	return count;
}

uint8_t getnumOfPanChar(ST_cardData_t* cardData) {

	uint8_t count = 0;
	uint8_t i = 0;
	while (cardData->primaryAccountNumber[i] != Null_OF_CHAR)
	{
		

		count++;
		i++;

	}
	return count;
}