#ifndef DLL_H
#define DLL_H
#include <QDebug>
#include <QTextCodec>
typedef int(*lib_ver)(unsigned int *pVer);
typedef int(*rf_init_com)(int port, long baud);
typedef int(*rf_ClosePort)();
typedef int(*rf_get_model)(unsigned short icdev,
	unsigned char *pVersion,
	unsigned char *pLen);
typedef int(*rf_init_device_number)(unsigned short icdev);
typedef int(*rf_get_device_number)(unsigned short *pIcdev);
typedef int(*rf_init_type)(unsigned short icdev, unsigned char type);
typedef int(*rf_light)(unsigned short icdev, unsigned char color);
typedef int(*rf_beep)(unsigned short icdev, unsigned char msec);
typedef int(*rf_cos_command)(unsigned short icdev,
	unsigned char *pCommand,
	unsigned char cmdLen,
	unsigned char *pData,
	unsigned char *pMsgLg);
typedef int(*rf_request)(unsigned short icdev,
	unsigned char model,
	unsigned short *TagType);
typedef int(*rf_ul_select)(unsigned short icdev,
	unsigned char *pSnr,
	unsigned char *pLen);
typedef int(*rf_select)(unsigned short icdev,
	unsigned char *pSnr,
	unsigned char snrLen,
	unsigned char *pSize);

typedef int(*rf_anticoll)(unsigned short icdev,
	unsigned char bcnt,
	unsigned char *pSnr,
	unsigned char *pLen);

typedef int(*rf_M1_read) (unsigned short icdev,
	unsigned char block,
	unsigned char *pData,
	unsigned char *pLen);

typedef int(*rf_ul_write)(unsigned short icdev,
	unsigned char page,
	unsigned char *pData);
typedef int(*rf_get_model)(unsigned short icdev,
	unsigned char *pVersion,
	unsigned char *pLen);

#endif