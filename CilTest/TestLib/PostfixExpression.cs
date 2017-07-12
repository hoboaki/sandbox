using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestLib
{
    public static class PostfixExpression
    {
        public static void IncDecInc(int aA0)
        {
            aA0++;
        }

        public static void IncDecDec(int aA0)
        {
            aA0--;
        }

        public static void FunctionCallExpr()
        {
            FunctionCallExpr();
        }

        public static int IndexExpr(int aIndex)
        {
            int[] array = { 1, 10, 100 };
            return array[aIndex];
        }

        public static float ChildIdentExpr(Vec2field aA0)
        {
            return aA0.Y;
        }
    }
}
