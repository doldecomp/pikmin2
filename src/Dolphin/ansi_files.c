#include "types.h"
#include "Dolphin/ansi_files.h"

extern int fflush(FILE* __stream);
extern void __begin_critical_region(int);
extern void __end_critical_region(int);
extern void fclose(FILE*);
static char stdin_buff[0x100];
static char stdout_buff[0x100];
static char stderr_buff[0x100];

extern int __read_console(u32, u32, u32*);
extern BOOL __write_console(s32, s32, s32*, s32);
extern int __close_console(u32);

// clang-format off
FILE __files[4] = 
{ 
	{ 0,
		0,
		1,
		1,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		&stdin_buff,
		sizeof(stdin_buff),
		&stdin_buff,
		0,
		0,
		0,
		0,
		0,
		&__read_console,
		&__write_console,
		&__close_console,
		0,
		&__files[1] 
	},
	{ 1,
		0,
		2,
		1,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		&stdout_buff,
		sizeof(stdout_buff),
		&stdout_buff,
		0,
		0,
		0,
		0,
		0,
		&__read_console,
		&__write_console,
		&__close_console,
		0,
		&__files[2] 
	},
	{ 2,
		0,
		2,
		0,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		&stderr_buff,
		sizeof(stderr_buff),
		&stderr_buff,
		0,
		0,
		0,
		0,
		0,
		&__read_console,
		&__write_console,
		&__close_console,
		0,
		&__files[3] 
	} 
};
// clang-format on

/*
 * --INFO--
 * Address:	........
 * Size:	00008C
 */
void __flush_line_buffered_output_files(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800C2A04
 * Size:	000070
 */

u32 __flush_all(void)
{
	u32 retval = 0;
	FILE* __stream;
	__stream = &__files[0];
	while (__stream) {
		if ((__stream->m_mode.file_kind) && (fflush(__stream))) {
			retval = -1;
		}
		__stream = __stream->m_nextFile;
	};
	return retval;
}

/*
 * --INFO--
 * Address:	800C2A74
 * Size:	0000A8
 */
void __close_all(void)
{
	FILE* p = &__files[0];
	FILE* plast;

	__begin_critical_region(2);

	while (p != nullptr) {
		if (p->m_mode.file_kind != __closed_file) {
			fclose(p);
		}

		plast = p;
		p     = p->m_nextFile;
		if (plast->m_isDynamicallyAllocated)
			free(plast);
		else {
			plast->m_mode.file_kind = __unavailable_file;
			if ((p != NULL) && p->m_isDynamicallyAllocated)
				plast->m_nextFile = nullptr;
		}
	}

	__end_critical_region(2);
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000DC
 */
void __init_file(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000090
 */
void __find_unopened_file(void)
{
	// UNUSED FUNCTION
}
