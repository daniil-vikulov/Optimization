#pragma once

namespace adaai::solution {
    class DragCoefficients {
    private:
        static constexpr int Size = 14;

        static constexpr double Speed[Size] = {
                0.4, 0.6, 0.8, 0.86, 0.91, 0.95, 1.0, 1.2, 1.4, 1.61, 1.8, 2.1, 2.2
        };
        static constexpr double Value[Size] = {
                0.086, 0.097, 0.1, 0.11, 0.125, 0.215, 0.37, 0.32, 0.305, 0.285, 0.27, 0.235, 0.22
        };

    public:
        ///@brief returns drag coefficients
        ///@param speed - speed in Mach numbers Must belong to [0.4; 2.2]
        static double get(double speed);

    private:
        ///@param index - index of the left existing point (whose speed is less than ${speed})
        static double interpolate(int index, double speed);
    };
}