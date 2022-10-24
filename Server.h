#pragma once

#include"std_types.h"
#include"Card.h"
#include"Terminal.h"


#ifndef Server_h_
#define Server_h_

#define MAXDATA 255
#define MAX_NUMBER_OF_TRIES 3

#define CARD_ERR_ARR_SIZE  3
#define TERM_ERR_ARR_SIZE  6
#define TRANS_ERR_ARR_SIZE  4
#define SERV_ERR_ARR_SIZE  4

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;               
	ST_terminalData_t terminalData;
	EN_transState_t transState;                
	uint32_t transactionSequenceNumber;       
}ST_transaction_t;




typedef enum EN_serverError_t
{
	OK_serv, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;


typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
uint8_t SearchPan_AccDB(ST_cardData_t* cardData);


#endif 