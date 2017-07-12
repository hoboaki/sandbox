using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestLib
{
    public static class PrefixExpression
    {
        public static void Inc(int aA0)
        {
            ++aA0;
        }

        public static void Dec(int aA0)
        {
            --aA0;
        }

        public static int Positive(int aA0)
        {
            return +aA0;
        }

        public static int Negative(int aA0)
        {
            return -aA0;
        }

        public static bool LogicalNot(bool aA0)
        {
            return !aA0;
        }

        public static uint BitwiseNot(uint aA0)
        {
            return ~aA0;
        }
    }
}
