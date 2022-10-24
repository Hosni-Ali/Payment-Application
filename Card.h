#pragma once

#include"std_types.h"


#ifndef Card_h_
#define Card_h_

#define CARD_HOLDER_SIZE 30
#define MAX_CARD_NAME 24
#define MIN_CARD_NAME 20

#define CARD_ARRAY_SIZE 30
#define CARD_EXP_DATE  7

#define PAN_SIZE     30
#define MAX_PAN_NUM  20
#define MIN_PAN_NUM  16

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[CARD_HOLDER_SIZE];
	uint8_t primaryAccountNumber[PAN_SIZE];
	uint8_t cardExpirationDate[CARD_ARRAY_SIZE];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK_card, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);
uint8_t getnumOfNameChar(ST_cardData_t* cardData);
uint8_t getnumOfDateChar(ST_cardData_t* cardData);
uint8_t getnumOfPanChar(ST_cardData_t* cardData);

#endif 