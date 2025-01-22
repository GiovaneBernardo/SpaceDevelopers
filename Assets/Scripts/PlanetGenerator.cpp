#include "PlanetGenerator.h"
#include "MarchingCubes.h"

namespace Plaza {
	void PlanetGenerator::OnStart(Scene* scene) {
		ECS::RegisterComponents();
	}
	void PlanetGenerator::OnUpdateEditorGUI(Scene* scene) {
		PLAZA_PROFILE_SECTION("section");
		PL_CORE_INFO("Info");
		std::cout << Scene::GetActiveScene()->mAssetName << "\n";
		if (ImGui::Button("Generate Planet")) {
			std::cout << "Generation tion tion é o generation \n";
			mLastGeneratedGrid = this->GenerateGrid(mGridSize, mIsoLevel, mNoiseFrequency, mNoiseAmplitude);
			mLastGeneratedPlanet = this->GeneratePlanet(scene, mLastGeneratedGrid, mGridSize, mIsoLevel);
		}
		ImGui::DragInt("Grid Size", &mGridSize);
		ImGui::DragFloat("Iso Level", &mIsoLevel);
		ImGui::DragFloat("Noise Frequency", &mNoiseFrequency);
		ImGui::DragFloat("Noise Amplitude", &mNoiseAmplitude);
		ImGui::DragFloat("Max Height", &mMaxHeight);
		ImGui::DragFloat("Min Height", &mMinHeight);
		if (Input::GetKeyDown(GLFW_KEY_M)) {
			MeshRenderer* meshRenderer = scene->NewComponent<MeshRenderer>(mLastGeneratedPlanet->uuid);
			Mesh* newMesh = this->GenerateMesh(mLastGeneratedGrid, mGridSize, mIsoLevel);
			meshRenderer->ChangeMesh(newMesh);
		}
	}

	Entity* PlanetGenerator::GeneratePlanet(Scene* scene, const std::vector<std::vector<std::vector<float>>>& grid, const int gridSize, const float isoLevel) {
		if (mLastGeneratedPlanet != nullptr)
			Scene::GetActiveScene()->RemoveEntity(mLastGeneratedPlanet->uuid);
		Entity* planetEntity = scene->NewEntity("Planet");
		MeshRenderer* meshRenderer = scene->NewComponent<MeshRenderer>(planetEntity->uuid);
		Mesh* newMesh = this->GenerateMesh(grid, gridSize, isoLevel);
		//for (int x = 0; x < grid.size(); ++x) {
		//	for (int y = 0; y < grid[x].size(); ++y) {
		//		for (int z = 0; z < grid[x][y].size(); ++z) {
		//			if (grid[x][y][z] < isoLevel) {
		//				CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x, y, z));
		//
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x, y, z));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x + 1, y, z));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x + 1, y + 1, z));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x, y + 1, z));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x, y, z + 1));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x + 1, y, z + 1));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x + 1, y + 1, z + 1));
		//				//CppHelper::FindEntity(Entity::Instantiate(CppHelper::FindEntity("SphereInstance")->uuid))->GetComponent<Transform>()->SetRelativePosition(glm::vec3(x, y + 1, z + 1));
		//			}
		//		}
		//	}
		//}

		meshRenderer->ChangeMesh(newMesh);
		meshRenderer->AddMaterial(AssetsManager::GetDefaultMaterial());
		return planetEntity;
	}


	Mesh* PlanetGenerator::GenerateMesh(const std::vector<std::vector<std::vector<float>>>& grid, const int gridSize, const float isoLevel) {
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> tangents;
		std::vector<unsigned int> materials{ 0 };

		for (int x = 0; x < gridSize - 1; ++x) {
			for (int y = 0; y < gridSize - 1; ++y) {
				for (int z = 0; z < gridSize - 1; ++z) {
					float cubeCorners[8] = {
						grid[x][y][z],
						grid[x + 1][y][z],
						grid[x + 1][y][z + 1],
						grid[x][y][z + 1],
						grid[x][y + 1][z],
						grid[x + 1][y + 1][z],
						grid[x + 1][y + 1][z + 1],
						grid[x][y + 1][z + 1]
					};
					glm::vec3 cubeOffset(x, y, z);

					MarchingCubes::March(cubeCorners, isoLevel, vertices, indices, normals, uvs, cubeOffset, mGridSize, mNoiseFrequency, mMaxHeight, mMinHeight, false);
				}
			}
		}

		//for (int i = 0; i < vertices.size(); ++i) {
		//	uvs.push_back(glm::vec2(0.5, 0.5f));
		//}

		if (vertices.size() <= 3)
			return nullptr;
		Mesh* newMesh = Application::Get()->mRenderer->CreateNewMesh(
			vertices, normals, uvs, tangents, indices, materials, false, {}, {}
		);
		AssetsManager::AddMesh(newMesh);
		return newMesh;
	}

	std::vector<std::vector<std::vector<float>>> PlanetGenerator::GenerateGrid(const int gridSize, const float isoLevel, const float noiseFrequency, const float noiseAmplitude) {
		const float stepSize = 2.0f / gridSize;

		std::vector<std::vector<std::vector<float>>> grid(gridSize, std::vector<std::vector<float>>(gridSize, std::vector<float>(gridSize)));
		PerlinNoise perlin = PerlinNoise();

		// Generate a sphere + mountains
		for (int x = 0; x < gridSize; ++x) {
			for (int y = 0; y < gridSize; ++y) {
				for (int z = 0; z < gridSize; ++z) {
					// Normalize position to [-1, 1]
					glm::vec3 position = glm::vec3(
						(x - gridSize / 2) / float(gridSize / 2),
						(y - gridSize / 2) / float(gridSize / 2),
						(z - gridSize / 2) / float(gridSize / 2)
					);

					// Base density: distance from center for a smooth sphere
					float baseDensity = glm::length(position);

					// Noise-based perturbations
					float noise = 0.0f;
					float amplitude = noiseAmplitude;
					float frequency = noiseFrequency;

					for (int octave = 0; octave < 6; ++octave) {
						float ridgedNoise = 1.0f - fabs(perlin.Noise(position * frequency));
						ridgedNoise = ridgedNoise * ridgedNoise; // Emphasize peaks
						noise += ridgedNoise * amplitude;

						amplitude *= 0.5f;  // Reduce amplitude for finer octaves
						frequency *= 2.0f;  // Increase frequency for finer details
					}

					// Fade noise influence near the surface
					float distanceToSurface = fabs(baseDensity - isoLevel);
					float noiseFalloff = exp(-distanceToSurface * 10.0f);
					noise *= noiseFalloff;

					//baseDensity = -y / gridSize;
					//baseDensity += -glm::length(position) / gridSize;
					// Combine base sphere with noise
					//baseDensity += perlin.Noise(glm::vec3(x, y, z));
					//baseDensity += perlin.Noise(glm::vec3(x, y, z) * 16.12f) * 0.0575f;
					//baseDensity += perlin.Noise(glm::vec3(x, y, z) * 8.06f) * 0.125f;
					//baseDensity += perlin.Noise(glm::vec3(x, y, z) * 4.03f) * 0.25f;
					//baseDensity += perlin.Noise(glm::vec3(x, y, z) * 1.96f) * 0.50f;
					//baseDensity += perlin.Noise(glm::vec3(x, y, z) * 1.01f) * 1.00f;
					grid[x][y][z] = baseDensity - noise;
				}
			}
		}
		return grid;
	}
}