#pragma once

#include "../core.h"
#include "../OpenGL/Vao.h"
#include "../OpenGL/Ebo.h"

struct Mesh
{
	std::shared_ptr<Vao> vao = nullptr;
	std::shared_ptr<Vbo> vbo = nullptr;
	uint32_t numVertices  = 0;

	Mesh() = default;
	Mesh(std::shared_ptr<Vao> vao, std::shared_ptr<Vbo> vbo, uint32_t numVertices) : vao(vao), vbo(vbo), numVertices(numVertices) {};
};