#pragma once

#include "SiMath.h"
#include <vector>

class BeizerSplineGenerator
{
public:
	explicit BeizerSplineGenerator(float step);

	void CreateBeizeSpline(const std::vector<iv::vec3>& i_pts,
		std::vector<iv::vec3>& o_pts);

private:
	std::vector<iv::vec3> m_CachedMidpts;
	float m_Step;
};