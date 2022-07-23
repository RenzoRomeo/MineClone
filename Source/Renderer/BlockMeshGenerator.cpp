#include "BlockMeshGenerator.h"

#include "BlockTexture.h"

namespace BlockMeshGenerator
{
	namespace
	{
		const std::array<std::array<std::pair<glm::vec3, glm::vec2>, 6>, 6> vertices = { {
		   {{
				   // top
				   {{0, 1, 1}, {1, 0}},
				   {{1, 1, 1}, {1, 1}},
				   {{0, 1, 0}, {0, 0}},
				   {{1, 1, 1}, {1, 1}},
				   {{1, 1, 0}, {0, 1}},
				   {{0, 1, 0}, {0, 0}},
				}},
				{{
						// +x east
						{{1, 1, 1}, {1, 0}},
						{{1, 0, 1}, {1, 1}},
						{{1, 1, 0}, {0, 0}},
						{{1, 0, 1}, {1, 1}},
						{{1, 0, 0}, {0, 1}},
						{{1, 1, 0}, {0, 0}},
					 }},
					 {{
							 //-x west
							 {{0, 1, 0}, {1, 0}},
							 {{0, 0, 0}, {1, 1}},
							 {{0, 1, 1}, {0, 0}},
							 {{0, 0, 0}, {1, 1}},
							 {{0, 0, 1}, {0, 1}},
							 {{0, 1, 1}, {0, 0}},
						  }},
						  {{
								  //-z north
								  {{1, 1, 0}, {1, 0}},
								  {{1, 0, 0}, {1, 1}},
								  {{0, 1, 0}, {0, 0}},
								  {{1, 0, 0}, {1, 1}},
								  {{0, 0, 0}, {0, 1}},
								  {{0, 1, 0}, {0, 0}},
							   }},

							   {{
									   // +z south
									   {{0, 1, 1}, {1, 0}},
									   {{0, 0, 1}, {1, 1}},
									   {{1, 1, 1}, {0, 0}},
									   {{0, 0, 1}, {1, 1}},
									   {{1, 0, 1}, {0, 1}},
									   {{1, 1, 1}, {0, 0}},
									}},
									{{
											// bottom
											{{1, 0, 1}, {1, 0}},
											{{0, 0, 1}, {1, 1}},
											{{1, 0, 0}, {0, 0}},
											{{0, 0, 1}, {1, 1}},
											{{0, 0, 0}, {0, 1}},
											{{1, 0, 0}, {0, 0}},
										 }},
									  } };

		const std::array<std::pair<glm::vec3, glm::vec2>, 6>& getFaceVerticesFromDirection(const glm::ivec3& vec) {
			switch (vec.x) {
			case 1:
				return vertices[1];
			case -1:
				return vertices[2];
			default:
				break;
			}

			switch (vec.y) {
			case 1:
				return vertices[0];
			case -1:
				return vertices[5];
			default:
				break;
			}

			switch (vec.z) {
			case 1:
				return vertices[4];
			case -1:
				return vertices[3];
			default:
				break;
			}
		}
	}

	std::vector<BlockVertex> BlockMeshGenerator::generateMesh(const Block& block, const glm::ivec3& direction)
	{
		std::vector<BlockVertex> vertices;

		const std::array<std::pair<glm::vec3, glm::vec2>, 6>& posAndUv = getFaceVerticesFromDirection(direction);

		for (const auto& [pos, uv] : posAndUv)
		{
			vertices.push_back({pos, uv, BlockTexture::getBlockAtlas(block, direction)});
		}

		return vertices;
	}
}