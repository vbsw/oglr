/*
 *          Copyright 2022, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

package oglr

// #cgo CFLAGS: -DOGLR_WIN32 -DUNICODE
// #cgo LDFLAGS: -luser32 -lgdi32 -lOpenGL32
// #include "oglr.h"
import "C"
import (
	"errors"
	"strconv"
	"unsafe"
)

// Init initializes OpenGL functions. An OpenGL context must have been set current
// before calling this function.
func Init() error {
	var err error
	if !initialized {
		var errC unsafe.Pointer
		C.oglr_init(&errC)
		err = toError(errC)
		initialized = bool(err == nil)
	}
	return err
}

// WGLFunctions returns pointer to wglChoosePixelFormatARB and wglCreateContextAttribsARB.
// Call Init first before calling this function.
func WGLFunctions() (unsafe.Pointer, unsafe.Pointer) {
	if initialized {
		var cpf, cca unsafe.Pointer
		C.oglr_wgl_ctx_functions(&cpf, &cca)
		return cpf, cca
	}
	panic(notInitialized)
}

// toError converts C error to Go error.
func toError(errC unsafe.Pointer) error {
	if errC != nil {
		var errStr string
		var errNumC C.int
		var errWin32 C.oglr_ul_t
		var errStrC *C.char
		C.oglr_error(errC, &errNumC, &errWin32, &errStrC)
		switch errNumC {
		case 1:
			errStr = "allocate memory failed"
		case 2:
			errStr = "loading OpenGL funtion failed"
		default:
			errStr = "unknown error " + strconv.FormatUint(uint64(errNumC), 10)
		}
		if errWin32 != 0 {
			errStr = errStr + " (" + strconv.FormatUint(uint64(errWin32), 10) + ")"
		}
		if errStrC != nil {
			errStr = errStr + "; " + C.GoString(errStrC)
		}
		C.oglr_error_free(errC)
		return errors.New(errStr)
	}
	return nil
}
