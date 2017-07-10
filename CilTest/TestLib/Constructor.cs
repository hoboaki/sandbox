using System;
namespace TestLib
{
    /// <summary>
    /// コンストラクタのテスト。
    /// </summary>
    public static class Constructor
    {
        /// <summary>
        /// 宣言なし。
        /// </summary>
        public class NoDecl
        {
        }

        /// <summary>
        /// 空っぽのコンストラクタ。
        /// </summary>
        public class Empty
        {
            public Empty()
            {
            }
        }

        /// <summary>
        /// 内容のあるコンストラクタ。
        /// </summary>
        public class Simple
        {
            public Simple()
            {
                System.Console.WriteLine("Simple Constructor");
            }
        }

        /// <summary>
        /// 自身は宣言無し＆宣言無しクラスの継承。
        /// </summary>
        public class NoDeclExtendNoDecl : NoDecl
        {
        }

		/// <summary>
		/// 自身は宣言無し＆空コンストラクタを継承。
		/// </summary>
		public class NoDeclExtendEmpty : Empty
		{
		}

        public class Extend : Empty
        {
            public Extend()
            {
                
            }
        }
    }
}
