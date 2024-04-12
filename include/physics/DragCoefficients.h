#pragma once

namespace adaai::solution {
    class DragCoefficients {
    public:
        ///@brief returns drag coefficients
        ///@param speed - speed in Mach numbers Must belong to [0.4; 2.2]
        static double get(double speed);
    };
}