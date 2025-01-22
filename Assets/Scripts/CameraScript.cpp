#include "CameraScript.h"

namespace Plaza {
	glm::mat4 interpolateMat4(const glm::mat4& mat1, const glm::mat4& mat2, float t) {
		// Decompose mat1
		glm::vec3 scale1, translation1, skew1;
		glm::vec4 perspective1;
		glm::quat rotation1;
		glm::decompose(mat1, scale1, rotation1, translation1, skew1, perspective1);

		// Decompose mat2
		glm::vec3 scale2, translation2, skew2;
		glm::vec4 perspective2;
		glm::quat rotation2;
		glm::decompose(mat2, scale2, rotation2, translation2, skew2, perspective2);

		// Interpolate translation
		glm::vec3 interpolatedTranslation = glm::mix(translation1, translation2, t);

		// Interpolate rotation (SLERP)
		glm::quat interpolatedRotation = glm::slerp(rotation1, rotation2, t);

		// Interpolate scale
		glm::vec3 interpolatedScale = glm::mix(scale1, scale2, t);

		// Reconstruct the matrix from the interpolated components
		glm::mat4 result = glm::mat4(1.0f);
		result = glm::translate(result, interpolatedTranslation);
		result *= glm::mat4_cast(interpolatedRotation);
		result = glm::scale(result, interpolatedScale);

		return result;
	}

	void CameraScript::OnStart(Scene* scene) {
		for (unsigned int i = 0; i < mPosCount; ++i) {
			mMatrices.push_back(scene->GetComponent<TransformComponent>(CppHelper::FindEntity("pos" + std::to_string(i))->uuid)->GetWorldMatrix());
		}
	}

	void CameraScript::OnUpdate(Scene* scene) {
		std::cout << "Start" << "\n";
		std::cout << mCurrentTime << "\n";
		std::cout << mCurrentPosIndex << "\n";
		std::cout << mPosCount << "\n";
		std::cout << "End" << "\n";
		if (mCurrentTime > 1.0f) {
			mCurrentTime = 0.0f;
			//mCurrentPosIndex = 0.0f;
			mCurrentPosIndex++;
			if (mCurrentPosIndex > mPosCount)
				mCurrentPosIndex = 0;
		}
		if (mCurrentPosIndex + 1 < mMatrices.size()) {
			glm::mat4 result = interpolateMat4(mMatrices[mCurrentPosIndex], mMatrices[mCurrentPosIndex + 1], mCurrentTime);
			uint64_t cameraUuid = CppHelper::FindEntity("CameraEntity")->uuid;
			scene->GetComponent<TransformComponent>(cameraUuid)->mLocalPosition = result[3];
			scene->GetComponent<TransformComponent>(cameraUuid)->mLocalRotation = glm::quat_cast(glm::mat3(result));
			ECS::TransformSystem::UpdateSelfAndChildrenTransform(*scene->GetComponent<TransformComponent>(cameraUuid), nullptr, scene, true);
		}
		else
			mCurrentPosIndex = 0;
		mCurrentTime += 0.31f * Time::deltaTime;
	}
}