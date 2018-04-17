#include "StentFrameGenerator.h";
#include "BeizerSpline.h"

#include <fstream>

#if 0
extern "C"
{
	__declspec(dllexport) bool init_dll()
	{
		if (s_pStentFrameGenerator == 0)
			s_pStentFrameGenerator = new StentFrameGenerator(32, 12, 12, false);
		if (s_pBeizerGenerator == 0)
			s_pBeizerGenerator = new BeizerSplineGenerator(0.1f);
		return true;
	}
	__declspec(dllexport) void CreateBeizerLine(float* pts,int ptCnt)
	{
		if (s_pBeizerGenerator == 0)
			return;

		std::ofstream abc("log.txt", std::ios::ate);

		std::vector<iv::vec3> ipts;
		for (int i = 0; i < ptCnt; ++i)
		{
			ipts.push_back(iv::vec3(pts));
			abc << pts[0] << "," << pts[1] << "," << pts[2] << "\n";
			pts += 3;
		}

		abc.flush();
		abc.close();

		s_pBeizerGenerator->CreateBeizeSpline(ipts, s_BeizerPts);
	}
	__declspec(dllexport) float* GetPtsPtr()
	{
		return s_BeizerPts[0].v;
	}
}
#endif

using namespace std;
using namespace iv;

int main()
{
	StentFrameGenerator sfg(32, 12,0.1f, 0.02f, true);
	vector<vec3> pts;
	pts.push_back(vec3(.0f, .0f, .0f));
	pts.push_back(vec3(1.0f, .0f, .0f));
	pts.push_back(vec3(1.0f, 1.0f, .0f));
	pts.push_back(vec3(1.0f, 1.0f, 1.0f));
	vector<vector<vec3>> result;
	sfg.CreateStentFrame(pts, result);
	if (result.empty())
		return -1;
	std::ofstream rf("result.txt", ios::ate);
	for (int i = 0; i < result.size(); ++i)
	{
		for (int j = 0; j < result[i].size(); ++j)
		{
			const vec3& p = result[i][j];
			rf << p.x << "\t" << p.y << "\t" << p.z << "\n";
		}
	}
	rf.close();

	getchar();
	getchar();

	return 0;
}