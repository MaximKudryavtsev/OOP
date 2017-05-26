#pragma once
#include <boost/noncopyable.hpp>

using namespace std;

class CCar;

class CCarController : boost::noncopyable
{
public:
    CCarController(CCar &car, istream &input, ostream &output);
    bool HandleCommand();
    // Избавляемся от предупреждения компилятора о том, что он не сможет сгенерировать оператор присваивания
private:
    bool EngineOn(istream &args);
    bool EngineOff(istream &args);
    bool Info(istream &args);
    bool SetGear(istream &args);
    bool SetSpeed(istream &args);
private:
    typedef map<string, function<bool(istream & args)>> ActionMap;
    CCar & m_car;
    istream & m_input;
    ostream & m_output;
    const ActionMap m_actionMap;
};
