#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"


NameCard* MakeNameCard(char* name, char* phone)
{
	NameCard* reNameCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(reNameCard->name, name);
	strcpy(reNameCard->phone, phone);
	return reNameCard;
}

void ShowNameCardInfo(NameCard* pcard)
{
}

int NameCompare(NameCard* pcard, char* name)
{
	return 0;
}

void ChangePhoneNum(NameCard* pcard, char* phone)
{
}
