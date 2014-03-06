#include "OutGauge.h"
#include "SharedMemory.h"
#include <windows.h>

namespace OutGauge {
	namespace Patterns {
 		public ref class SMMapper {
		private: 
			HANDLE m_fileHandle;
			const SharedMemory* m_sharedData;
		public:
			SMMapper();
			~SMMapper();
			!SMMapper();
			void Run();
		private:
			//
		};
	}
}