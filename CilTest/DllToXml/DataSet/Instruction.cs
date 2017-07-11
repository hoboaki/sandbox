using System;
namespace DllToXml.DataSet
{
    public class Instruction
    {
        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("offset")]
        public int Offset { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("name")]
        public string Name { get; set; }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlAttribute("operand")]
        public string OperandText { get { return Operand == null ? null : Operand.ToString(); } set { } }

        //------------------------------------------------------------------------------
        [System.Xml.Serialization.XmlIgnore]
        public object Operand { get; set; }
    }
}
