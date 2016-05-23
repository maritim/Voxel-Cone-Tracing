#ifndef VERTEXBONEINFO
#define VERTEXBONEINFO

#include "Core/Interfaces/Object.h"

#include <vector>

class VertexBoneInfo : public Object
{
protected:
	std::vector<unsigned int> _boneIDs;
	std::vector<float> _boneWeights;

public:
	std::size_t GetBoneIDsCount () const;
	std::size_t GetBoneWeightsCount () const;

	unsigned int GetBoneID (std::size_t index) const;
	float GetBoneWeight (std::size_t index) const;

	void AddBone (unsigned int boneID, float boneWeight);
};

#endif