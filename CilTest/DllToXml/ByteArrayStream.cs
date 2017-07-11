using System;
namespace DllToXml
{
    public class ByteArrayStream
    {
        public ByteArrayStream(byte[] aArray)
        {
            _Bytes = aArray;
        }

        public int Position { get { return _Position; } }
        public int Length { get { return _Bytes.Length; } }

        public byte ReadOneByte()
        {
            var result = _Bytes[_Position];
            ++_Position;
            return result;
        }

        public int ReadInt32()
        {
            var result = BitConverter.ToInt32(_Bytes, _Position);
            _Position += 4;
            return result;
        }

        public long ReadInt64()
        {
            var result = BitConverter.ToInt64(_Bytes, _Position);
            _Position += 8;
            return result;
        }

        public ushort ReadUint16()
        {
            var result = BitConverter.ToUInt16(_Bytes, _Position);
            _Position += 2;
            return result;
        }

        public float ReadFloat()
        {
            var result = BitConverter.ToSingle(_Bytes, _Position);
            _Position += 4;
            return result;
        }

        public double ReadDouble()
        {
            var result = BitConverter.ToDouble(_Bytes, _Position);
            _Position += 8;
            return result;
        }



        byte[] _Bytes;
        int _Position = 0;
    }
}
