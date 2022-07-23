#pragma once

enum BlockType
{
	Air,
	Dirt,
	Wood
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