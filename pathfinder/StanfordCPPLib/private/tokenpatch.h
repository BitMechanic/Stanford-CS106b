/*
 * File: tokenpatch.h
 * ------------------
 * This file renames TokenType to avoid conflict with the <windows.h>
 * header.
 */

#ifdef _MSC_VER
#  define TokenType TokenTypeT
#endif
