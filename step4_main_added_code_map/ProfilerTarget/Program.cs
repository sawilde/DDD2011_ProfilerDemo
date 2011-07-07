using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProfilerTarget
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Diagnostics.Debugger.Break();
            try {
                for (int i = 0; i < 15; i++)
                    TargetMethod(i);
            }
            catch (Exception e) {
                Console.WriteLine("Caught exception of type {0}",
                    e.GetType().FullName);
            }
        }

        static void TargetMethod(int i)
        {
            if (i == 10) throw new InvalidOperationException();
            Console.WriteLine("{0}", i);
        }
    }
}
