#include "../include/EERTOS.h"

// подсчет контрольной суммы
u08 checksumCalc(u08 *Address, u16 size)
{
	u08 CheckSum = 0;

	for(u16 ix = 0; ix < size; ix++ ) {
		CheckSum += *Address;
		Address++;
	}

	return (~CheckSum + 1);
}

// проверка совпадения контрольной суммы
u08 check_sum(u08 *Address, u16 size)
{
	u08 CheckSum = 0;

	for(u16 ix = 0; ix < size; ix++ ) {
		CheckSum += *Address;
		Address++;
	}

	if(CheckSum == 0)
		return 1;
	else
		return 0;
}

