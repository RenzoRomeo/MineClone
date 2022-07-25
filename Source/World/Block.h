#pragma once

enum BlockType
{
	Air,
	Dirt,
	Grass,
	Wood,
	Planks,
	Stone,
};

struct Block
{
	Block()
		: type(BlockType::Dirt), solid(true) {}

	Block(BlockType type, bool solid)
		: type(type), solid(solid) {}

	BlockType type;
	bool solid;
};