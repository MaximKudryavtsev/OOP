#include "stdafx.h"
#include "Car.h"

using namespace std;
namespace
{
    static map<Gear, pair<int, int>> ranges = {
        { Gear::REVERSE, { 0, 20 } },
        { Gear::NEUTRAL, { 0, 150 } },
        { Gear::FIRST, { 0, 30 } },
        { Gear::SECOND, { 20, 50 } },
        { Gear::THIRD, { 30, 60 } },
        { Gear::FOURTH, { 40, 90 } },
        { Gear::FIFTH, { 50, 150 } }
    };

    bool IsInRange(int number, const pair<int, int> &range)
    {
        return (number >= range.first) && (number <= range.second);
    }

    bool IsSpeedInRangeForGear(Gear gear, int speed)
    {
        return (IsInRange(speed, ranges[gear]));
    }

    Gear ConvertIntToGear(int intGear)
    {
        Gear gear;
		gear = static_cast<Gear>(intGear);
        /*switch (intGear)
        {
        case -1:
            gear = Gear::REVERSE;
            break;
        case 0:
            gear = Gear::NEUTRAL;
            break;
        case 1:
            gear = Gear::FIRST;
            break;
        case 2:
            gear = Gear::SECOND;
            break;
        case 3:
            gear = Gear::THIRD;
            break;
        case 4:
            gear = Gear::FOURTH;
            break;
        case 5:
            gear = Gear::FIFTH;
            break;
        default:
            gear = Gear::NEUTRAL;
            break;
        }*/

        return gear;
    }
}

CCar::CCar()
{
    m_isTurnedOn = false;
    m_speed = 0;
    m_gear = Gear::NEUTRAL;
}

CCar::~CCar() = default;

bool CCar::IsTurnedOn() const
{
    return m_isTurnedOn;
}

bool CCar::TurnOnEngine()
{
    if (!m_isTurnedOn)
    {
        m_isTurnedOn = true;
        return true;
    }

    return false;
}

bool CCar::TurnOffEngine()
{
    if ((m_isTurnedOn) && (m_gear == Gear::NEUTRAL) && (m_speed == 0))
    {
        m_isTurnedOn = false;
        return true;
    }

    return false;
}

bool CCar::SetGear(int gear)
{
    if ((gear < -1) || (gear > 5))
    {
        return false;
    }

    bool switched = false;

    if (gear == 0)
    {
        m_gear = ConvertIntToGear(gear);
        switched = true;
    }
    else if ((m_isTurnedOn) && (IsSpeedInRangeForGear(ConvertIntToGear(gear), abs(m_speed))))
    {
        if (((gear > 0) && (m_speed >= 0)) || ((gear < 0) && (m_speed == 0)))
        {
            m_gear = ConvertIntToGear(gear);
            switched = true;
        }
    }

    return switched;
}

bool CCar::SetSpeed(int speed)
{
    if (!m_isTurnedOn)
    {
        return false;
    }

    bool changed = false;

    if ((m_gear == Gear::NEUTRAL) && (speed <= m_speed) && (speed >= 0))
    {
        m_speed = speed;
        changed = true;
    }
    else if ((m_gear != Gear::NEUTRAL) && (IsSpeedInRangeForGear(m_gear, speed)))
    {
        m_speed = (m_gear == Gear::REVERSE) ? -speed : speed;
        changed = true;
    }

    return changed;
}

int CCar::GetCurrentSpeed() const
{
    return abs(m_speed);
}

Direction CCar::GetCurrentDirection() const
{
    Direction direction;

    if (m_speed < 0)
    {
        direction = Direction::BACKWARD;
    }
    else if (m_speed > 0)
    {
        direction = Direction::FORWARD;
    }
    else
    {
        direction = Direction::NONE;
    }

    return direction;
}

int CCar::GetCurrentGear() const
{
    return static_cast<int>(m_gear);
}

bool operator==(const CCar &left, const CCar &right)
{
	return (left.m_isTurnedOn == right.m_isTurnedOn) &&
		(left.m_speed == right.m_speed) &&
		(left.m_gear == right.m_gear);
}
