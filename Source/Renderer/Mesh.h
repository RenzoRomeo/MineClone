#pragma once

#include "../core.h"
#include "../OpenGL/Vao.h"
#include "../OpenGL/Ebo.h"

struct Mesh
{
	std::shared_ptr<Vao> vao;
	uint32_t numVertices;

	Mesh(std::shared_ptr<Vao> vao, uint32_t numVertices) : vao(vao), numVertices(numVertices) {};
};