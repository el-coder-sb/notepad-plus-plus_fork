// This file is part of Notepad++ project
// Copyright (C)2021 Pavel Nedev (pg.nedev@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#include <windows.h>
#include <string>
#include <tchar.h>
#include <cstdint>


class Win32_IO_File final
{
public:
	enum class Mode {
		WRITE,
		APPEND
	};

	Win32_IO_File(const char *fname, Mode fmode);
	Win32_IO_File(const wchar_t *fname, Mode fmode);

	Win32_IO_File() = delete;
	Win32_IO_File(const Win32_IO_File&) = delete;
	Win32_IO_File& operator=(const Win32_IO_File&) = delete;

	~Win32_IO_File() {
		close();
	};

	bool isOpened() {
		return (_hFile != INVALID_HANDLE_VALUE);
	};

	void close();
	//int_fast64_t getSize();
	unsigned long read(void *rbuf, unsigned long buf_size);
	bool write(const void *wbuf, unsigned long buf_size);

	bool writeStr(const std::string& str) {
		return write(str.c_str(), static_cast<unsigned long>(str.length()));
	};

private:
	HANDLE	_hFile		{INVALID_HANDLE_VALUE};
	Mode	_hMode		{Mode::WRITE};
	bool	_written	{false};

	const DWORD _accessParam  { GENERIC_READ | GENERIC_WRITE };
	const DWORD _shareParam   { FILE_SHARE_READ | FILE_SHARE_WRITE };
	const DWORD _dispParam    { OPEN_ALWAYS }; // Open existing file for writing without destroying it or create new
	const DWORD _attribParam  { FILE_ATTRIBUTE_NORMAL | FILE_FLAG_POSIX_SEMANTICS | FILE_FLAG_WRITE_THROUGH }; // FILE_FLAG_POSIX_SEMANTICS: distinguish between upper/lower case in name
};
