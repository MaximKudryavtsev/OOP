#pragma once
#include <ostream>
#include <istream>
/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	const CRational operator-() const;
	const CRational operator+() const;

	CRational& operator+=(const CRational &rightValue);
	CRational& operator-=(const CRational &rightValue);
	CRational& operator*=(const CRational &rightValue);
	CRational& operator/=(const CRational &rightValue);

private:
	int m_numerator;
	int m_denominator;

	// Нормализует рациональное число
	void Normalize();
};

CRational const operator+(const CRational &leftValue, const CRational &rightValue);
CRational const operator-(const CRational &leftValue, const CRational &rightValue);
CRational const operator*(const CRational &leftValue, const CRational &rightValue);
CRational const operator/(const CRational &leftValue, const CRational &rightValue);

bool const operator==(const CRational &leftValue, const CRational &rightValue);
bool const operator!=(const CRational &leftValue, const CRational &rightValue);
bool const operator<(const CRational &leftValue, const CRational &rightValue);
bool const operator<=(const CRational &leftValue, const CRational &rightValue);
bool const operator>(const CRational &leftValue, const CRational &rightValue);
bool const operator>=(const CRational &leftValue, const CRational &rightValue);

std::ostream &operator<<(std::ostream &output, const CRational &rational);
std::istream &operator>>(std::istream &input, CRational &rational);

// Вычисляет наибольший общий делитель (greatest common denominator) чисел a и b
unsigned GCD(unsigned a, unsigned b);

