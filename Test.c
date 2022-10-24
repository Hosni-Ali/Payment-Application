


#include"App.h"


 ST_cardData_t New_CardData;

int main()
{


	//card name ,  pan id , expir date , 





	EN_cardError_t CardDataChecker[3] = { WRONG_NAME,WRONG_EXP_DATE,WRONG_PAN };
	//EN_cardError_t dateCheker  = WRONG_EXP_DATE;
	//EN_cardError_t panCheker   = WRONG_PAN;

	//ST_cardData_t* NameDataPassing = NULL;
	//ST_cardData_t* DateDataPassing = NULL;
	//ST_cardData_t* PanDataPassing = NULL;

	uint8_t NumOfWrongTries = 0;









	do {

		CardDataChecker[0] = getCardHolderName(&New_CardData.cardHolderName);
		printf("%d \n", CardDataChecker[0]);
		//CardDataChecker[1] = getCardExpiryDate(DateDataPassing);
		//printf("%d \n", CardDataChecker[1]);
		//CardDataChecker[2] = getCardPAN(PanDataPassing);
		//printf("%d \n", CardDataChecker[2]);

		if ((CardDataChecker[0] != OK_card) || (CardDataChecker[1] != OK_card) || (CardDataChecker[2] != OK_card))
		{


			NumOfWrongTries++;
			printf("wrong data please try again\n");
		}
		else
		{
			break;
		}

	} while (NumOfWrongTries < 3);



	printf("%d , %d \n", OK_card, WRONG_NAME);
	printf("%s \n", New_CardData.cardHolderName);


}