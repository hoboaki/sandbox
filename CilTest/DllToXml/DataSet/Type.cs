using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DllToXml.DataSet
{
    public class Type
    {
        //------------------------------------------------------------------------------
        public static Type Create(System.Type aNative)
        {
            var type = new Type();

            type.Name = aNative.Name;
            type.FullName = aNative.FullName;
            type.Namespace = aNative.Namespace;

            return type;
        }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("name")]
        public string Name { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("full_name")]
        public string FullName { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("namespace")]
        public string Namespace { get; set; }


    }
}
