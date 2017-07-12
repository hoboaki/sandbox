using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestLib
{
    /// <summary>
    /// ２項演算式。
    /// </summary>
    public static class BinaryOpExpression
    {
        public static int AdditiveAdd(int aA0, int aA1)
        {
            return aA0 + aA1;
        }

        public static int AdditiveSub(int aA0, int aA1)
        {
            return aA0 - aA1;
        }

        public static uint BitwiseAnd(uint aA0, uint aA1)
        {
            return aA0 & aA1;
        }

        public static uint BitwiseOr(uint aA0, uint aA1)
        {
            return aA0 | aA1;
        }

        public static int BitwiseXor(int aA0, int aA1)
        {
            return aA0 ^ aA1;
        }

        public static bool EqualityEqual(int aA0, int aA1)
        {
            return aA0 == aA1;
        }

        public static bool EqualityNotEqual(int aA0, int aA1)
        {
            return aA0 != aA1;
        }

        public static TType ObjectAs<TType>(object aA0) where TType : class
        {
            return aA0 as TType;
        }

        public static bool ObjectIs<TType>(object aA0)
        {
            return aA0 is TType;
        }

        public static bool LogicalAnd(bool aA0, bool aA1)
        {
            return aA0 && aA1;
        }

        public static bool LogicalOr(bool aA0, bool aA1)
        {
            return aA0 || aA1;
        }

        public static int MultiplicativeDiv(int aA0, int aA1)
        {
            return aA0 / aA1;
        }

        public static int MultiplicativeMul(int aA0, int aA1)
        {
            return aA0 * aA1;
        }

        public static int MultiplicativeMod(int aA0, int aA1)
        {
            return aA0 % aA1;
        }

        public static bool RelationalGreater(int aA0, int aA1)
        {
            return aA0 > aA1;
        }

        public static bool RelationalGreaterEqual(int aA0, int aA1)
        {
            return aA0 >= aA1;
        }

        public static bool RelationalLess(int aA0, int aA1)
        {
            return aA0 < aA1;
        }

        public static bool RelationalLessEqual(int aA0, int aA1)
        {
            return aA0 <= aA1;
        }
        
        public static uint ShiftLeft(uint aA0, int aA1)
        {
            return aA0 << aA1;
        }

        public static uint ShiftRight(uint aA0, int aA1)
        {
            return aA0 >> aA1;
        }
    }
}
