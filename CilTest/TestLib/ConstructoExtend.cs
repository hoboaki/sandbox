using System;
namespace TestLib
{
	/// <summary>
	/// 継承を使ったコンストラクタのテスト。
	/// </summary>
	public static class ConstructorExtend
	{
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
        /// オーバーロードを持つコンストラクタ。
        /// </summary>
        public class HasOverload
        {
            public HasOverload(int aVal)
            {
                System.Console.WriteLine(aVal);
            }

            public HasOverload(bool aVal)
            {
                System.Console.WriteLine(aVal);
            }
        }

		/// <summary>
		/// 自身は宣言無し＆空コンストラクタを継承。
		/// </summary>
		public class NoDeclExtendEmpty : Empty
		{
		}

        /// <summary>
        /// オーバーロード持ちを継承。
        /// </summary>
        public class ExtendHasOverload : HasOverload
		{
            public ExtendHasOverload() : base(0)
			{
			}
		}
	}
}
