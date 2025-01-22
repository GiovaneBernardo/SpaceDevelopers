#pragma once
#include "pch.h"

namespace Plaza {
	class PlanetGenerator : public CppScript {
	public:
		int mGridSize = 64;
		float mIsoLevel = 0.6f;
		float mNoiseFrequency = 2.0f;
		float mNoiseAmplitude = 2.7f;
		float mMaxHeight = 10.0f;
		float mMinHeight = 0.0f;
		glm::vec3 mCubicChunksSize = glm::vec3(256.0f, 256.0f, 256.0f);
		int mPlanetRadius = 1000.0f;

		void OnStart(Scene* scene);
		void OnUpdateEditorGUI(Scene* scene);

		std::vector<std::vector<std::vector<float>>> mLastGeneratedGrid;
		Entity* mLastGeneratedPlanet = nullptr;
	private:
		Entity* GeneratePlanet(Scene* scene, const std::vector<std::vector<std::vector<float>>>& grid, const int gridSize, const float isoLevel);
		Mesh* GenerateMesh(const std::vector<std::vector<std::vector<float>>>& grid, const int gridSize, const float isoLevel);
		std::vector<std::vector<std::vector<float>>> GenerateGrid(const int gridSize, const float isoLevel, const float noiseFrequency, const float noiseAmplitude);
	};
	PL_REGISTER_SCRIPT(PlanetGenerator);
}