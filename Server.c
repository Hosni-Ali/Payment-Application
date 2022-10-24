#include<stdio.h>
#include"Terminal.h"
#include"Card.h"
#include"Server.h"


ST_accountsDB_t AccountsDataBase[MAXDATA] =
{
	{.balance = 10000,
	  .primaryAccountNumber = {'0', '3', '4', '5', '6', '7', '8', '9', '9', '1', '2', '3', '4', '5', '6', '7', '8', '9', '9'}
	},

	{.balance = 20000,
	 .primaryAccountNumber = {'1', '3', '4', '5', '6', '7', '8', '9', '9', '1', '2', '3', '4', '5', '6', '7', '8', '9', '9'}
	},

	{.balance = 30000,
	.primaryAccountNumber = {'2', '3', '4', '5', '6', '7', '8', '9', '9', '1', '2', '3', '4', '5', '6', '7', '8', '9', '9'}
	},

	{.balance = 40000,
	.primaryAccountNumber = {'3', '3', '4', '5', '6', '7', '8', '9', '9', '1', '2', '3', '4', '5', '6', '7', '8', '9', '9'}
	}
};

ST_transaction_t tranDataBase[MAXDATA] =
{
	{
		.cardHolderData = {
			.cardHolderName = "\0",
			.cardExpirationDate = "\0",
			.primaryAccountNumber = "\0"
		},

		.terminalData = {
			.maxTransAmount = 0,
			.transactionDate = "\0",
			.transAmount = 0,
		},

		.transState = APPROVED,

		.transactionSequenceNumber = 0
	},

	{
		.cardHolderData = {
			.cardHolderName = "\0",
			.cardExpirationDate = "\0",
			.primaryAccountNumber = "\0"
		},

		.terminalData = {
			.maxTransAmount = 0,
			.transactionDate = "\0",
			.transAmount = 0,
		},

		.transState = APPROVED,

		.transactionSequenceNumber = 0
	},

	{
		.cardHolderData = {
			.cardHolderName = "\0",
			.cardExpirationDate = "\0",
			.primaryAccountNumber = "\0"
		},

		.terminalData = {
			.maxTransAmount = 0,
			.transactionDate = "\0",
			.transAmount = 0,
		},

		.transState = APPROVED,

		.transactionSequenceNumber = 0
	},

	{
		.cardHolderData = {
			.cardHolderName = "\0",
			.cardExpirationDate = "\0",
			.primaryAccountNumber = "\0"
		},

		.terminalData = {
			.maxTransAmount = 0,
			.transactionDate = "\0",
			.transAmount = 0,
		},

		.transState = APPROVED,

		.transactionSequenceNumber = 0
	}
};


ST_transaction_t New_transData;

uint8_t Acc_DB_Idx = 1000;        
uint8_t transIdx = 0;             
uint8_t sequenceIdx = 0;          


EN_cardError_t CardDataChecker[CARD_ERR_ARR_SIZE] = { WRONG_NAME,WRONG_EXP_DATE,WRONG_PAN };
EN_terminalError_t TermDataChecker[TERM_ERR_ARR_SIZE] = { WRONG_DATE,EXPIRED_CARD,INVALID_CARD,INVALID_AMOUNT,EXCEED_MAX_AMOUNT,INVALID_MAX_AMOUNT };
EN_transState_t TransactionDataChecker[TRANS_ERR_ARR_SIZE] = { DECLINED_INSUFFECIENT_FUND,DECLINED_INSUFFECIENT_FUND,DECLINED_INSUFFECIENT_FUND,DECLINED_INSUFFECIENT_FUND };
EN_serverError_t ServerDataChecker[SERV_ERR_ARR_SIZE] = { ACCOUNT_NOT_FOUND,ACCOUNT_NOT_FOUND,ACCOUNT_NOT_FOUND,ACCOUNT_NOT_FOUND };




EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{

	while (1)
	{

		ServerDataChecker[0] = isValidAccount(&transData->cardHolderData);
		ServerDataChecker[1] = isAmountAvailable(&transData->terminalData);
		ServerDataChecker[2] = saveTransaction(&transData->cardHolderData);

		if ((ServerDataChecker[0] == OK_serv) && (ServerDataChecker[1] == OK_serv) && (ServerDataChecker[2] == OK_serv))
		{


			AccountsDataBase[Acc_DB_Idx].balance = AccountsDataBase[Acc_DB_Idx].balance - tranDataBase[transIdx].terminalData.transAmount;

			printf("======================================================\n");
			printf("=     Your Transcation has been done Successfully    = \n");
			printf("======================================================\n");

			printf("======================================================\n");
			printf("=           Your Current balance is %f L.E           = \n", AccountsDataBase[Acc_DB_Idx].balance);
			printf("======================================================\n");

			transIdx++;
			sequenceIdx++;
			return APPROVED;
		}
		else if ((ServerDataChecker[0] == OK_serv) && (ServerDataChecker[1] == OK_serv) && (ServerDataChecker[2] == SAVING_FAILED))
		{

			printf("======================================================\n");
			printf("=                Internal Server Error               = \n");
			printf("======================================================\n");

			tranDataBase[transIdx].transState = INTERNAL_SERVER_ERROR;
			transIdx++;
			sequenceIdx++;

			return INTERNAL_SERVER_ERROR;
		}
		else if ((ServerDataChecker[0] == OK_serv) && (ServerDataChecker[1] == LOW_BALANCE))
		{

			printf("======================================================\n");
			printf("=              DECLINED INSUFFECIENT FUND            = \n");
			printf("======================================================\n");

			tranDataBase[transIdx].transState = DECLINED_INSUFFECIENT_FUND;
			transIdx++;
			sequenceIdx++;
			return DECLINED_INSUFFECIENT_FUND;
		}
		else if ((ServerDataChecker[0] == OK_serv) && (ServerDataChecker[1] == ACCOUNT_NOT_FOUND))
		{

			tranDataBase[transIdx].transState = ACCOUNT_NOT_FOUND;
			transIdx++;
			sequenceIdx++;
			return INTERNAL_SERVER_ERROR;
			break;
		}
		else if ((ServerDataChecker[0] == ACCOUNT_NOT_FOUND))
		{

			printf("======================================================\n");
			printf("=              DECLINED STOLEN CARD                  = \n");
			printf("======================================================\n");

			tranDataBase[transIdx].transState = DECLINED_STOLEN_CARD;
			transIdx++;
			sequenceIdx++;
			return DECLINED_STOLEN_CARD;
		}
	}
}




EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	uint8_t CmpResult;
	

	while (1)
	{


	    CardDataChecker[0] = getCardHolderName(cardData);
		if (CardDataChecker[0] != OK_card)
		{
			printf("SORRY YOUR CARD NAME IS WRONG\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}
		CardDataChecker[1] = getCardExpiryDate(cardData);
		if (CardDataChecker[1] != OK_card)
		{
			printf("SORRY YOUR CARD Expiry Date IS WRONG\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}
		CardDataChecker[2] = getCardPAN(cardData);
		if (CardDataChecker[2] != OK_card)
		{
			printf("SORRY YOUR CARD PAN ID IS WRONG\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}

		CmpResult = SearchPan_AccDB(cardData);

			if (CmpResult == 0)
			{
				memcpy(&New_transData.cardHolderData.primaryAccountNumber, cardData->primaryAccountNumber,
					sizeof(New_transData.cardHolderData.primaryAccountNumber));

				memcpy(&New_transData.cardHolderData.cardHolderName, cardData->cardHolderName,
					sizeof(&New_transData.cardHolderData.cardHolderName));

				memcpy(&New_transData.cardHolderData.cardExpirationDate, cardData->cardExpirationDate,
					sizeof(&New_transData.cardHolderData.cardExpirationDate));

				New_transData.transState = APPROVED;

				return OK_serv;
				break;
			}
			else
			{
				memcpy(&New_transData.cardHolderData.primaryAccountNumber, cardData->primaryAccountNumber,
					sizeof(New_transData.cardHolderData.primaryAccountNumber));

				memcpy(&New_transData.cardHolderData.cardHolderName, cardData->cardHolderName,
					sizeof(&New_transData.cardHolderData.cardHolderName));

				memcpy(&New_transData.cardHolderData.cardExpirationDate, cardData->cardExpirationDate,
					sizeof(&New_transData.cardHolderData.cardExpirationDate));
		
				return ACCOUNT_NOT_FOUND;
				break;
				
			}


		
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t * termData)
{
	uint8_t CmpResult;
	
	while (1)
	{

		TermDataChecker[0] = getTransactionDate(termData); 
		if (TermDataChecker[0] != OK_ter)
		{
			printf("SORRY YOUR TRANSCATION DATE IS WRONG\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}
		TermDataChecker[1] = isCardExpired(New_transData.cardHolderData, *termData); 
		if (TermDataChecker[1] != OK_ter)
		{
			printf("SORRY YOUR CARD IS EXPIRED\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}
		
		TermDataChecker[3] = getTransactionAmount(termData); 
		if (TermDataChecker[3] != OK_ter)
		{
			printf("SORRY YOUR TRANSCATION AMOUNT IS NOT CORRECT\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}

		TermDataChecker[5] = setMaxAmount(termData);
		if (TermDataChecker[5] != OK_ter)
		{
			printf("SORRY INVALID MAX AMOUNT \n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}

		TermDataChecker[4] = isBelowMaxAmount(termData); 
		if (TermDataChecker[4] != OK_ter)
		{
			printf("SORRY YOUR TRANSCATION AMOUNT IS BELOW MAX\n");
			printf("end\n");


			return ACCOUNT_NOT_FOUND;
			break;
		}

			memcpy(&New_transData.terminalData.transactionDate, termData->transactionDate,
				sizeof(New_transData.terminalData.transactionDate));

			memcpy(&New_transData.terminalData.maxTransAmount,&termData->maxTransAmount,
				sizeof(New_transData.terminalData.maxTransAmount));

			memcpy(&New_transData.terminalData.transAmount,&termData->transAmount,
				sizeof(New_transData.terminalData.transAmount));


			if (Acc_DB_Idx != 1000)
			{
				if (AccountsDataBase[Acc_DB_Idx].balance >= New_transData.terminalData.transAmount)
				{
					printf("======================================================\n");
					printf("=              UPDATING YOUR BALANCE                 = \n");
					printf("======================================================\n");

					return OK_serv;
				}
				else
				{
					return LOW_BALANCE;
				}
			}
			else
			{
				return ACCOUNT_NOT_FOUND;
			}
		
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	uint32_t SequanceDoubleCheck = 0;
	EN_serverError_t ServerErrorType = SAVING_FAILED;

	memcpy(tranDataBase[transIdx].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber,
		sizeof(transData->cardHolderData.primaryAccountNumber));

	memcpy(tranDataBase[transIdx].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName,
		sizeof(transData->cardHolderData.cardHolderName));

	memcpy(tranDataBase[transIdx].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate,
		sizeof(transData->cardHolderData.cardExpirationDate));


	memcpy(&tranDataBase[transIdx].terminalData.maxTransAmount, &transData->terminalData.maxTransAmount,
		sizeof(transData->terminalData.maxTransAmount));

	memcpy(tranDataBase[transIdx].terminalData.transactionDate, transData->terminalData.transactionDate,
		sizeof(transData->terminalData.transactionDate));

	memcpy(&tranDataBase[transIdx].terminalData.transAmount, &transData->terminalData.transAmount,
		sizeof(transData->terminalData.transAmount));


	tranDataBase[transIdx].transactionSequenceNumber = sequenceIdx + 1;

	SequanceDoubleCheck = tranDataBase[transIdx].transactionSequenceNumber;

	ServerErrorType = getTransaction(SequanceDoubleCheck, &transData);

	return ServerErrorType; 

}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{

	if (tranDataBase[transIdx].transactionSequenceNumber == transactionSequenceNumber)
	{
	
		return OK_serv;
	}
	else
	{
	
		return SAVING_FAILED;
	}
}

uint8_t SearchPan_AccDB(ST_cardData_t* cardData)
{
	uint8_t CmpResult;
	uint8_t PanIter;
	for (PanIter = 0; PanIter < MAXDATA; PanIter++)
	{
		CmpResult = memcmp(cardData->primaryAccountNumber, AccountsDataBase[PanIter].primaryAccountNumber,
			sizeof(AccountsDataBase[PanIter].primaryAccountNumber));

		if (CmpResult == 0)
		{
			printf("======================================================\n");
			printf("=         Your PAN ID Has Been Found In DataBase     = \n");
			printf("======================================================\n");
			
			Acc_DB_Idx = PanIter;
			break;
		}
		
	}

	return CmpResult;

}