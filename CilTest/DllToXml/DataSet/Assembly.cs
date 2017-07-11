using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DllToXml.DataSet
{
    [System.Xml.Serialization.XmlRoot("assembly")]
    public class Assembly
    {
        //------------------------------------------------------------------------------
        public static Assembly Create(System.Reflection.Assembly aNative)
        {
            var asm = new Assembly();

            asm.Name = aNative.GetName().Name;

            foreach (var mod in aNative.Modules)
            {
                asm.Modules.Add(Module.Create(mod));
            }

            return asm;
        }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("name")]
        public string Name { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlArray("modules")]
        [System.Xml.Serialization.XmlArrayItem("module")]
        public List<Module> Modules { get { return _Modules; } }
        List<Module> _Modules = new List<Module>();
    }
}
