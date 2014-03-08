#include "..\Include\Patterns.h"
#include <string.h>
#include <stdio.h>

using namespace OutGauge;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

#define MAP_OBJECT_NAME L"$pcars$"

void Patterns::SMMapper::Write() {

	if(m_sharedData) {
		try
		{
			const int size = sizeof(SharedMemory);

			array<System::Byte> ^buffer = gcnew array<System::Byte>(size);

			Marshal::Copy((System::IntPtr)m_sharedData, buffer, 0, size);

			BinaryWriter ^bw = gcnew BinaryWriter(m_stream);

			bw->Write(buffer);

			m_stream->Seek (0, SeekOrigin::Begin);

			return;

		}
		catch (System::Exception^ ex)
		{
			throw ex;
		}
	}
}

Patterns::SMMapper::SMMapper(System::IO::MemoryStream^ stream) {

	this->m_stream = stream;

	m_fileHandle = OpenFileMapping( PAGE_READONLY, FALSE, MAP_OBJECT_NAME );
	if (m_fileHandle == INVALID_HANDLE_VALUE)
	{
		printf( "Could not open file mapping object (%d).\n", GetLastError() );
		return;
	}

	// Get the data structure
	m_sharedData = (SharedMemory*)MapViewOfFile( m_fileHandle, PAGE_READONLY, 0, 0, sizeof(SharedMemory) );
	if (m_sharedData == NULL)
	{
		printf( "Could not map view of file (%d).\n", GetLastError() );
		return;
	}

	// Ensure we're sync'd to the correct data version
	if ( m_sharedData->mVersion != SHARED_MEMORY_VERSION )
	{
		printf("Data version mismatch\n");
		return;
	}
}

Patterns::SMMapper::~SMMapper() {
	this->!SMMapper();
}

Patterns::SMMapper::!SMMapper() {
	if(m_sharedData)
		UnmapViewOfFile(m_sharedData);
	if(m_fileHandle != INVALID_HANDLE_VALUE && m_fileHandle != 0) {
		if(CloseHandle(m_fileHandle))
			m_fileHandle = INVALID_HANDLE_VALUE;
	}
}