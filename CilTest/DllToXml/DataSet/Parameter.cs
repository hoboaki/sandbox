using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DllToXml.DataSet
{
    public class Parameter
    {
        public static Parameter Create(ParameterInfo aNative)
        {
            var param = new Parameter();

            param.FullName = aNative.ParameterType.FullName;

            return param;
        }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("full_name")]
        public string FullName { get; set; }
    }
}
