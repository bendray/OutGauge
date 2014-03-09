using System;
using System.IO;
using OutGauge.Patterns;

namespace OutGauge.Application
{
	class MainClass
	{

		public static void Main (string[] args)
		{
			bool isRunning = false;
			Console.CancelKeyPress += delegate(object sender, ConsoleCancelEventArgs e) {
				isRunning = false;
			};
			using (MemoryStream stream = new MemoryStream ()) {
				using (SMMapper mapper = new SMMapper (stream)) {
						mapper.Write ();
					using (BinaryReader br = new BinaryReader (stream, System.Text.Encoding.ASCII)) {
						if(stream.Length > 0) {
							isRunning = true;
							while (isRunning) {
								Console.SetCursorPosition (0, 0);
								stream.Seek (0, SeekOrigin.Begin);
								mapper.Write ();
								Console.Write ("{0}, {1}, {2}, {3}, {4}\r\n", 
									br.ReadUInt32 (), 
									br.ReadUInt32 (), 
									br.ReadUInt32 (), 
									br.ReadUInt32 (),
									br.ReadUInt32 ());
								stream.Seek(6428, SeekOrigin.Begin);
								Console.Write ("Throttle: {0:F1}\r\nBrake: {1:F1}\r\n", 
									br.ReadSingle (), 
									br.ReadSingle ());
								float steering = br.ReadSingle ();
								bool isNegativeSteer = steering < 0;
								Console.Write ("Steering: {0}{1:F3}\r\nClutch: {2:F1}\r\n", 
									(isNegativeSteer ? "-" : " "),
									Math.Abs(steering),
									br.ReadSingle ());
								stream.Seek(6444, SeekOrigin.Begin);
								Console.Write ("{0}\r\n", new string(br.ReadChars(21)));
							}
						}
					}
				}
			}
			Console.Write ("\r\nPress any key...");
			Console.ReadKey ();
		}			
	}
}
