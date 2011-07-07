using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Injected
{
    public class InjectedClass
    {
        public static void InjectedMethod(int i)
        {
            if (i == 5) 
                throw new SpecialException();
        }
    }

    public class SpecialException : Exception
    {
    }
}
