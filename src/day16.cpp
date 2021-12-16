#include <stdio.h>

class AbstractCharStream
{
public:
	virtual char get() = 0;
};

class StringStream : public AbstractCharStream
{
	const char *_s;
public:
	StringStream(const char *s) : _s(s) {}
	char get() { char ch = *_s++; /*printf("'%c'", ch);*/ return ch; }
};

class StdInFileStream : public AbstractCharStream
{
public:
	char get() { return fgetc(stdin); }
};

class BitStream
{
	AbstractCharStream *_charStream;
	unsigned char _byte;
	int _b;
	int _pos;
public:
	BitStream(AbstractCharStream *charStream)
	{
		_charStream = charStream;
		_b = 0;
		_pos = 0;
	}
	int get()
	{
		_pos++;
		if (_b == 0)
		{
			char ch = _charStream->get();
			if ('0' <= ch && ch <= '9')
				_byte = ch - '0';
			else if ('A' <= ch && ch <= 'F')
				_byte = ch - 'A' + 10;
			_b = 4;
		}
		_b--;
		int r = (_byte >> _b) & 1;
		//printf("[%d]", r);
		return r;
	}
	long pos() { return _pos; }
};

class DataStream
{
	BitStream &_input;
public:
	DataStream(BitStream& input) : _input(input) {}
	int get(int bits)
	{
		int result = 0;
		for (int i = 0; i < bits; i++)
			result = (result << 1) | _input.get();
		return result;
	}
	int pos() { return _input.pos(); }
};

int sum_version_nrs;

long long parse(DataStream &data)
{
	int version = data.get(3);
	int type = data.get(3);
	sum_version_nrs += version;
	//printf(" (%d %d", version, type);
	printf(" (");
	long long result = 0;
	if (type == 4)
	{
		long long value = 0;
		for (;;)
		{
			int more = data.get(1);
			int v = data.get(4);
			//printf(" %d\n", v);
			value = (value << 4) | v;
			if (more == 0)
				break;
		}
		printf("%lld", value);
		result = value;
	}
	else
	{
		int mode = data.get(1);
		/*
		if (mode == 0)
		{
			int total_length = data.get(15);
			printf(" length = %d\n", total_length);
			int end = data.pos() + total_length;
			while (data.pos() < end)
				parse(data);
		}
		else
		{
			int subpackets = data.get(11);
			printf(" packets = %d\n", subpackets);
			for (int i = 0; i < subpackets; i++)
				parse(data);
		}*/
		int end;
		int subpackets;
		if (mode == 0)
		{
			int total_length = data.get(15);
			end = data.pos() + total_length;
		}
		else
			subpackets = data.get(11);
		if (type == 0)
		{
			printf(" sum");
			for (int i = 0; mode == 0 ? data.pos() < end : i < subpackets; i++)
				result += parse(data);
		}
		else if (type == 1)
		{
			printf(" product");
			result = 1;
			for (int i = 0; mode == 0 ? data.pos() < end : i < subpackets; i++)
				result *= parse(data);
		}
		else if (type == 2)
		{
			printf(" min");
			for (int i = 0; mode == 0 ? data.pos() < end : i < subpackets; i++)
			{
				long long value = parse(data);
				if (i == 0 || value < result)
					result = value;
			}
		}
		else if (type == 3)
		{
			printf(" max");
			for (int i = 0; mode == 0 ? data.pos() < end : i < subpackets; i++)
			{
				long long value = parse(data);
				if (i == 0 || value > result)
					result = value;
			}
		}
		else if (type == 5)
		{
			printf(" gt");
			int a1 = parse(data);
			int a2 = parse(data);
			result = a1 > a2 ? 1 : 0;
		}
		else if (type == 6)
		{
			printf(" lt");
			int a1 = parse(data);
			int a2 = parse(data);
			result = a1 < a2 ? 1 : 0;
		}
		else if (type == 7)
		{
			printf(" eq");
			int a1 = parse(data);
			int a2 = parse(data);
			result = a1 == a2 ? 1 : 0;
		}
	}
	printf("):%lld", result);
	return result;
}

void parseString(const char *inp)
{
	sum_version_nrs = 0;
	printf("Process %s:", inp);
	StringStream ss(inp);
	BitStream bitStream(&ss);
	DataStream data(bitStream);
	int result = parse(data);
	printf("\nVersions %d %d\n", sum_version_nrs, result);
}

void parseFile()
{
	sum_version_nrs = 0;
	StdInFileStream ss;
	BitStream bitStream(&ss);
	DataStream data(bitStream);
	long long result = parse(data);
	printf("\nVersions %d %lld\n", sum_version_nrs, result);
}

int main()
{
	/*
	parseString("D2FE28");
	parseString("38006F45291200");
	parseString("8A004A801A8002F478");
	parseString("620080001611562C8802118E34");
	parseString("C0015000016115A2E0802F182340");
	parseString("A0016C880162017C3686B18A3D4780");
	parseFile();
	*/
	parseString("C200B40A82");
	parseString("04005AC33890");
	parseString("880086C3E88112");
	parseString("CE00C43D881120");
	parseString("D8005AC2A8F0");
	parseString("F600BC2D8F");
	parseString("9C005AC2F8F0");
	parseString("9C0141080250320F1802104A08");
	parseFile();
	
}
		
		