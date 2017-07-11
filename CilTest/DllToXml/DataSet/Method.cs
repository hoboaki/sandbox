using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DllToXml.DataSet
{
    public class Method
    {
        //------------------------------------------------------------------------------
        public static Method Create(MethodInfo aNative)
        {
            var method = new Method();

            method.Name = aNative.Name;
            method._Instructions = IlReader.ReadInstructions(aNative);

            return method;
        }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("name")]
        public string Name { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlArray("instructions")]
        [System.Xml.Serialization.XmlArrayItem("instruction")]
        public List<Instruction> Instructions { get { return _Instructions; } }
        List<Instruction> _Instructions = new List<Instruction>();

    }
}
