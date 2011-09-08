
#ifndef _JSON_H_
#define _JSON_H_

#define ENTER_LEVEL()	{			\
	m_CurrentDocLevel++;			\
	m_CurrentPadding += L'\t';		\
	m_CurrentPadding_UTF8 += '\t';	\
	}

#define LEAVE_LEVEL()														\
	if (--m_CurrentDocLevel >= 0) {											\
		m_CurrentPadding.erase(m_CurrentPadding.size() - 1, 1);				\
		m_CurrentPadding_UTF8.erase(m_CurrentPadding_UTF8.size() - 1, 1);	\
	}


extern "C" int json_parse_bytes(const char *bytes, size_t length, void **param);

#endif

#include "os_spec.h"
#include "utf8.h"
#include "json_type.h"
#include "json_value.h"
#include "json_null_value.h"
#include "json_boolean_value.h"
#include "json_integer_value.h"
#include "json_double_value.h"
#include "json_string_value.h"
#include "json_object_value.h"
#include "json_array_value.h"
#include "json_value_factory.h"
#include "json_engine.h"
#include "json_input_source.h"
#include "json_scanner.h"
#include "json_document.h"
