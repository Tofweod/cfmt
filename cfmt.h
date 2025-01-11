#ifndef TOF_CFMT_H
#define TOF_CFMT_H

#ifdef __GNUC__
#define API __attribute__((__visibility__("default")))
#else
#define API
#endif

#if defined __cplusplus
extern "C" {
#include <cstddef>
#include <cstdio>
#else
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#endif

#define CFMT_API extern API

#define ____FORMAT_ARG_LIST                                                \
	____FORMAT_ARG_ITEM(FORMAT_INT, int, i_data)                       \
	____FORMAT_ARG_ITEM(FORMAT_LONG_LONG, long long, ll_data)          \
	____FORMAT_ARG_ITEM(FORMAT_UNSIGNED, unsigned, u_data)             \
	____FORMAT_ARG_ITEM(FORMAT_UNSIGNED_LONG_LONG, unsigned long long, \
			    ull_data)                                      \
	____FORMAT_ARG_ITEM(FORMAT_DOUBLE, double, d_data)                 \
	____FORMAT_ARG_ITEM(FORMAT_FLOAT, float, f_data)                   \
	____FORMAT_ARG_ITEM(FORMAT_BOOL, bool, b_data)                     \
	____FORMAT_ARG_ITEM(FORMAT_CHAR, char, c_data)                     \
	____FORMAT_ARG_ITEM(FORMAT_STR, char *, s_data)                    \
	____FORMAT_ARG_ITEM(FOMRAT_PTR, void *, p_data)                    \
	____FORMAT_ARG_ITEM(FOMRAT_CPTR, const void *, cp_data)

enum FORMAT_TYPE {
#define ____FORMAT_ARG_ITEM(enum, ...) enum,
	____FORMAT_ARG_LIST
#undef ____FORMAT_ARG_ITEM
};

typedef union {
#define ____FORMAT_ARG_ITEM(enum, type, name) type name;
	____FORMAT_ARG_LIST;
#undef ____FORMAT_ARG_ITEM
	// to convert char* to union's const char*
	const char *cs_data;
} FORMAT_DATA;

typedef struct {
	enum FORMAT_TYPE type;
	FORMAT_DATA data;
} cfmt_format_arg;

#define FORMAT_ARG(data, type) \
	(cfmt_format_arg) { type, (FORMAT_DATA)data }
// TODO:
#define FORMAT_ARG_INT(val) \
	(cfmt_format_arg) { FORMAT_INT, .data.i_data = val }
#define FORMAT_ARG_STR(val) \
	(cfmt_format_arg) { FORMAT_STR, .data.cs_data = val }

CFMT_API char* format_string_dup(const char *format,size_t n,...);

CFMT_API void format_fprint(FILE *file, const char *format, size_t n, ...);

#define format_print(format, n, ...) format_fprint(stdout, format, n, __VA_ARGS__)

/**
 * print fmt: error_code's eror message\n
 */
CFMT_API void format_system_error_fprint(FILE *file, int error_code, const char *fmt, size_t n, ...);

// TODO:
/* CFMT_API void format_fprint(FILE *file,text_style style, const char *format, size_t n, ...); */

#ifdef __cplusplus
}
#endif
#endif
