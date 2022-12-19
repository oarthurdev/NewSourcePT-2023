#pragma once

#include "Language/language.h"

#define	PRIME_ITEM_TIME_3H		(60*60*3)
#define	PRIME_ITEM_TIME_6H		(60*60*6)
#define	PRIME_ITEM_TIME_12H		(60*60*12)
#define	PRIME_ITEM_TIME_24H		(60*60*24)
#define	PRIME_ITEM_TIME_7D  	(60*60*24*7)
#define	PRIME_ITEM_TIME_30D  	(60*60*24*30)

#define ITEM_KIND_PERFECT			9

#define SERVER_TCP_PORT 8000

#ifdef _GAME
#define CONNECTMAX 64
#else
#define CONNECTMAX 256
#endif

//Lag Grace = 10 minutes
#define MAX_LAGGRACE		1000 * 60 * 10
#define NUM_ENCKEYS 256

#define CONNECTMAX_MASK (CONNECTMAX - 1)

#define smSOCKBUFF_SIZE 8192
#define TRANS_RECORD_LEN (smSOCKBUFF_SIZE - 32)

#define DELET(p)			{ if(p != NULL) delete p; p = NULL;}
#define DELETA(p)			{ if(p != NULL) delete[] p; p = NULL;}