#ifndef SNDDATA_H
#define SNDDATA_H

#define BUF_SIZE 134
#define SV_CHAR char
#define SV_U16 unsigned short
struct SNDDATA {
	SV_CHAR CODE[64];
	SV_CHAR STATE[64];
	SV_U16 u16X, u16Y;
};

int setdata(char * Buffer, const struct SNDDATA  *p);
int buffer2data(struct SNDDATA *precv,const char * Buffer);

#endif