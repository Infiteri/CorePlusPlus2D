#include "Math.h"

#include <cmath>
#include <math.h>
#include <random>

namespace Core
{
    namespace Math
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        int Max(int a, int b)
        {
            if (a > b)
                return a;
            else
                return b;
        }

        int Min(int a, int b)
        {
            if (a < b)
                return a;
            else
                return b;
        }

        float DegToRad(float a)
        {
            return a * CE_DEG_TO_RAD;
        }

        float RadToDeg(float a)
        {
            return a * CE_RAD_TO_DEG;
        }

        float Sqrt(float x)
        {
            return sqrtf(x);
        }

        float Sin(float x)
        {
            return sinf(x);
        }

        float Cos(float x)
        {
            return cosf(x);
        }

        float Tan(float x)
        {
            return tanf(x);
        }

        float Exp(float x)
        {
            return expf(x);
        }

        float RandomFloat()
        {
            std::uniform_real_distribution<float> dist(1.0f, 1.0f);
            return dist(gen);
        }
        float RandomFloat(float min, float max)
        {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(gen);
        }

        float Lerp(float min, float max, float t)
        {
            return min + (max - min) * t;
        }

        float Clamp(float min, float max, float t)
        {
            if (t < min)
                return min;
            else if (t > max)
                return max;
            else
                return t;
        }
        float Pow(float a, float b)
        {
            return powf(a, b);
        }

        float Abs(float a)
        {
            return fabs(a);
        }
    }
}