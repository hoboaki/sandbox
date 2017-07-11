using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace DllToXml
{
    class Program
    {
        static void Main(string[] aArgs)
        {
            var path = aArgs[0];
            var asm = Assembly.LoadFrom(path);
            var reader = new IlReader();

            {
                var dll = DataSet.Assembly.Create(asm);
                
                var serializer = new XmlSerializer(typeof(DataSet.Assembly));
                using(var writer = new StringWriter())
                {
                    serializer.Serialize(writer, dll);
                    Console.WriteLine(writer.ToString());
                }
            }

            foreach (var mod in asm.Modules)
            {
                Console.WriteLine("Module: {0}", mod.FullyQualifiedName);
                foreach (var type in mod.GetTypes())
                {
                    Console.WriteLine("  Type: {0}", type.FullName);
                    foreach (var ctor in type.GetConstructors())
                    {
                        string args = "";
                        foreach (var arg in ctor.GetParameters())
                        {
                            if (args != "")
                            {
                                args += ",";
                            }
                            args += arg.ParameterType.FullName;
                        }

                        Console.WriteLine("    Constructor: ({0})", args);
                        {
                            Console.WriteLine("      Instructions:");
                            var instructions = reader.ReadInstructions(ctor);
                            foreach (var inst in instructions)
                            {
                                Console.WriteLine("        {0} {1}", inst.Name, inst.Operand);
                            }
                        }
                    }
                    foreach (var method in type.GetMethods(BindingFlags.DeclaredOnly | BindingFlags.Static | BindingFlags.Instance | BindingFlags.CreateInstance | BindingFlags.Public | BindingFlags.NonPublic))
                    {
                        Console.WriteLine("    Method: {0}", method.Name);
                        {
                            Console.WriteLine("      Instructions:");
                            var instructions = reader.ReadInstructions(method);
                            foreach (var inst in instructions)
                            {
                                Console.WriteLine("        {0} {1}", inst.Name, inst.Operand);
                            }
                        }
                    }

                }
            }
        }
    }
}
