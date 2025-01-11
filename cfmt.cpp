#include "cfmt.h"
#include <cassert>
#include <cstdarg>
#include <fmt/args.h>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <cstring>

static void push_arg_2store(cfmt_format_arg &arg, fmt::dynamic_format_arg_store<fmt::format_context> &store)
{
	switch (arg.type) {
#define ____FORMAT_ARG_ITEM(enum, type, field)      \
	case enum: {                                \
		type data = (type)(arg.data.field); \
		store.push_back(data);              \
		break;                              \
	}

		____FORMAT_ARG_LIST;

#undef ____FORMAT_ARG_ITEM
	}
}

static void format_dynamic_arg_store_build(fmt::dynamic_format_arg_store<fmt::format_context> &store, size_t n, va_list args)
{
	unsigned i;
	for (i = 0; i < n; i++) {
		cfmt_format_arg arg = va_arg(args, cfmt_format_arg);
		push_arg_2store(arg, store);
	}
	assert(store.size() == n);
}

CFMT_API auto named_arg(const char *name, int data)
{
	return fmt::arg(name, data);
}

CFMT_API char* format_string_dup(const char *format,size_t n,...)
{
	fmt::dynamic_format_arg_store<fmt::format_context> store;
	va_list ap;

	va_start(ap,n);
	format_dynamic_arg_store_build(store,n,ap);
	va_end(ap);

	return strdup(fmt::vformat(format,store).c_str());
}

CFMT_API void format_fprint(FILE *file, const char *format, size_t n, ...)
{
	fmt::dynamic_format_arg_store<fmt::format_context> store;
	va_list ap;

	va_start(ap, n);
	format_dynamic_arg_store_build(store, n, ap);
	va_end(ap);

	std::string result = fmt::vformat(format, store);
	fmt::print(file, result);
}

CFMT_API void format_system_error_fprint(FILE *file, int error_code, const char *fmt, size_t n, ...)
{
	fmt::dynamic_format_arg_store<fmt::format_context> store;
	va_list ap;

	va_start(ap, n);
	format_dynamic_arg_store_build(store, n, ap);
	va_end(ap);

	std::string result = fmt::vformat(fmt, store);
	auto e = fmt::system_error(error_code, result);
	fmt::println(e.what());
}
