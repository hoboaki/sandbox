using System;
using System.Reflection;

namespace ReadDll
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            var path = args[0];
            var asm = Assembly.LoadFrom(path);
            var reader = new IlReader();
            foreach(var mod in asm.Modules)
			{
				foreach (var type in mod.GetTypes())
				{
                    foreach (var method in type.GetMethods(BindingFlags.DeclaredOnly | BindingFlags.Static | BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic))
					{
						Console.WriteLine("-----------------");
                        Console.WriteLine("{0}:", method.Name);
                        if (method.DeclaringType.FullName == "System.Object")
                        {
                            continue;
                        }
						var instructions = reader.ReadInstructions(method);
						foreach (var inst in instructions)
						{
							Console.WriteLine("{0} {1}", inst.Name, inst.Operand);
						}
					}
                    
                }
            }
        }
    }
}
