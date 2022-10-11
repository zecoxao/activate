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
	//https://www.epochconverter.com/hex
	//myfunc(0x5CDB121F)
	//Tuesday, 14 May 2019 19:08:15
	ksceIoMkdir(DUMP_PATH, 6);
	log_reset();
    uintptr_t stub;

    int res = module_get_export_func(KERNEL_PID, "SceSblPostSsMgr", 0x2254e1b2, 0x3f9bdedf, &stub);
    if(res==0){
        void (*myfunc) (int) = (void *) stub;
        myfunc(0x4B3D6531);
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