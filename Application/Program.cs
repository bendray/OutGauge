using System;
using OutGauge.Patterns;

namespace OutGauge.Application
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			using (SMMapper mapper = new SMMapper ()) {
				mapper.Run ();
			}
			Console.Write ("Press any key...");
			Console.ReadKey ();
		}
	}
}
