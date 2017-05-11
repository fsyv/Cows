#include "stdafx.h"
#include "NFCOperator.h"


NFCOperator::NFCOperator()
{
	m_lib = new QLibrary("MasterRD.dll");
	m_lib->load();
	if (!m_lib->isLoaded())
		exit(1);

	set_light = (rf_light)m_lib->resolve("rf_light");
	getIcdev = (rf_get_device_number)m_lib->resolve("rf_get_device_number");
	setIcdev = (rf_init_device_number)m_lib->resolve("rf_init_device_number");
	init = (rf_init_com)m_lib->resolve("rf_init_com");
	close = (rf_ClosePort)m_lib->resolve("rf_ClosePort");
	getModel = (rf_get_model)m_lib->resolve("rf_get_model");
	getCommand = (rf_cos_command)m_lib->resolve("rf_cos_command");
	request = (rf_request)m_lib->resolve("rf_request");
	select = (rf_ul_select)m_lib->resolve("rf_ul_select");
	read = (rf_M1_read)m_lib->resolve("rf_M1_read");
	write = (rf_ul_write)m_lib->resolve("rf_ul_write");
	getSIze = (rf_select)m_lib->resolve("rf_select");
	getSeq = (rf_anticoll)m_lib->resolve("rf_anticoll");
}


NFCOperator::~NFCOperator()
{
}
