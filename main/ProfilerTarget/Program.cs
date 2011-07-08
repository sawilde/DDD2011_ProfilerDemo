using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace ProfilerTarget
{
    class Program
    {
        static void Main(string[] args)
        {
            OnMethodToInstrument("hello", new EventArgs());
        }

        static void OnMethodToInstrument(object sender, EventArgs e)
        {
            Console.WriteLine("OnDoThingInstrument");
        }
    }
}
