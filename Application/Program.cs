using System;
using System.IO;
using OutGauge.Patterns;

namespace OutGauge.Application
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			using (MemoryStream stream = new MemoryStream ()) {
				using (SMMapper mapper = new SMMapper (stream)) {
					mapper.Write ();
					using (BinaryReader br = new BinaryReader (stream)) {
						if(stream.Length > 0){
							//test
							Console.Write ("{0},{1}\r\n", br.ReadUInt32(), br.ReadUInt32());
							stream.Seek(6444, SeekOrigin.Begin);
							Console.Write ("{0}\r\n", new string(br.ReadChars(21)));
						}
					}
				}
			}
			Console.Write ("Press any key...");
			Console.ReadKey ();
		}
	}
}
