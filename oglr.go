/*
 *          Copyright 2021, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

// Package oglr renders graphics using OpenGL.
package oglr

// Context provides OpenGL context functions.
type Context interface {
	MakeCurrent() error
	Release() error
	SwapBuffers() error
}
