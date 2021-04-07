/*!
 * \file PointLight.h
 * \date 2020/11/11 5:09
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A class that represents point light that can be set into the scene
 *
 * TODO:
 *
 * \note It uses sphere as its mesh but you can change by changing some code
*/
#pragma once

#include "Graphics.h"
#include "SolidSphere.h"
#include "ConstantBuffers.h"
#include "CommonMacros.h"

class PointLight
{
public:
	PointLight( Graphics& gfx, float radius = 0.5f );
	void SpawnControlWindow() noexcept;
	void Draw( Graphics& gfx ) const IFNOEXCEPT;
	void Bind( Graphics& gfx, DirectX::FXMMATRIX view ) const noexcept;
	void Reset() noexcept;

private:
	struct PointLightCBuf
	{
		// GPU expects 16 byte val
		DirectX::XMFLOAT3A pos;
		DirectX::XMFLOAT3A ambient;
		DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};

private:
	PointLightCBuf cbufData;
	mutable SolidSphere mesh;
	mutable PixelConstantBuffer<PointLightCBuf> cbuffer;
};