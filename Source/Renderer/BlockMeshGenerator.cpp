#include "BlockMeshGenerator.h"

#include "BlockTexture.h"

namespace BlockMeshGenerator
{
	namespace
	{
		const std::array<std::array<std::pair<glm::vec3, glm::vec2>, 6>, 6> faceVertices = { {
		   {{
				   // YP
				   {{0, 1, 1}, {1, 0}},
				   {{1, 1, 1}, {1, 1}},
				   {{0, 1, 0}, {0, 0}},
				   {{1, 1, 1}, {1, 1}},
				   {{1, 1, 0}, {0, 1}},
				   {{0, 1, 0}, {0, 0}},
				}},
				{{
						// XP
						{{1, 1, 1}, {1, 0}},
						{{1, 0, 1}, {1, 1}},
						{{1, 1, 0}, {0, 0}},
						{{1, 0, 1}, {1, 1}},
						{{1, 0, 0}, {0, 1}},
						{{1, 1, 0}, {0, 0}},
					 }},
					 {{
							 // XN
							 {{0, 1, 0}, {1, 0}},
							 {{0, 0, 0}, {1, 1}},
							 {{0, 1, 1}, {0, 0}},
							 {{0, 0, 0}, {1, 1}},
							 {{0, 0, 1}, {0, 1}},
							 {{0, 1, 1}, {0, 0}},
						  }},
						  {{
								  // ZN
								  {{1, 1, 0}, {1, 0}},
								  {{1, 0, 0}, {1, 1}},
								  {{0, 1, 0}, {0, 0}},
								  {{1, 0, 0}, {1, 1}},
								  {{0, 0, 0}, {0, 1}},
								  {{0, 1, 0}, {0, 0}},
							   }},

							   {{
									   // ZP
									   {{0, 1, 1}, {1, 0}},
									   {{0, 0, 1}, {1, 1}},
									   {{1, 1, 1}, {0, 0}},
									   {{0, 0, 1}, {1, 1}},
									   {{1, 0, 1}, {0, 1}},
									   {{1, 1, 1}, {0, 0}},
									}},
									{{
											// YN
											{{1, 0, 1}, {1, 0}},
											{{0, 0, 1}, {1, 1}},
											{{1, 0, 0}, {0, 0}},
											{{0, 0, 1}, {1, 1}},
											{{0, 0, 0}, {0, 1}},
											{{1, 0, 0}, {0, 0}},
										 }},
									  } };
	}

	std::vector<BlockVertex> BlockMeshGenerator::generateMesh(const Block& block, Sides side)
	{
		std::vector<BlockVertex> vertices;

		int index = 0;
		switch (side)
		{
		case Sides::XP:
			index = 1;
			break;
		case Sides::XN:
			index = 2;
			break;
		case Sides::ZP:
			index = 4;
			break;
		case Sides::ZN:
			index = 3;
			break;
		case Sides::YP:
			index = 0;
			break;
		case Sides::YN:
			index = 5;
			break;
		}

		for (const auto& [pos, uv] : faceVertices[index])
		{
			vertices.push_back({ pos, uv, BlockTexture::getBlockAtlas(block, side) });
		}

		return vertices;
	}
}