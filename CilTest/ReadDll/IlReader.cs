using System;
using System.Collections.Generic;
using System.Reflection;
using System.Reflection.Emit;

namespace ReadDll
{
	public class IlReader
	{
        private ByteArrayStream stream;
		private OpCode[] singleByteOpCode;
		private OpCode[] doubleByteOpCode;
		private byte[] instrunctions;
		private IList<LocalVariableInfo> locals;
		private ParameterInfo[] parameters;
		private Type[] typeArgs = null;
		private Type[] methodArgs = null;
		private MethodBase currentMethod = null;
		private List<IlInstruction> ilInstructions = null;

		public IlReader()
		{
			CreateOpCodes();
		}

		private void CreateOpCodes()
		{
			singleByteOpCode = new OpCode[225];
			doubleByteOpCode = new OpCode[31];

			FieldInfo[] fields = GetOpCodeFields();

			for (int i = 0; i < fields.Length; i++)
			{
				OpCode code = (OpCode)fields[i].GetValue(null);

				if (code.OpCodeType == OpCodeType.Nternal)
					continue;

				if (code.Size == 1)
					singleByteOpCode[code.Value] = code;
				else
					doubleByteOpCode[code.Value & 0xff] = code;
			}
		}

		public List<IlInstruction> ReadInstructions(MethodBase method)
		{
			ilInstructions = new List<IlInstruction>();
			this.currentMethod = method;

			locals = method.GetMethodBody().LocalVariables;
			instrunctions = method.GetMethodBody().GetILAsByteArray();

            stream = new ByteArrayStream(instrunctions);

            if (!(method is ConstructorInfo))
            {
                methodArgs = method.GetGenericArguments();
            }

            if (method.DeclaringType != null)
            {
                typeArgs = method.DeclaringType.GetGenericArguments();
            }

			IlInstruction instruction = null;

			while (stream.Position < stream.Length)
			{
				instruction = new IlInstruction();

				OpCode code = ReadOpCode();
				instruction.Operand = ReadOperand(code, method.Module);
				instruction.Name = code.Name;

				ilInstructions.Add(instruction);
			}

			return ilInstructions;
		}

		private object ReadOperand(OpCode code, Module module)
		{
			object operand = null;

			switch (code.OperandType)
			{
				case OperandType.InlineNone:
					break;
				case OperandType.InlineSwitch:
					int length = stream.ReadInt32();
					int[] branches = new int[length];
					int[] offsets = new int[length];
					for (int i = 0; i < length; i++)
						offsets[i] = stream.ReadInt32();
					for (int i = 0; i < length; i++)
						branches[i] = (int)stream.Position + offsets[i];
					break;
				case OperandType.ShortInlineBrTarget:
					operand = (stream.ReadOneByte() + stream.Position);
					break;
				case OperandType.InlineBrTarget:
					operand = (stream.ReadInt32() + stream.Position);
					break;
				case OperandType.ShortInlineI:
					if (code == OpCodes.Ldc_I4_S)
						operand = (sbyte)stream.ReadOneByte();
					else
						operand = stream.ReadOneByte();
					break;
				case OperandType.InlineI:
					operand = stream.ReadInt32();
					break;
				case OperandType.ShortInlineR:
					operand = stream.ReadFloat();
					break;
				case OperandType.InlineR:
					operand = stream.ReadDouble();
					break;
				case OperandType.InlineI8:
					operand = stream.ReadInt64();
					break;
				case OperandType.InlineSig:
					operand = module.ResolveSignature(stream.ReadInt32());
					break;
				case OperandType.InlineString:
					operand = module.ResolveString(stream.ReadInt32());
                    break;
				case OperandType.InlineTok:
				case OperandType.InlineType:
				case OperandType.InlineMethod:
				case OperandType.InlineField:
					operand = module.ResolveMember(stream.ReadInt32()
						, typeArgs, methodArgs);
					break;
				case OperandType.ShortInlineVar:
					operand = GetVariable(code, stream.ReadOneByte());
					break;
				case OperandType.InlineVar:
					operand = GetVariable(code, stream.ReadUint16());
					break;
				default:
					throw new NotSupportedException();
			}

			return operand;
		}

		private OpCode ReadOpCode()
		{
			byte instruction = stream.ReadOneByte();
			if (instruction != 254)
				return singleByteOpCode[instruction];
			else
				return doubleByteOpCode[stream.ReadOneByte()];
		}

		private object GetVariable(OpCode code, int index)
		{
			if (code.Name.Contains("loc"))
				return locals[index];

			if (!currentMethod.IsStatic)
				index--;

			return parameters[index];
		}

		private FieldInfo[] GetOpCodeFields()
		{
			return typeof(OpCodes).GetFields(BindingFlags.Public
				| BindingFlags.Static);
		}
	}
}
