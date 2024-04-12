#pragma once

namespace adaai::solution {
    class AirDensity {
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

    public:
        ///@brief calculates air density at a specific height
        ///@param height - in meters. Must be less than 47'000
        static double get(double height);

        static double getPressure(double height);
    };
}