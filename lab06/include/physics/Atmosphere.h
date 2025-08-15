#pragma once

namespace adaai::solution {
    class Atmosphere {
    private:
        constexpr static const double HEIGHT_1_UPPER_BOUND = 11'000.0;
        constexpr static const double HEIGHT_2_UPPER_BOUND = 20'000.0;
        constexpr static const double HEIGHT_3_UPPER_BOUND = 32'000.0;
        constexpr static const double HEIGHT_4_UPPER_BOUND = 47'000.0;

        constexpr static const double R_0 = 6.5e-3;
        constexpr static const double R_1 = 0.0;
        constexpr static const double R_2 = -10e-3;
        constexpr static const double R_3 = -2.83e-3;

        constexpr static double T0 = 288.15;
        constexpr static double T1 = 216.65;
        constexpr static double T2 = 216.65;
        constexpr static double T3 = 228.65;

        constexpr static double P0 = 101325.0;
        constexpr static double P1 = 22632.3777602;
        constexpr static double P2 = 5475.03644646;
        constexpr static double P3 = 868.056901172;

        constexpr static int AirSpeedSize = 7;
        constexpr static double Heights[AirSpeedSize] = {0, 1'000, 5'000, 10'000, 20'000, 50'000, 80'000};
        constexpr static double AirSpeed[AirSpeedSize] = {340.29, 336.43, 320.54, 299.53, 295.07, 329.8, 282.54};

    public:
        ///@brief calculates air density at a specific height
        ///@param height - in meters. Must be less than 47'000
        static double getDensity(double height);

        static double getPressure(double height);

        static double getAirSpeed(double height);
    };
}