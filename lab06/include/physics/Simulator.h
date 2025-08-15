#pragma once

namespace adaai::solution {
    class Simulator {
    public:
        struct Params {
            double x{};
            double y{};
            double vX{};
            double vY{};
            double mass{};
            ///cross-sectional area (in m^2)
            double csa{};
            double time{};

            ///@brief function, specifying air density at a specific height
            ///@return absolute air density value
            double (*airDensity)(double height){};

            ///@brief function, specifying gravity acceleration (G) at a specific height
            ///@details note that the gravity forces are applied along Y-axis
            ///@return absolute value of G
            double (*gravity)(double height){};

            ///@brief function, specifying drag force coefficient at a specific speed (in mach)
            ///@brief absolute value of the coefficient
            double (*dragCoefficient)(double speed){};

            ///@brief function, specifying air speed (in m/s) at a specific height
            double (*airSpeed)(double height){};

            ///@brief function, which controls the simulation and makes slices of the telemetry
            ///@return true - simulation should continue, false - termination flag
            bool (*handler)(double x, double y, double vX, double vY, double timePast){};
        };

    private:
        Params _params{};
        double _timeStep{};
        double arr[4]{};

    public:
        ///@brief creates a simulate for calculating ballistic trajectory of the body
        ///@param initialParams - _parameters, which specify the initial state of the experiment
        ///@param timeStep - global step (in seconds). The smaller it is, the more precise simulation will perform
        Simulator(Params initialParams, double timeStep);

        ///@brief starts simulation until the stopper function returns false
        Params simulate(double endTime);

        Params simulate2(double endTime);

    private:
        static int function(double t, const double *arr, double *funcs, void *parameters);
    };
}