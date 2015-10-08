// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>
#include "Common/GL/GLInterfaceBase.h"

class cInterfaceWGL : public cInterfaceBase
{
public:
	void SwapInterval(int Interval);
	void Swap();
	void* GetFuncAddress(const std::string& name);
	bool Create(void *window_handle, bool core);
	bool MakeCurrent();
	bool ClearCurrent();
	void Shutdown();

	void Update();
	bool PeekMessages();

	HWND m_window_handle;
};
