/*
 *          Copyright 2021, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

#if defined(OGLR_WIN32)


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <gl/GL.h>
#include "oglr.h"

// from wglext.h
typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
typedef int (WINAPI * PFNWGLGETSWAPINTERVALEXTPROC) (void);
// from glcorearb.h
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef GLuint(APIENTRY *PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRY *PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef GLuint(APIENTRY *PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRY *PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRY *PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLint(APIENTRY *PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY *PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, GLvoid **pointer);
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRY *PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY *PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLDELETESHADERPROC) (GLuint shader);
typedef GLint(APIENTRY *PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY *PFNGLGENERATEMIPMAPPROC) (GLenum target);

static PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB    = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC         wglSwapIntervalEXT         = NULL;
static PFNWGLGETSWAPINTERVALEXTPROC      wglGetSwapIntervalEXT      = NULL;

static PFNGLCREATESHADERPROC            glCreateShader            = NULL;
static PFNGLSHADERSOURCEPROC            glShaderSource            = NULL;
static PFNGLCOMPILESHADERPROC           glCompileShader           = NULL;
static PFNGLGETSHADERIVPROC             glGetShaderiv             = NULL;
static PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog        = NULL;
static PFNGLCREATEPROGRAMPROC           glCreateProgram           = NULL;
static PFNGLATTACHSHADERPROC            glAttachShader            = NULL;
static PFNGLLINKPROGRAMPROC             glLinkProgram             = NULL;
static PFNGLVALIDATEPROGRAMPROC         glValidateProgram         = NULL;
static PFNGLGETPROGRAMIVPROC            glGetProgramiv            = NULL;
static PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog       = NULL;
static PFNGLGENBUFFERSPROC              glGenBuffers              = NULL;
static PFNGLGENVERTEXARRAYSPROC         glGenVertexArrays         = NULL;
static PFNGLGETATTRIBLOCATIONPROC       glGetAttribLocation       = NULL;
static PFNGLBINDVERTEXARRAYPROC         glBindVertexArray         = NULL;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
static PFNGLVERTEXATTRIBPOINTERPROC     glVertexAttribPointer     = NULL;
static PFNGLBINDBUFFERPROC              glBindBuffer              = NULL;
static PFNGLBUFFERDATAPROC              glBufferData              = NULL;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = NULL;
static PFNGLUSEPROGRAMPROC              glUseProgram              = NULL;
static PFNGLDELETEVERTEXARRAYSPROC      glDeleteVertexArrays      = NULL;
static PFNGLDELETEBUFFERSPROC           glDeleteBuffers           = NULL;
static PFNGLDELETEPROGRAMPROC           glDeleteProgram           = NULL;
static PFNGLDELETESHADERPROC            glDeleteShader            = NULL;
static PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation      = NULL;
static PFNGLUNIFORMMATRIX4FVPROC        glUniformMatrix4fv        = NULL;
static PFNGLUNIFORMMATRIX3FVPROC        glUniformMatrix3fv        = NULL;
static PFNGLUNIFORMMATRIX2X3FVPROC      glUniformMatrix2x3fv      = NULL;
static PFNGLGENERATEMIPMAPPROC          glGenerateMipmap          = NULL;
static PFNGLACTIVETEXTUREPROC           glActiveTexture           = NULL;

typedef struct {
	int err_num;
	oglr_ul_t err_win32;
	char *err_str;
} error_t;

static error_t err_no_mem = {1, ERROR_SUCCESS, NULL};

static void *error_new(const int err_num, const DWORD err_win32, char *const err_str) {
	error_t *const err = (error_t*)malloc(sizeof(error_t));
	err->err_num = err_num;
	err->err_win32 = (oglr_ul_t)err_win32;
	err->err_str = err_str;
	return err;
}

static PROC get_proc(LPCSTR const func_name, void **const err) {
	PROC proc = NULL;
	if (err[0] == NULL) {
		// wglGetProcAddress could return -1, 1, 2 or 3 on failure (https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions).
		proc = wglGetProcAddress(func_name);
		const DWORD err_win32 = GetLastError();
		if (err_win32) {
			char *const err_str = (char*)malloc(sizeof(char) * 100);
			proc = NULL;
			if (err_str) {
				const size_t length0 = strlen(func_name) + 1;
				memcpy(err_str, func_name, length0);
				err[0] = error_new(2, err_win32, err_str);
			} else {
				err[0] = (void*)&err_no_mem;
			}
		}
	}
	return proc;
}

static void wgl_functions_init(void **const err) {
	wglChoosePixelFormatARB    = (PFNWGLCHOOSEPIXELFORMATARBPROC)    get_proc("wglChoosePixelFormatARB",    err);
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) get_proc("wglCreateContextAttribsARB", err);
	wglSwapIntervalEXT         = (PFNWGLSWAPINTERVALEXTPROC)         get_proc("wglSwapIntervalEXT",         err);
	wglGetSwapIntervalEXT      = (PFNWGLGETSWAPINTERVALEXTPROC)      get_proc("wglGetSwapIntervalEXT",      err);
}

static void ogl_functions_init(void **const err) {
	glCreateShader            = (PFNGLCREATESHADERPROC)            get_proc("glCreateShader",            err);
	glShaderSource            = (PFNGLSHADERSOURCEPROC)            get_proc("glShaderSource",            err);
	glCompileShader           = (PFNGLCOMPILESHADERPROC)           get_proc("glCompileShader",           err);
	glGetShaderiv             = (PFNGLGETSHADERIVPROC)             get_proc("glGetShaderiv",             err);
	glGetShaderInfoLog        = (PFNGLGETSHADERINFOLOGPROC)        get_proc("glGetShaderInfoLog",        err);
	glCreateProgram           = (PFNGLCREATEPROGRAMPROC)           get_proc("glCreateProgram",           err);
	glAttachShader            = (PFNGLATTACHSHADERPROC)            get_proc("glAttachShader",            err);
	glLinkProgram             = (PFNGLLINKPROGRAMPROC)             get_proc("glLinkProgram",             err);
	glValidateProgram         = (PFNGLVALIDATEPROGRAMPROC)         get_proc("glValidateProgram",         err);
	glGetProgramiv            = (PFNGLGETPROGRAMIVPROC)            get_proc("glGetProgramiv",            err);
	glGetProgramInfoLog       = (PFNGLGETPROGRAMINFOLOGPROC)       get_proc("glGetProgramInfoLog",       err);
	glGenBuffers              = (PFNGLGENBUFFERSPROC)              get_proc("glGenBuffers",              err);
	glGenVertexArrays         = (PFNGLGENVERTEXARRAYSPROC)         get_proc("glGenVertexArrays",         err);
	glGetAttribLocation       = (PFNGLGETATTRIBLOCATIONPROC)       get_proc("glGetAttribLocation",       err);
	glBindVertexArray         = (PFNGLBINDVERTEXARRAYPROC)         get_proc("glBindVertexArray",         err);
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) get_proc("glEnableVertexAttribArray", err);
	glVertexAttribPointer     = (PFNGLVERTEXATTRIBPOINTERPROC)     get_proc("glVertexAttribPointer",     err);
	glBindBuffer              = (PFNGLBINDBUFFERPROC)              get_proc("glBindBuffer",              err);
	glBufferData              = (PFNGLBUFFERDATAPROC)              get_proc("glBufferData",              err);
	glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) get_proc("glGetVertexAttribPointerv", err);
	glUseProgram              = (PFNGLUSEPROGRAMPROC)              get_proc("glUseProgram",              err);
	glDeleteVertexArrays      = (PFNGLDELETEVERTEXARRAYSPROC)      get_proc("glDeleteVertexArrays",      err);
	glDeleteBuffers           = (PFNGLDELETEBUFFERSPROC)           get_proc("glDeleteBuffers",           err);
	glDeleteProgram           = (PFNGLDELETEPROGRAMPROC)           get_proc("glDeleteProgram",           err);
	glDeleteShader            = (PFNGLDELETESHADERPROC)            get_proc("glDeleteShader",            err);
	glGetUniformLocation      = (PFNGLGETUNIFORMLOCATIONPROC)      get_proc("glGetUniformLocation",      err);
	glUniformMatrix3fv        = (PFNGLUNIFORMMATRIX3FVPROC)        get_proc("glUniformMatrix3fv",        err);
	glUniformMatrix4fv        = (PFNGLUNIFORMMATRIX4FVPROC)        get_proc("glUniformMatrix4fv",        err);
	glUniformMatrix2x3fv      = (PFNGLUNIFORMMATRIX2X3FVPROC)      get_proc("glUniformMatrix2x3fv",      err);
	glGenerateMipmap          = (PFNGLGENERATEMIPMAPPROC)          get_proc("glGenerateMipmap",          err);
	glActiveTexture           = (PFNGLACTIVETEXTUREPROC)           get_proc("glActiveTexture",           err);
}

void oglr_error(void *const err, int *const err_num, oglr_ul_t *const err_win32, char **const err_str) {
	error_t *const error = (error_t*)err;
	err_num[0] = error->err_num;
	err_win32[0] = error->err_win32;
	err_str[0] = error->err_str;
}

void oglr_init(void **const err) {
	wgl_functions_init(err);
	ogl_functions_init(err);
}

void oglr_free(void *const data) {
	free(data);
}

void oglr_error_free(void *const data) {
	error_t *const err = (error_t*)data;
	if (err[0].err_str) {
		free(err[0].err_str);
		err[0].err_str = NULL;
	}
	if (err != &err_no_mem)
		free(data);
}

/* #if defined(_OGLWIN_WIN32) */
#endif
