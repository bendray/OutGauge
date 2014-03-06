#include "..\Include\Patterns.h"
#include <stdio.h>

using namespace OutGauge;

#define MAP_OBJECT_NAME L"$pcars$"

void Patterns::SMMapper::Run() {
	
	if(m_sharedData) {
		//	printf( "%d \n", m_sharedData->mVersion);
		//	printf( "%d \n", m_sharedData->mBuildVersionNumber);
		//	printf( "%d \n", m_sharedData->mGameState);
		//	printf( "%s \n", m_sharedData->mCarName);
	}

	return;
}

Patterns::SMMapper::SMMapper() {

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