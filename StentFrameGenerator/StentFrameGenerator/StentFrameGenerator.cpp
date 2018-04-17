#include "StentFrameGenerator.h"
#include "BeizerSpline.h"

#include <iostream>

StentFrameGenerator::StentFrameGenerator(int sampleCnt, int periodCnt, float xzScale, float yScale, bool splineFit) : m_SampleCnt(sampleCnt)
	,m_PeriodCnt(periodCnt)
	,m_PartCnt(10)
	,m_xzScale(xzScale)
	,m_yScale(yScale)
	,m_SplineFit(splineFit)
{

	CacheSinsAndCoss();
}

StentFrameGenerator::~StentFrameGenerator()
{
}

std::vector<iv::vec3> StentFrameGenerator::CreateStentLine(const TNB & tnb, float xzScale, float yScale)
{
	using namespace iv;
	const vec3& vx = tnb.N;
	const vec3& vy = tnb.T;
	const vec3& vz = tnb.B;

	float dx = 4.0f / (float)m_SampleCnt;

	std::vector<vec3> pts;

	for (int j = 0; j < m_PeriodCnt; ++j)
	{
		float xBase = (float)j * 4.0f;
		for (int i = 0; i < m_SampleCnt; ++i)
		{
			vec3 p;
			p.x = dx * (float)i + xBase;
			p.y = yScale * m_CachedSins[i];
			pts.push_back(p);
		}
	}

	for (int i = 0; i < pts.size(); ++i)
	{
		pts[i].x = xzScale * m_CachedSins2[i];
		pts[i].z = xzScale * m_CachedCoss2[i];
	}

	for (int i = 0; i < pts.size(); ++i)
	{
		const vec3& p = pts[i];
		pts[i] = tnb.O + vx * p.x + vy * p.y + vz * p.z;
	}

	pts.push_back(pts[0]);
	return pts;
}

void StentFrameGenerator::CreateStentFrame(const std::vector<iv::vec3>& i_pts, std::vector<std::vector<iv::vec3>>& o_pts)
{
	using namespace std;
	using namespace iv;
	if (i_pts.empty())
		return;


	if (m_SplineFit)
	{
		BeizerSplineGenerator bsg(0.1f);
		vector<vec3> bzpts,realipts;
		bsg.CreateBeizeSpline(i_pts, bzpts);
		int bzcnt = bzpts.size();
		cout << "bzcnt:" << bzcnt << endl;
		int gap = bzcnt / m_PartCnt;
		cout << "gap:" << gap << endl;
		for (int i = 0; i < bzcnt; i += gap)
		{
			cout << "--:" << i << endl;
			realipts.push_back(bzpts[i]);
		}
		UpdateTNBFrames(realipts);
	}
	else
		UpdateTNBFrames(i_pts);
	o_pts.clear();
	for (int i = 0; i < m_Frames.size(); ++i)
	{
		o_pts.push_back(CreateStentLine(m_Frames[i], m_xzScale, m_yScale));
	}
}

void StentFrameGenerator::UpdateTNBFrames(const std::vector<iv::vec3>& pts)
{
	using namespace iv;

	m_Frames.clear();

	int ptCnt = pts.size();
	for (int i = 0; i < ptCnt - 1; ++i)
	{
		TNB tnb;
		const vec3& p0 = pts[i];
		const vec3& p1 = pts[i + 1];
		tnb.T = normalize(p1 - p0);
		if (i == 0)
		{
			vec3 tmp = normalize(vec3(tnb.T.x + 0.5f, tnb.T.y - 0.5f, tnb.T.z));
			tnb.N = normalize(cross(tmp, tnb.T));
			tnb.B = normalize(cross(tnb.N, tnb.T));
		}
		else
		{
			float rad = iv::GetRadianBetween(m_Frames[i - 1].T, tnb.T);
			if (rad < 0.00001)
			{
				tnb.N = m_Frames[i - 1].N;
				tnb.B = m_Frames[i - 1].B;
			}
			else
			{
				vec3 axis = normalize(cross(m_Frames[i - 1].T, tnb.T));
				mat4 rotMat = rotate(rad, axis);
				tnb.N = (rotMat * vec4(m_Frames[i - 1].N, .0f)).xyz();
				tnb.B = (rotMat * vec4(m_Frames[i - 1].B, .0f)).xyz();
			}
		}
		tnb.O = p0;
		m_Frames.push_back(tnb);
	}
}

void StentFrameGenerator::CacheSinsAndCoss()
{
	m_CachedSins.resize(m_SampleCnt, .0f);
	m_CachedCoss.resize(m_SampleCnt, .0f);
	float drad = iv::ivTWOPI / (double)m_SampleCnt;
	for (int i = 0; i < m_SampleCnt; ++i)
	{
		float rad = (float)i * drad;
		m_CachedSins[i] = std::sinf(rad);
		m_CachedCoss[i] = std::cosf(rad);
	}

	int total = m_SampleCnt * m_PeriodCnt;
	m_CachedSins2.resize(total, .0f);
	m_CachedCoss2.resize(total, .0f);
	float drad2 = iv::ivTWOPI / (double)total;
	for (int i = 0; i < total; ++i)
	{
		float rad2 = (float)i * drad2;
		m_CachedSins2[i] = std::sinf(rad2);
		m_CachedCoss2[i] = std::cosf(rad2);
	}
}
