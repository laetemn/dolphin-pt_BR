// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#ifdef __APPLE__
#import <AppKit/AppKit.h>
#endif

#include "Common/GL/GLInterfaceBase.h"

class cInterfaceAGL : public cInterfaceBase
{
private:
	NSView *cocoaWin;
	NSOpenGLContext *cocoaCtx;
public:
	void Swap();
	bool Create(void *window_handle, bool core);
	bool MakeCurrent();
	bool ClearCurrent();
	void Shutdown();
	void Update();
	void SwapInterval(int interval);

};
