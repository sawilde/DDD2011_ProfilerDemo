using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;

namespace ProfilerHost
{
    class Program
    {
        static void Main(string[] args)
        {
            var startInfo = new ProcessStartInfo(
                Path.Combine(Environment.CurrentDirectory, 
                "ProfilerTarget.exe"));

            startInfo.EnvironmentVariables.Add(
                "Cor_Profiler", "{BDD57A0C-D4F7-486D-A8CA-86070DC12FA0}");

            startInfo.EnvironmentVariables.Add(
                "Cor_Enable_Profiling", "1");

            startInfo.UseShellExecute = false;

            var process = Process.Start(startInfo);
            process.WaitForExit();
        }
    }
}
