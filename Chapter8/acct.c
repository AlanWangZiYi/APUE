#include "../include/apue.h"
#include "../include/error.h"
#include <sys/acct.h>

#define FMT "%-*.*s e=%6ld, chars = %7ld, %c %c %c %c\n"

static unsigned long compt2ulong(comp_t comptime)    /* convert comp_t to unsigned long */
{
	unsigned long   val;
        int             exp;
		 
	val = comptime & 0x1fff;    /* 13-bit fraction */
	exp = (comptime >> 13) & 7; /* 3-bit exponent (0-7) */
	while (exp-- > 0)
		val *= 8;
	return(val);
}


int main(int argc, char* argv[])
{
	struct acct_v3 acdata;
	FILE *fp;

	if((fp = fopen(argv[1], "r")) == NULL)
		err_sys("open error");

	while(fread(&acdata, sizeof(acdata), 1, fp) == 1)
	{
		printf(FMT, (int)sizeof(acdata.ac_comm), (int)sizeof(acdata.ac_comm),
				acdata.ac_comm,
				compt2ulong(acdata.ac_etime), 
				compt2ulong(acdata.ac_io),  
				acdata.ac_flag & ACORE ? 'D' : ' ',
				acdata.ac_flag & AXSIG ? 'X' : ' ',
				acdata.ac_flag & AFORK ? 'F' : ' ',
				acdata.ac_flag & ASU ? 'S' : ' ');
	}
	if(ferror(fp))
		err_sys("read error");
	exit(0);
}
