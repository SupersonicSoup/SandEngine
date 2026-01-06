#pragma once

void _check_gl_error(const char* file, int line);
bool _gl_has_error();

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)
#define gl_has_error() _gl_has_error()