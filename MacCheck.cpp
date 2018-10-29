#include <stdio.h>
#include <sys/types.h>
#include <regex.h> 

int is_valid_mac_addr(const char* mac) 
{ 
	int status;
	const char * pattern = "^([A-Fa-f0-9]{2}[-,:]){5}[A-Fa-f0-9]{2}$";
	const int cflags = REG_EXTENDED | REG_NEWLINE;
	char ebuf[128];
	regmatch_t pmatch[1];
	int nmatch = 10;
	regex_t reg;

	status = regcomp(&reg, pattern, cflags);//编译正则模式
	if(status != 0) 
	{
		regerror(status, &reg, ebuf, sizeof(ebuf));
		fprintf(stderr, "regcomp fail: %s , pattern '%s' \n",ebuf, pattern);
		regfree(&reg);
		return -1;
	} 

	status = regexec(&reg, mac, nmatch, pmatch,0);//执行正则表达式和缓存的比较,
	if(status != 0) 
	{
		regerror(status, &reg, ebuf, sizeof(ebuf));
		fprintf(stderr, "regexec fail: %s , mac:\"%s\" \n", ebuf, mac);
		regfree(&reg);
		return -1;
	}

	printf("[%s] match success.\n", __FUNCTION__);
	regfree(&reg);
	return 0;
}
