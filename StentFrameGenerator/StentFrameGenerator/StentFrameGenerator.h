#pragma once

#include <vector>
#include "SiMath.h"

/* example */
/*
	StentFrameGenerator sfg(32, 12, 0.1f, 0.02f, true);
	vector<vec3> pts;
	pts.push_back(vec3(.0f, .0f, .0f));
	pts.push_back(vec3(1.0f, .0f, .0f));
	pts.push_back(vec3(1.0f, 1.0f, .0f));
	pts.push_back(vec3(1.0f, 1.0f, 1.0f));
	vector<vector<vec3>> result;
	sfg.CreateStentFrame(pts, result);
*/

class StentFrameGenerator
{
private:
	struct TNB
	{
		iv::vec3 T;
		iv::vec3 N;
		iv::vec3 B;
		iv::vec3 O;
	};
public:
	// sampleCnt: sample count of 2PI.
	// periodCnt: count of sin periond repeated in a layer.
	// xzScale: scale factor of xz plane.
	// yScale: scale factor of y direction.
	// splineFit: whether use beizer spline to fit the center-line.
	StentFrameGenerator(int sampleCnt, int periodCnt,float xzScale,float yScale, bool splineFit);

	~StentFrameGenerator();

	// i_pts: input points.
	// o_pts: output points.
	void CreateStentFrame(const std::vector<iv::vec3>& i_pts, std::vector<std::vector<iv::vec3>>& o_pts);

private:
	void CacheSinsAndCoss();
	std::vector<iv::vec3> CreateStentLine(const TNB& tnb, float xzScale, float yScale);
	void UpdateTNBFrames(const std::vector<iv::vec3>& pts);

private:
	int m_SampleCnt;
	int m_PeriodCnt;
	int m_PartCnt;
	bool m_SplineFit;

	float m_xzScale;
	float m_yScale;

	std::vector<float> m_CachedSins;
	std::vector<float> m_CachedCoss;
	std::vector<float> m_CachedSins2;
	std::vector<float> m_CachedCoss2;

	std::vector<TNB> m_Frames;
};