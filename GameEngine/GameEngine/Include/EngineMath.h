#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;

#include "Flag.h"
#include <math.h>
#include <random>

#define PI  3.14159f

static float DegreeToRadian(float Angle)
{
    return Angle / 180.f * PI;
}

static float RadianToDegree(float Angle)
{
    return Angle * 180.f / PI;
}

static int GetRandom(int Min, int Max)
{
	std::random_device rd;
	std::mt19937_64 rng1(rd());
	std::uniform_int_distribution<int> dist(Min, Max);


	return dist(rng1);
}

static float GetRandomFloat(float Min, float Max)
{
	float Range = Max - Min;
		float ret = (float)GetRandom(1,10000) * Range;
		ret += Min;

	return ret;
}

static float GetRandomFloat2(int Min, int Max, float division)
{
	float Ret = (float)GetRandom(Min, Max);
	Ret /= division;

	return Ret;
}