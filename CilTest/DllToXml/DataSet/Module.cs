using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DllToXml.DataSet
{
    public class Module
    {
        //------------------------------------------------------------------------------
        public static Module Create(System.Reflection.Module aNative)
        {
            var mod = new Module();

            mod.Name = aNative.Name;
               
            foreach (var type in aNative.GetTypes())
            {
                mod.Types.Add(Type.Create(type));
            }

            return mod;
        }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("name")]
        public string Name { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlArray("types")]
        [System.Xml.Serialization.XmlArrayItem("type")]
        public List<Type> Types { get { return _Types; } }
        List<Type> _Types = new List<Type>();
    }
}
