#pragma once
#include "dll.h"
#include <QLibrary>

class NFCOperator
{
private:
	QLibrary *m_lib;
public:
	NFCOperator();
	~NFCOperator();
public:
	
	rf_init_device_number setIcdev;
	rf_get_device_number getIcdev;
	rf_light set_light;
	rf_init_com init;
	rf_ClosePort close;
	rf_get_model getModel;
	rf_request request;
	rf_ul_select  select;
	rf_M1_read read;
	rf_ul_write write;
	rf_select getSIze;
	rf_anticoll getSeq;
	rf_cos_command getCommand;


};

