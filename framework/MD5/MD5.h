//---------------------------------------------------------------------- 
//include protection
#ifndef MD5_H
#define MD5_H

//---------------------------------------------------------------------- 
//STL includes
#include <string>

//---------------------------------------------------------------------- 
//typedefs
typedef unsigned char *POINTER;

/*
 * MD5 context.
 */
typedef struct 
{
	unsigned long int state[4];   	      /* state (ABCD) */
	unsigned long int count[2]; 	      /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];	      /* input buffer */
} MD5_CTX;

/*
 * MD5 class
 */
class MD5
{

	private:

		void MD5Transform (unsigned long int state[4], unsigned char block[64]);
		void Encode (unsigned char*, unsigned long int*, unsigned int);
		void Decode (unsigned long int*, unsigned char*, unsigned int);
		void MD5_memcpy (POINTER, POINTER, unsigned int);
		void MD5_memset (POINTER, int, unsigned int);

	public:
	
		void MD5Init (MD5_CTX*);
		void MD5Update (MD5_CTX*, unsigned char*, unsigned int);
		void MD5Final (unsigned char [16], MD5_CTX*);

	MD5(){};
};

//---------------------------------------------------------------------- 
//End of include protection
#endif

/*
 * EOF
 */
