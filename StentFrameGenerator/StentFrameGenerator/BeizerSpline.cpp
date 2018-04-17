#include "BeizerSpline.h"

BeizerSplineGenerator::BeizerSplineGenerator(float step) : m_Step(step)
{
}

void BeizerSplineGenerator::CreateBeizeSpline(const std::vector<iv::vec3>& i_pts, std::vector<iv::vec3>& o_pts)
{
	using namespace iv;

	if (i_pts.size() <= 2)
		return;

	m_CachedMidpts.clear();
	
	int ptCnt = i_pts.size();

	for (int i = 0; i < ptCnt; ++i)
	{
		vec3 prev = (i == 0) ? i_pts[i] : i_pts[i - 1];
		vec3 p = i_pts[i];
		vec3 next = (i == (ptCnt - 1)) ? i_pts[i]: i_pts[i + 1];

		vec3 mid_prev = (prev + p) * 0.5f;
		vec3 mid_next = (next + p) * 0.5f;

		vec3 offset = (mid_next - mid_prev) * 0.5f;

		m_CachedMidpts.push_back(p - offset);
		m_CachedMidpts.push_back(p + offset);
	}

	o_pts.clear();


	for (int i = 0; i < ptCnt - 1; ++i)
	{
		vec3 p0 = i_pts[i];
		vec3 p1 = m_CachedMidpts[2 * i + 1];
		vec3 p2 = m_CachedMidpts[2 * (i + 1) + 0];
		vec3 p3 = i_pts[i + 1];

		float t = 0.0f;

		while (t < 1.0f)
		{
			float c0 = (1.0f - t) * (1.0f - t) * (1.0f - t);
			float c1 = 3.0f * (1.0f - t) * (1.0f - t) * t;
			float c2 = 3.0f * (1.0f - t) * t * t;
			float c3 = t * t * t;

			vec3 px = p0 * c0 + p1 * c1 + p2 * c2 + p3 * c3;
			o_pts.push_back(px);

			t += m_Step;
		}
	}

	o_pts.push_back(i_pts[ptCnt - 1]);
}
