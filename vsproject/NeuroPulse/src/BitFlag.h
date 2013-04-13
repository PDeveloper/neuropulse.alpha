#pragma once
namespace np
{
	class BitFlag
	{
	public:

		static const BitFlag ALL;

		BitFlag& setBits( unsigned long int bits)
		{
			_bits = bits;

			return *this;
		}

		unsigned long int getBits() const
		{
			return _bits;
		}

		BitFlag& add( BitFlag& flag)
		{
			_bits = flag.getBits() | _bits;

			return *this;
		}

		BitFlag& sub( BitFlag& flag)
		{
			_bits = ~flag.getBits() | _bits;

			return *this;
		}

		bool contains( BitFlag& flag) const
		{
			return ( flag.getBits() & _bits) == flag.getBits();
		}

		BitFlag(void)
		{
			_bits = 0;
		}

		BitFlag( unsigned long int bits)
		{
			_bits = bits;
		}

		~BitFlag(void)
		{
		}

		bool operator == ( const BitFlag& other) const
		{
			return _bits == other._bits;
		}

		bool operator < ( const BitFlag& other) const
		{
			return ( _bits & other._bits) == _bits;
		}

		bool operator > ( const BitFlag& other) const
		{
			return ( other._bits & _bits) == other._bits;
		}

		BitFlag& operator = ( const BitFlag& other)
		{
			_bits = other._bits;

			return *this;
		}

		BitFlag& operator += (BitFlag& other)
		{
			_bits = other._bits | _bits;

			return *this;
		}

		BitFlag operator + (BitFlag& other)
		{
			return BitFlag( other._bits | _bits);
		}

		BitFlag operator + ( unsigned long int other)
		{
			return BitFlag( other | _bits);
		}

		BitFlag& operator -= (BitFlag& other)
		{
			_bits = ~other._bits | _bits;

			return *this;
		}

		BitFlag operator - (BitFlag& other)
		{
			return BitFlag( ~other._bits | _bits);
		}

		BitFlag operator - ( unsigned long int other)
		{
			return BitFlag( ~other | _bits);
		}
	private:
		unsigned long int _bits;
	};
}

