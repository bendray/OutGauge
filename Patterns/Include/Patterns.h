#include "OutGauge.h"
#include "SharedMemory.h"
#include <windows.h>

namespace OutGauge {
	namespace Patterns {
		
		//public value class OutGaugePack {};
 		public ref class SMMapper {
		private: 
			HANDLE m_fileHandle;
			SharedMemory* m_sharedData;
			System::IO::MemoryStream^ m_stream;
		public:
			SMMapper(System::IO::MemoryStream^);
			~SMMapper();
			!SMMapper();
			void Write();

			property System::IO::MemoryStream^ pStream {
				System::IO::MemoryStream^ get() { return m_stream; }
			private: void set(System::IO::MemoryStream^ value) { m_stream = value; }
			}
		private:
			//
		};
	}
}