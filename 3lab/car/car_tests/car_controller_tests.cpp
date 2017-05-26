#include "stdafx.h"
#include "../Car.h"
#include "../CarController.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// «ависимости CarController-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструировани€ самого CarController-а
struct CarControllerDependencies
{
    CCar car;
    stringstream input;
    stringstream output;
};

struct CarControllerFixture : CarControllerDependencies
{
    CCarController controller;

    CarControllerFixture()
        : controller(car, input, output) {}

    // ¬спомогательна€ функци€ дл€ проверки работы команды command
    // ќна принимает команду command и ожидаемый результат expectedOutput
    void VerifyCommandHandling(const std::string &command, const std::string &expectedOutput)
    {
        // ѕредварительно очищаем содержимое выходного потока
        input = stringstream();
        output = stringstream();
        BOOST_CHECK(input << command);
        controller.HandleCommand();
        BOOST_CHECK(input.eof());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }
};

BOOST_FIXTURE_TEST_SUITE(Car_Controller, CarControllerFixture)
    BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command_if_not_turned_on_yet)
    {
        VerifyCommandHandling("EngineOn", "Car engine was turned on\n");
    }

    BOOST_AUTO_TEST_CASE(can_turn_off_car_engine_which_is_on)
    {
        car.TurnOnEngine();
        VerifyCommandHandling("EngineOff", "Car engine was turned off\n");
    }

    BOOST_AUTO_TEST_CASE(can_print_car_info)
    {
        // провер€ем у машины с незаведЄнным двигателем
        car.TurnOffEngine();
        VerifyCommandHandling("Info", "Engine: off\nGear: 0\nSpeed: 0\nDirection: none\n");

        // провер€ем у машины с заведЄнным двигателем
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);
        VerifyCommandHandling(
            "Info", "Engine: on\nGear: 1\nSpeed: 20\nDirection: forward\n"
        );
    }

    BOOST_AUTO_TEST_CASE(can_print_alert_messages)
    {
        car.TurnOffEngine();
        VerifyCommandHandling(
            "SetSpeed 30", "Speed is out of range for current gear or car engine is turned off\n"
        );
    }

    BOOST_AUTO_TEST_CASE(can_show_info_that_operation_on_car_engine_is_already_done)
    {
        car.TurnOnEngine();
        VerifyCommandHandling(
            "EngineOn", "Car engine is already turned on\n"
        );

        car.TurnOffEngine();
        VerifyCommandHandling(
            "EngineOff", "Car engine is already turned off\n"
        );
    }
BOOST_AUTO_TEST_SUITE_END()
