using System;
using System.Threading;
using System.Threading.Tasks;

namespace TestLib
{
    /// <summary>
    /// async await。
    /// </summary>
    public static class AsyncAwait
    {
        public static async Task PrintAbc()
        {
            await Print("A", 10);
            await Print("B", 1);
            await Print("C", 5);
        }

        static async Task Print(string aString, int aDelayMsec)
        {
            await Task.Delay(aDelayMsec);
            Console.WriteLine(aString);
        }

    }
}
