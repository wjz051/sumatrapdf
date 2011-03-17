/* Copyright 2006-2011 the SumatraPDF project authors (see ../AUTHORS file).
   License: FreeBSD (see ./COPYING) */

#ifndef TStrUtil_h
#define TStrUtil_h

/* currently, we always need both of these:
 * - StrUtil.h for DBG_OUT and
 * - WStrUtil.h for multibyte_to_wstr and wstr_to_multibyte */
#include "StrUtil.h"
#include "WStrUtil.h"

#ifdef UNICODE
#define CF_T_TEXT CF_UNICODETEXT
#else
#define CF_T_TEXT CF_TEXT
#endif

#ifdef _UNICODE
  #define tchar_is_ws       iswspace
  #define tstr_find_char    wstr_find_char

  #define tstr_endswith     wstr_endswith
  #define tstr_endswithi    wstr_endswithi
  #define tstr_empty        wstr_empty
  #define tstr_copy         wstr_copy
  #define tstr_copyn        wstr_copyn
  #define tstr_dupn         wstr_dupn
  #define tstr_cat_s        wstr_cat_s
  #define tstr_catn_s       wstr_catn_s
  #define tstr_cat          wstr_cat
  #define tstr_printf       wstr_printf
  #define tstr_printf_s     wstr_printf_s

  #define multibyte_to_tstr(src, CodePage)  multibyte_to_wstr((src), (CodePage))
  #define tstr_to_multibyte(src, CodePage)  wstr_to_multibyte((src), (CodePage))
  #define wstr_to_tstr(src)                 Str::Dup((LPCWSTR)src)
  #define tstr_to_wstr(src)                 Str::Dup((LPCWSTR)src)
  #define DBG_OUT_T     DBG_OUT_W

  #define wstr_to_tstr_q(src)               (src)
  #define tstr_to_wstr_q(src)               (src)
#else
  #define tchar_is_ws       isspace
  #define tstr_find_char    str_find_char

  #define tstr_endswith     str_endswith
  #define tstr_endswithi    str_endswithi
  #define tstr_empty        str_empty
  #define tstr_copy         str_copy
  #define tstr_copyn        str_copyn
  #define tstr_dupn         str_dupn
  #define tstr_cat_s        str_cat_s
  #define tstr_catn_s       str_catn_s
  #define tstr_cat          str_cat
  #define tstr_printf       str_printf
  #define tstr_printf_s     str_printf_s

  #define multibyte_to_tstr(src, CodePage)  multibyte_to_str((src), (CodePage))
  #define tstr_to_multibyte(src, CodePage)  str_to_multibyte((src), (CodePage))
  #define wstr_to_tstr(src)                 wstr_to_multibyte((src), CP_ACP)
  #define tstr_to_wstr(src)                 multibyte_to_wstr((src), CP_ACP)
  #define DBG_OUT_T     DBG_OUT

static inline char *wstr_to_tstr_q(WCHAR *src)
{
    if (!src) return NULL;
    char *str = wstr_to_tstr(src);
    free(src);
    return str;
}
static inline WCHAR *tstr_to_wstr_q(char *src)
{
    if (!src) return NULL;
    WCHAR *str = tstr_to_wstr(src);
    free(src);
    return str;
}
#endif

#define   utf8_to_tstr(src) multibyte_to_tstr((src), CP_UTF8)
#define   tstr_to_utf8(src) tstr_to_multibyte((src), CP_UTF8)
#define   ansi_to_tstr(src) multibyte_to_tstr((src), CP_ACP)
#define   tstr_to_ansi(src) tstr_to_multibyte((src), CP_ACP)

int       tstr_trans_chars(TCHAR *str, const TCHAR *oldChars, const TCHAR *newChars);
TCHAR *   tstr_url_encode(const TCHAR *str);
int       tstr_skip(const TCHAR **strp, const TCHAR *expect);
int       tstr_copy_skip_until(const TCHAR **strp, TCHAR *dst, size_t dst_size, TCHAR stop);
TCHAR *   tstr_parse_possibly_quoted(TCHAR **txt);

#endif
