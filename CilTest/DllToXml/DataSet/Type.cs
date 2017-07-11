using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
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

            foreach(var ctor in aNative.GetConstructors())
            {
                type.Constructors.Add(Constructor.Create(ctor));
            }

            foreach (var method in aNative.GetMethods(BindingFlags.DeclaredOnly | BindingFlags.Static | BindingFlags.Instance | BindingFlags.CreateInstance | BindingFlags.Public | BindingFlags.NonPublic))
            {
                type.Methods.Add(Method.Create(method));
            }

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

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlArray("constructors")]
        [System.Xml.Serialization.XmlArrayItem("constructor")]
        public List<Constructor> Constructors { get { return _Constructors; } }
        List<Constructor> _Constructors = new List<Constructor>();

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlArray("methods")]
        [System.Xml.Serialization.XmlArrayItem("method")]
        public List<Method> Methods { get { return _Methods; } }
        List<Method> _Methods = new List<Method>();

    }
}
