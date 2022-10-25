

#include<stdio.h>
#include"App.h"
#include "Terminal.h"
#include "Server.h"



	int main()
	{
		appStart();
	
	}


	void appStart(void)
	{

		ST_transaction_t New_transData;

		while (1)
		{

			New_transData.transState = recieveTransactionData(&New_transData);

			if (New_transData.transState == APPROVED)
			{
				printf("======================================================\n");
				printf("=     Your Transcation has been done Successfully    = \n");
				printf("======================================================\n");


			}
			break;

		}
	}


