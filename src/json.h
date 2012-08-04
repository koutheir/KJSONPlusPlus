
/*
Copyright 2011-2011 Koutheir Attouchi. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY KOUTHEIR ATTOUCHI ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL KOUTHEIR ATTOUCHI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Koutheir Attouchi.
*/

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
#include "buffer.h"
#include "utf8.h"
#include "base85_enc.h"
#include "base85_dec.h"
#include "iso8601.h"
#include "json_type.h"
#include "json_value.h"
#include "json_null_value.h"
#include "json_boolean_value.h"
#include "json_integer_value.h"
#include "json_double_value.h"
#include "json_binary_value.h"
#include "json_datetime_value.h"
#include "json_string_value.h"
#include "json_object_value.h"
#include "json_array_value.h"
#include "json_value_factory.h"
#include "json_engine.h"
#include "json_input_source.h"
#include "json_scanner.h"
#include "json_document.h"
