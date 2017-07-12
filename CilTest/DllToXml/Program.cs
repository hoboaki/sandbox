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

            {
                var dll = DataSet.Assembly.Create(asm);
                
                var serializer = new XmlSerializer(typeof(DataSet.Assembly));
                using(var writer = new StringWriter())
                {
                    serializer.Serialize(writer, dll);
                    Console.WriteLine(writer.ToString());
                }
            }
        }
    }
}
