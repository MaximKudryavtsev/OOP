#include "stdafx.h"
#include "Body.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Compound.h"
#include "AppController.h"

CAppController::CAppController(std::vector<std::shared_ptr<CBody>> &bodies, std::istream &input, std::ostream &output)
    : m_bodies(bodies)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
        { "Sphere", std::bind(&CAppController::CreateSphere, this, std::placeholders::_1) },
        { "Parallelepiped", std::bind(&CAppController::CreateParallelepiped, this, std::placeholders::_1) },
        { "Cone", std::bind(&CAppController::CreateCone, this, std::placeholders::_1) },
        { "Cylinder", std::bind(&CAppController::CreateCylinder, this, std::placeholders::_1) },
        { "Compound", std::bind(&CAppController::CreateCompound, this, std::placeholders::_1) }
    })
{
}

bool CAppController::Info()
{
	m_output << "available commands:\n"
		<< "1) Sphere <density> <radius>\n"
		<< "2) Parallelepiped <width> <height> <depth> <density>\n"
		<< "3) Cone <density> <radius> <height>\n"
		<< "4) Cylinder <density> <radius> <height>\n"
		<< "5) Compound - Begining of the input elements of compound body\n"
		<< "Any elements\n"
		<< "... - to finish entering elements of compound body or exit\n";
	return true;
}

bool CAppController::HandleCommand()
{
    std::string commandLine;

    if ((!std::getline(m_input, commandLine)) || (commandLine.empty()))
    {
        return true;
    }
    else if (commandLine == "...")
    {
        return false;
    }

    std::istringstream strm(commandLine);

    std::string action;
    strm >> action;

    auto it = m_actionMap.find(action);

    if (it != m_actionMap.end())
    {
        try
        {
            it->second(strm);
        }
        catch (const std::invalid_argument &error)
        {
            m_output << error.what() << '\n';
        }
    }
    else
    {
        m_output << "Unknown command!\n";
    }

    return true;
}

bool CAppController::CreateSphere(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 2)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CSphere>(parametrs.at(0), parametrs.at(1));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Sphere created!\n";
    }
    else
    {
        m_output << "Can't create this sphere...\n"
                 << "Usage: Sphere <density> <radius>\n";
    }
    
    return created;
}

bool CAppController::CreateParallelepiped(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 4)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CParallelepiped>(parametrs.at(0), parametrs.at(1), parametrs.at(2), parametrs.at(3));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Parallelepiped created!\n";
    }
    else
    {
        m_output << "Can't create this parallelepiped...\n"
                 << "Usage: Parallelepiped <density> <width> <height> <depth>\n";
    }

    return created;
}

bool CAppController::CreateCone(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 3)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CCone>(parametrs.at(0), parametrs.at(1), parametrs.at(2));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Cone created!\n";
    }
    else
    {
        m_output << "Can't create this cone\n"
                 << "Usage: Cone <density> <base radius> <height>\n";
    }

    return created;
}

bool CAppController::CreateCylinder(std::istream &args)
{
    bool created = false;

    double parametr;
    std::vector<double> parametrs;
    while (args >> parametr)
    {
        parametrs.push_back(parametr);
    }

    if (parametrs.size() == 3)
    {
        std::shared_ptr<CBody> ptr = std::make_shared<CCylinder>(parametrs.at(0), parametrs.at(1), parametrs.at(2));
        m_bodies.push_back(ptr);
        created = true;
        m_output << "Cylinder created!\n";
    }
    else
    {
        m_output << "Can't create this cylinder\n"
                 << "Usage: Cylinder <density> <base radius> <height>\n";
    }

    return created;
}

bool CAppController::CreateCompound(std::istream &args)
{
    std::vector<std::shared_ptr<CBody>> compoundBodyElements;
    CAppController compoundBodiesController(compoundBodyElements, m_input, m_output);
    std::shared_ptr<CCompound> compoundBody = std::make_shared<CCompound>();

    m_output << "Creating compound body (\"...\" for quit creating)\n";

    while ((!m_input.eof()) || (!m_input.fail()))
    {
        m_output << "> ";
        if (!compoundBodiesController.HandleCommand())
        {
            break;
        }
    }

    m_output << "Qutting create of compound body\n";

    if (!compoundBodyElements.empty())
    {
        for (auto &element : compoundBodyElements)
        {
            compoundBody->AddChildBody(element);
        }

        m_bodies.push_back(compoundBody);
        return true;
    }

    return false;
}

void CAppController::PrintInfoAboutAllBodies(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
    if (!bodies.empty())
    {
        for (const auto &body : bodies)
        {
            strm << body->ToString() << '\n';
        }
    }
}

void CAppController::PrintInfoAboutBodyWithMaxMass(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
    if (!bodies.empty())
    {
        auto hasBiggerMass = [] (const std::shared_ptr<CBody> &first, const std::shared_ptr<CBody> &second)
        {
            return (first->GetMass() < second->GetMass());
        };

        auto bodyWithMaxMass = *std::max_element(bodies.begin(), bodies.end(), hasBiggerMass);

        strm << "Body with max mass is " << bodyWithMaxMass->ToString() << '\n';
    }
}

void CAppController::PrintInfoAboutBodyWithMinWeightInWater(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
    if (!bodies.empty())
    {
        auto hasLessWeight = [this] (const std::shared_ptr<CBody> &first, const std::shared_ptr<CBody> &second)
        {
            return (GetBodyWeightInWater(*first) < GetBodyWeightInWater(*second));
        };

        auto bodyWithMinWeightInWater = *std::min_element(bodies.begin(), bodies.end(), hasLessWeight);

        strm << "Body with min weight in water is " << bodyWithMinWeightInWater->ToString() << '\n';
    }
}

double CAppController::GetBodyWeightInWater(const CBody &body) const
{
    const double gravityAcceleration = 9.8;
    const double waterDensity = 1000;

    return (body.GetDensity() - waterDensity) * gravityAcceleration * body.GetVolume();
}
