using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DllToXml.DataSet
{
    public class Constructor
    {
        //------------------------------------------------------------------------------
        public static Constructor Create(ConstructorInfo aNative)
        {
            var Constructor = new Constructor();

            Constructor.Name = aNative.Name;
            Constructor._Instructions = IlReader.ReadInstructions(aNative);

            return Constructor;
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
