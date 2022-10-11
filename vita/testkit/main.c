#include <stdio.h>
#include <string.h>
#include <taihen.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/threadmgr.h>
#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/io/fcntl.h>

#define DUMP_PATH "ux0:dump/"
#define LOG_FILE DUMP_PATH "kplugin_log.txt"

static void log_reset();
static void dump_reset();
static void log_write(const char *buffer, size_t length);

#define LOG(...) \
	do { \
		char buffer[256]; \
		snprintf(buffer, sizeof(buffer), ##__VA_ARGS__); \
		log_write(buffer, strlen(buffer)); \
} while (0)

void _start() __attribute__ ((weak, alias ("module_start")));

int module_stop(SceSize argc, const void *args)
{
	return SCE_KERNEL_STOP_SUCCESS;
}

int module_start(SceSize argc, const void *args)
{
	//http://vitatricks.tk/timestamp.html
	//00e248dc  8fbdc580
	//mydate[1] mydate[2]
	//14 May 2019 18:54:38
	ksceIoMkdir(DUMP_PATH, 6);
	log_reset();
	uintptr_t stub;

	int res = module_get_export_func(KERNEL_PID, "SceRtc", TAI_ANY_LIBRARY, 0xAAB6053F, &stub);
	LOG("res = %08x\n", res);
	if(res==0){
		int (*myfunc) (unsigned int*) = (int *) stub;
		unsigned int mydate[2]; 
		mydate[0] = 0xA5800; 
		mydate[1] = 0xE1D480;   
		int ret = myfunc(mydate);
		LOG("ret = %08x\n", ret);
	}

	res = module_get_export_func(KERNEL_PID, "SceRtc", TAI_ANY_LIBRARY, 0x70A78CD2, &stub);
	LOG("res = %08x\n", res);
	if(res==0){
		int (*myfunc) (unsigned int*) = (int *) stub;
		unsigned int mydate[2]; 
		mydate[0] = 0xA5800; 
		mydate[1] = 0xE1D480;   
		int ret = myfunc(mydate);
		LOG("ret = %08x\n", ret);
	}

	res = module_get_export_func(KERNEL_PID, "SceRtc", TAI_ANY_LIBRARY, 0x162E486E, &stub);
	LOG("res = %08x\n", res);
	if(res==0){
		int (*myfunc) (unsigned int*) = (int *) stub;
		unsigned int mydate[2]; 
		mydate[0] = 0xA5800; 
		mydate[1] = 0xE1D480;   
		int ret = myfunc(mydate);
		LOG("ret = %08x\n", ret);
	}

	res = module_get_export_func(KERNEL_PID, "SceRtc", TAI_ANY_LIBRARY, 0x7D431C87 , &stub);
	LOG("res = %08x\n", res);
	if(res==0){
		int (*myfunc) (unsigned int*) = (int *) stub;
		unsigned int mydate[2]; 
		mydate[0] = 0xA5800; 
		mydate[1] = 0xE1D480;   
		int ret = myfunc(mydate);
		LOG("ret = %08x\n", ret);
	}
	return SCE_KERNEL_START_SUCCESS;
}

void log_reset()
{
	SceUID fd = ksceIoOpen(LOG_FILE,
		SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 6);
	if (fd < 0)
		return;

	ksceIoClose(fd);
}

void log_write(const char *buffer, size_t length)
{
	extern int ksceIoMkdir(const char *, int);
	ksceIoMkdir(DUMP_PATH, 6);

	SceUID fd = ksceIoOpen(LOG_FILE,
		SCE_O_WRONLY | SCE_O_CREAT | SCE_O_APPEND, 6);
	if (fd < 0)
		return;

	ksceIoWrite(fd, buffer, length);
	ksceIoClose(fd);
}