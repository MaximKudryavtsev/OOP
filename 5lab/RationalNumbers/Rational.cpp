#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
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
	return static_cast<double>(m_numerator) / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integer = m_numerator / m_denominator;
	int numerator = m_numerator % m_denominator;
	std::pair<int, CRational> pair = std::make_pair(integer, CRational(numerator, m_denominator));
	return pair;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
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

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational CRational::operator+() const
{
	return *this;
}

CRational const operator+(const CRational &leftValue, const CRational &rightValue)
{
	int numerator;
	int denominator;
	if (leftValue.GetDenominator() == rightValue.GetDenominator())
	{
		numerator = leftValue.GetNumerator() + rightValue.GetNumerator();
		denominator = leftValue.GetDenominator();
	}
	else
	{
		numerator = leftValue.GetNumerator() * rightValue.GetDenominator() +
			rightValue.GetNumerator() * leftValue.GetDenominator();
		denominator = leftValue.GetDenominator() * rightValue.GetDenominator();
	}

	return CRational(numerator, denominator);
}

CRational const operator-(const CRational &leftValue, const CRational &rightValue)
{
	return leftValue + (-rightValue);
}

CRational &CRational::operator+=(const CRational &rightValue)
{
	*this = *this + rightValue;
	Normalize();
	return *this;
}

CRational &CRational::operator-=(const CRational &rightValue)
{
	*this = *this - rightValue;
	Normalize();
	return *this;
}

CRational const operator*(const CRational &leftValue, const CRational &rightValue)
{
	int numerator = leftValue.GetNumerator() * rightValue.GetNumerator();
	int denominator = leftValue.GetDenominator() * rightValue.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator/(const CRational &leftValue, const CRational &rightValue)
{
	CRational oppositeSecond(rightValue.GetDenominator(), rightValue.GetNumerator());
	return leftValue * oppositeSecond;
}

CRational &CRational::operator*=(const CRational &rightValue)
{
	*this = *this * rightValue;
	return *this;
}

CRational &CRational::operator/=(const CRational &rightValue)
{
	CRational oppositeSecond(rightValue.GetDenominator(), rightValue.GetNumerator());
	*this = *this * oppositeSecond;
	return *this;
}

bool const operator==(const CRational &leftValue, const CRational &rightValue)
{
	return (leftValue.GetNumerator() == rightValue.GetNumerator() &&
		(leftValue.GetDenominator() == rightValue.GetDenominator()));
}

bool const operator!=(const CRational &leftValue, const CRational &rightValue)
{
	return !(leftValue == rightValue);
}

bool const operator<(const CRational &leftValue, const CRational &rightValue)
{
	if (leftValue.GetDenominator() == rightValue.GetDenominator())
	{
		return leftValue.GetNumerator() < rightValue.GetNumerator();
	}
	else
	{
		return leftValue.GetNumerator() * rightValue.GetDenominator() < rightValue.GetNumerator() * leftValue.GetDenominator();
	}
}

bool const operator<=(const CRational &leftValue, const CRational &rightValue)
{
	return !(leftValue > rightValue);
}

bool const operator>(const CRational &leftValue, const CRational &rightValue)
{
	if (leftValue.GetDenominator() == rightValue.GetDenominator())
	{
		return leftValue.GetNumerator() > rightValue.GetNumerator();
	}
	else
	{
		return leftValue.GetNumerator() * rightValue.GetDenominator() > rightValue.GetNumerator() * leftValue.GetDenominator();
	}
}

bool const operator>=(const CRational &leftValue, const CRational &rightValue)
{
	return !(leftValue < rightValue);
}

std::ostream &operator<<(std::ostream &output, const CRational &rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();
	return output;
}

std::istream &operator >> (std::istream &input, CRational &rational)
{
	int numerator;
	int denominator;
	if (
		(input >> numerator) &&
		(input.get() == '/') &&
		(input >> denominator)
		)
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit | input.rdstate());
	}
	return input;
}
