/*
 * =====================================================================================
 *
 *       Filename:  RenderTarget.cpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 19:55:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "IDrawable.hpp"
#include "RenderTarget.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"

void RenderTarget::draw(const IDrawable &drawable, const RenderStates &states) {
	drawable.draw(*this, states);
}

void RenderTarget::draw(const VertexBuffer &vertexBuffer, const RenderStates &states) {
	draw(vertexBuffer, vertexBuffer.first(), vertexBuffer.count(), states);
}

void RenderTarget::draw(const VertexBuffer &vertexBuffer, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states) {
	if (!states.shader) return;

	Shader::bind(states.shader);

	VertexBuffer::bind(&vertexBuffer);

	states.shader->setUniform("u_projectionMatrix", (states.projectionMatrix) ? *states.projectionMatrix : glm::mat4{1});
	states.shader->setUniform("u_modelMatrix", (states.modelMatrix) ? *states.modelMatrix : glm::mat4{1});
	states.shader->setUniform("u_viewMatrix", (states.viewMatrix) ? *states.viewMatrix : glm::mat4{1});

	states.shader->enableVertexAttribArray("coord3d");

	glVertexAttribPointer(states.shader->attrib("coord3d"), 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (states.texture)
		Texture::bind(states.texture);

	glDrawArrays(vertexBuffer.mode(), firstVertex, vertexCount);

	Texture::bind(nullptr);

	states.shader->disableVertexAttribArray("coord3d");

	VertexBuffer::bind(nullptr);

	Shader::bind(nullptr);
}
