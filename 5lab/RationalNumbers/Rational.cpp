#include "stdafx.h"
#include "Rational.h"

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("denominator can't equal to zero");
	}

	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	if (m_denominator == 0)
	{
		throw std::logic_error("denominator can't be equal to zero");
	}

	return static_cast<double>(m_numerator) / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integer = m_numerator / m_denominator;
	int numerator = m_numerator - m_denominator * integer;
	return{ integer, CRational(numerator, m_denominator) };
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

CRational const CRational::operator +() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const CRational::operator -() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator +=(const CRational &rightValue)
{
	*this = *this + rightValue;
	return *this;
}

CRational& CRational::operator -=(const CRational &rightValue)
{
	*this = *this - rightValue;
	return *this;
}

CRational& CRational::operator *=(const CRational &rightValue)
{
	*this = *this * rightValue;
	return *this;
}

CRational& CRational::operator /=(const CRational &rightValue)
{
	*this = *this / rightValue;
	return *this;
}

CRational const operator +(const CRational &leftValue, const CRational &rightValue)
{
	return CRational(
		leftValue.GetNumerator() * rightValue.GetDenominator() + rightValue.GetNumerator() * leftValue.GetDenominator(),
		leftValue.GetDenominator() * rightValue.GetDenominator()
	);
}

CRational const operator -(const CRational &leftValue, const CRational &rightValue)
{
	return leftValue + -rightValue;
}

CRational const operator *(const CRational &leftValue, const CRational &rightValue)
{
	return CRational(
		leftValue.GetNumerator() * rightValue.GetNumerator(),
		leftValue.GetDenominator() * rightValue.GetDenominator()
	);
}

CRational const operator /(const CRational &leftValue, const CRational &rightValue)
{
	return CRational(
		leftValue.GetNumerator() * rightValue.GetDenominator(),
		leftValue.GetDenominator() * rightValue.GetNumerator()
	);
}

bool operator ==(const CRational &leftValue, const CRational &rightValue)
{
	return (leftValue.GetNumerator() == rightValue.GetNumerator()) &&
		(leftValue.GetDenominator() == rightValue.GetDenominator());
}

bool operator !=(const CRational &leftValue, const CRational &rightValue)
{
	return !(leftValue == rightValue);
}

bool operator >(const CRational &leftValue, const CRational &rightValue)
{
	return (leftValue.ToDouble() > rightValue.ToDouble());
}

bool operator <= (const CRational &leftValue, const CRational &rightValue)
{
	return !(leftValue > rightValue);
}

bool operator <(const CRational &leftValue, const CRational &rightValue)
{
	return (leftValue.ToDouble() < rightValue.ToDouble());
}

bool operator >=(const CRational &leftValue, const CRational &rightValue)
{
	return !(leftValue < rightValue);
}

std::ostream& operator <<(std::ostream &strm, const CRational &number)
{
	strm << number.GetNumerator() << '/' << number.GetDenominator();
	return strm;
}

std::istream& operator >> (std::istream &strm, CRational &number)
{
	int numerator;
	int denominator;

	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		number = CRational(numerator, denominator);
	}
	else
	{
		strm.setstate(std::ios_base::failbit | strm.rdstate());
	}

	return strm;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}