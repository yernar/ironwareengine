/*!
 * \file Mesh.h
 *
 * \author Yernar Aldabergenov
 * \date May 2021
 *
 *
 */
#pragma once

#include "Graphics.h"
#include "Drawable.h"

class Material;

class Mesh : public Drawable
{
public:
	Mesh( Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.f ) IFNOEXCEPT;
	void Submit( size_t channelFilter, DirectX::FXMMATRIX accumulatedTransform ) const IFNOEXCEPT;
	DirectX::XMMATRIX GetTransformXM() const noexcept override { return DirectX::XMLoadFloat4x4( &transform ); }

private:
	mutable DirectX::XMFLOAT4X4 transform = {};
};