/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest.h"
#include "core/sampling/sampling.h"

template <int N>
void CheckUniformity(std::vector<Vector<double, N>> samples, double totalArea)
{
	const int numAreasToTest = 500;
	const double radiusToTest = 0.1;

    // Points must be uniformly distributed
    // For every point, it should roughly have the same number of neighbors
    // as any other point
    std::vector<int> numNeighborsPerPoint;
    numNeighborsPerPoint.reserve(numAreasToTest);

    // Keep track of sum for faster mean computation later
    int totalNeighborsOfAllPoints = 0;

    for (int i = 0; i < numAreasToTest; ++i)
    {
        int numNeighbors = 0;
        for (int j = 0; j < samples.size(); ++j)
        {
            // Use sqr magnitude vs delta area instead of magnitude vs radius
            // for faster computation
            if ((samples[j] - samples[i]).Magnitude() <= radiusToTest)
                numNeighbors++;
        }

        numNeighborsPerPoint.push_back(numNeighbors);
        totalNeighborsOfAllPoints += numNeighbors;
    }

    double meanNeighborCount = (double)totalNeighborsOfAllPoints / numNeighborsPerPoint.size();

    // Compute variance
    double sumOfDeviationSquared = 0;
    for (int i = 0; i < numNeighborsPerPoint.size(); ++i)
    {
        sumOfDeviationSquared += std::pow(numNeighborsPerPoint[i] - meanNeighborCount, 2);
    }

    double variance = sumOfDeviationSquared / numNeighborsPerPoint.size();
    double stdDeviation = std::sqrt(variance);

    
	//std::cout << "samples: " << samples.size() << std::endl;
	//std::cout << "variance " << variance << std::endl;
	//std::cout << "standard deviation " << stdDeviation << std::endl;
	//std::cout << "average neighbors per sample: " << meanNeighborCount << std::endl;


    // area = totalArea
    // area of sample = pi * r^2
	// num areas = totalArea / (pi * r^2)
    double numDeltaArea = totalArea / (Math::Pi * radiusToTest * radiusToTest);
    double expectedNeighborCount = samples.size() / numDeltaArea;
    //std::cout << "expectedNeighborCount: " << expectedNeighborCount << std::endl;

    EXPECT_LT(stdDeviation / expectedNeighborCount, 0.5);
}

TEST(SamplingTest, CanSampleHemisphereUniformly)
{
    const int numSamples = 50000;

    std::vector<Vector3> samples(numSamples);

    for (int i = 0; i < numSamples; ++i)
    {
        Vector3 sample = Sampling::UniformSampleHemisphere();

        // Points must be on the surface of the sphere
        EXPECT_LE(std::abs(sample.Magnitude() - 1.0), Math::Epsilon);
        // Points must be on upper hemisphere
        EXPECT_GE(sample.y, 0.0);

        samples[i] = sample;
    }

    CheckUniformity(samples, Math::Pi * 2);
}

TEST(SamplingTest, CanSampleSphereUniformly)
{
    const int numSamples = 50000;
    const int numAreasToTest = 500;
    const double radiusToTest = 0.1;

    std::vector<Vector3> samples(numSamples);

    for (int i = 0; i < numSamples; ++i)
    {
        Vector3 sample = Sampling::UniformSampleSphere();

        // Points must be on the surface of the sphere
        EXPECT_LE(std::abs(sample.Magnitude() - 1.0), Math::Epsilon);
        samples[i] = sample;
    }

	CheckUniformity(samples, Math::Pi * 4);
}

TEST(SamplingTest, CanSampleDiskUniformly_RejectionMethod)
{
	const int numSamples = 50000;
	const int numAreasToTest = 500;
	const double radiusToTest = 0.1;

	std::vector<Vector2> samples(numSamples);

	for (int i = 0; i < numSamples; ++i)
	{
		Vector2 sample = Sampling::RejectionSampleDisk();

		// Points must be within the disk
		EXPECT_LE(sample.Magnitude(), 1.0 + Math::Epsilon);
		samples[i] = sample;
	}

	CheckUniformity(samples, Math::Pi);
}

TEST(SamplingTest, CanSampleDiskUniformly_ConcentricMethod)
{
	const int numSamples = 50000;
	const int numAreasToTest = 500;
	const double radiusToTest = 0.1;

	std::vector<Vector2> samples(numSamples);

	for (int i = 0; i < numSamples; ++i)
	{
		Vector2 sample = Sampling::ConcentricSampleDisk();

		// Points must be within the disk
		EXPECT_LE(sample.Magnitude(), 1.0 + Math::Epsilon);
		samples[i] = sample;
	}

	CheckUniformity(samples, Math::Pi);
}
