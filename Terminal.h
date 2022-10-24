#pragma once

#include"std_types.h"
#include"Card.h"
#include<time.h>
#include <string.h>

#ifndef Terminal_h_
#define Terminal_h_

#define TRANSACTION_DATE_CHAR 10
#define TRANSACTION_DATE_SIZE 30

typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[TRANSACTION_DATE_SIZE];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	OK_ter, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData); 
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData); 
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);  
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);      
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);         
uint8_t getnumOfTermDateChar(ST_terminalData_t* termData);            

#endif