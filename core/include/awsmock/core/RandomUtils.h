//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWSMOCK_CORE_RANDOMUTILS_H
#define AWSMOCK_CORE_RANDOMUTILS_H

// Standard C++ includes
#include <string>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>

namespace AwsMock::Core {

    /**
     * Random utilities.
     *
     * <p>Using the Mersenne Twister random generator with a uniform distribution.</p>
     */
    class RandomUtils {

    public:

      /**
       * Generates a random integer between min and max
       *
       * @param min minimum integer
       * @param max minimum integer
       * @return random number between min and max
       */
      static int NextInt(int min, int max);

      /**
       * Generates a random integer array, with random numbers between min and max with the given size
       *
       * @param size number of random numbers to generate
       * @param min minimum integer
       * @param max minimum integer
       * @return random number between min and max
       */
      static std::vector<int> IntArray(int size, int min, int max);

      /**
       * Generates a double between min and max
       *
       * @param min minimum integer
       * @param max minimum integer
       * @return double random number between min and max
       */
      static double NextDouble(double min, double max);

      /**
       * Generates a random double array, with random numbers between min and max with the given size
       *
       * @param size number of random numbers to generate
       * @param min minimum integer
       * @param max minimum integer
       * @return double random number between min and max
       */
      static std::vector<double> DoubleArray(int size, double min, double max);

    };

}

#endif // AWSMOCK_CORE_RANDOMUTILS_H