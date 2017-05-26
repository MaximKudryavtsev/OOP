#include "stdafx.h"
#include "../Car.h"

struct CarFixture
{
    CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
    BOOST_AUTO_TEST_SUITE(when_constructed)
        BOOST_AUTO_TEST_CASE(engine_is_turned_off)
        {
            BOOST_CHECK(!car.IsTurnedOn());
        }

        BOOST_AUTO_TEST_CASE(gear_is_neutral)
        {
            BOOST_CHECK(car.GetCurrentGear() == 0);
        }

        BOOST_AUTO_TEST_CASE(speed_equals_to_zero)
        {
            BOOST_CHECK(car.GetCurrentSpeed() == 0);
        }

        BOOST_AUTO_TEST_CASE(does_not_have_any_direction)
        {
            BOOST_CHECK(car.GetCurrentDirection() == Direction::NONE);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(when_engine_is_turned_off)
        BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
        {
            auto clone(car);
            BOOST_CHECK(car.TurnOnEngine());
            BOOST_CHECK(car.IsTurnedOn());
            BOOST_CHECK(!(car == clone));
        }

        BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_off_again)
        {
            auto clone(car);
            BOOST_CHECK(!car.TurnOffEngine());
            BOOST_CHECK(!car.IsTurnedOn());
            BOOST_CHECK(car == clone);
        }

        BOOST_AUTO_TEST_CASE(gear_cannot_be_switched_on_any_possible_gear_besides_neutral)
        {
            for (int i = -1; i < 6; ++i)
            {
                if (i != 0)
                {
                    BOOST_CHECK(!car.SetGear(i));
                }
                else
                {
                    BOOST_CHECK(car.SetGear(i));
                }
            }
        }

        BOOST_AUTO_TEST_CASE(speed_cannot_be_changed)
        {
            auto clone(car);
            BOOST_CHECK(!car.SetSpeed(10));
            BOOST_CHECK(!car.SetSpeed(0));
            BOOST_CHECK(clone == car);
        }
    BOOST_AUTO_TEST_SUITE_END()

    struct when_turned_on_ : CarFixture
    {
        when_turned_on_()
        {
            car.TurnOnEngine();
        }
    };

    BOOST_FIXTURE_TEST_SUITE(when_engine_is_turned_on, when_turned_on_)
        BOOST_AUTO_TEST_CASE(cannot_turn_engine_on_again)
        {
            BOOST_CHECK(!car.TurnOnEngine());
            BOOST_CHECK(car.IsTurnedOn());
        }

        BOOST_AUTO_TEST_CASE(can_turn_engine_off_on_neutral_gear_and_zero_speed_only)
        {
            // пробуем выключить с первой передачей на скорости
            car.SetGear(1);
            car.SetSpeed(10);
            auto clone(car);
            BOOST_CHECK(!car.TurnOffEngine());
            BOOST_CHECK(car.IsTurnedOn());
            BOOST_CHECK(car == clone);

            // пробуем выключить с нейтральной передачей на скорости
            car.SetGear(0);
            BOOST_CHECK(!car.TurnOffEngine());
            BOOST_CHECK(car.IsTurnedOn());

            // выключаем машину на нейтральной передаче и на нулевой скорости
            car.SetGear(0);
            car.SetSpeed(0);
            BOOST_CHECK(car.TurnOffEngine());
            BOOST_CHECK(!car.IsTurnedOn());
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_FIXTURE_TEST_SUITE(SetGear_method, when_turned_on_)
        BOOST_AUTO_TEST_CASE(cannot_set_gear_that_does_not_exist)
        {
            auto clone(car);
            BOOST_CHECK(!car.SetGear(-2));
            BOOST_CHECK(!car.SetGear(6));
            BOOST_CHECK(car == clone);
        }

        BOOST_AUTO_TEST_CASE(can_set_first_or_reverse_gear_when_speed_is_zero)
        {
            auto clone(car);
            BOOST_CHECK(car.SetGear(-1));
            BOOST_CHECK(car.SetGear(1));
            BOOST_CHECK(!(car == clone));
        }

        BOOST_AUTO_TEST_CASE(cannot_set_gear_if_the_speed_is_too_low_for_this_gear)
        {
            car.SetGear(1);
            car.SetSpeed(10);
            auto clone(car);
            BOOST_CHECK(!car.SetGear(2));
            BOOST_CHECK(car == clone);
        }

        BOOST_AUTO_TEST_CASE(can_set_gear_if_speed_allows_to_do_that)
        {
            car.SetGear(1);
            car.SetSpeed(20);
            auto clone(car);
            BOOST_CHECK(car.SetGear(2));
            BOOST_CHECK(!(clone == car));
        }

        BOOST_AUTO_TEST_CASE(can_set_on_same_gear_anytime)
        {
            car.SetGear(1);
            auto clone(car);
            BOOST_CHECK(car.SetGear(1));
            BOOST_CHECK(car.GetCurrentGear() == 1);
            BOOST_CHECK(car == clone);
        }

        BOOST_AUTO_TEST_CASE(cannot_switch_on_first_gear_from_neutral_with_non_zero_speed_and_backward_direction)
        {
            car.SetGear(-1);
            car.SetSpeed(10);
            BOOST_CHECK(car.SetGear(0));
            auto clone(car);
            BOOST_CHECK(!car.SetGear(1));
            BOOST_CHECK(car.GetCurrentDirection() == Direction::BACKWARD);
            BOOST_CHECK(car == clone);
        }

        BOOST_AUTO_TEST_CASE(cannot_switch_on_reverse_gear_from_neutral_with_non_zero_speed_and_forward_direction)
        {
            car.SetGear(1);
            car.SetSpeed(10);
            BOOST_CHECK(car.SetGear(0));
            auto clone(car);
            BOOST_CHECK(!car.SetGear(-1));
            BOOST_CHECK(car.GetCurrentDirection() == Direction::FORWARD);
            BOOST_CHECK(car == clone);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_FIXTURE_TEST_SUITE(SetSpeed_method, when_turned_on_)
        BOOST_AUTO_TEST_CASE(cannot_accelerate_when_gear_is_neutral)
        {
            car.SetGear(1);
            car.SetSpeed(10);
            car.SetGear(0);
            auto carClone(car);
            BOOST_CHECK(!car.SetSpeed(20));
            BOOST_CHECK(car == carClone);
        }

        BOOST_AUTO_TEST_CASE(can_slow_down_when_gear_is_neutral)
        {
            car.SetGear(1);
            car.SetSpeed(10);
            car.SetGear(0);
            auto carClone(car);
            BOOST_CHECK(car.SetSpeed(5));
            BOOST_CHECK(!(car == carClone));
        }

        BOOST_AUTO_TEST_CASE(cannot_set_any_speed_if_gear_does_not_allow_to_do_that)
        {
            // задняя скорость
            {
                car.SetGear(-1);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(21));
                BOOST_CHECK(!car.SetSpeed(-1));

                BOOST_CHECK(car == clone);
            }

            // нейтральная скорость
            {
                car.SetGear(0);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(-1));
                BOOST_CHECK(!car.SetSpeed(151));

                BOOST_CHECK(car == clone);
            }

            // 1-я скорость
            {
                car.SetGear(1);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(31));
                BOOST_CHECK(!car.SetSpeed(-1));

                BOOST_CHECK(car == clone);
            }

            // 2-я скорость
            {
                car.SetSpeed(20);
                car.SetGear(2);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(51));
                BOOST_CHECK(!car.SetSpeed(19));

                BOOST_CHECK(car == clone);
            }

            // 3-я скорость
            {
                car.SetSpeed(50);
                car.SetGear(3);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(61));
                BOOST_CHECK(!car.SetSpeed(29));

                BOOST_CHECK(car == clone);
            }

            // 4-я скорость
            {
                car.SetSpeed(60);
                car.SetGear(4);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(91));
                BOOST_CHECK(!car.SetSpeed(39));

                BOOST_CHECK(car == clone);
            }

            // 5-я скорость
            {
                car.SetSpeed(90);
                car.SetGear(5);
                auto clone(car);

                BOOST_CHECK(!car.SetSpeed(151));
                BOOST_CHECK(!car.SetSpeed(49));

                BOOST_CHECK(car == clone);
            }
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
