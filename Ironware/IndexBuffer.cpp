/*!
 * \file IndexBuffer.cpp
 *
 * \author Yernar Aldabergenov
 * \date September 2020
 *
 *
 */
#include "IndexBuffer.h"
#include "GraphicsExceptionMacros.h"

namespace PipelineBindable
{
	IndexBuffer::IndexBuffer( Graphics& gfx, const std::vector<uint16_t>& indices ) :
		count( (UINT)indices.size() )
	{
		INFOMAN( gfx );

		D3D11_BUFFER_DESC descInputBuffer = {};
		descInputBuffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
		descInputBuffer.Usage = D3D11_USAGE_DEFAULT;
		descInputBuffer.CPUAccessFlags = 0u;
		descInputBuffer.MiscFlags = 0u;
		descInputBuffer.ByteWidth = UINT( count * sizeof( uint16_t ) );
		descInputBuffer.StructureByteStride = sizeof( uint16_t );
		D3D11_SUBRESOURCE_DATA subresInputData = {};
		subresInputData.pSysMem = indices.data();
		GFX_CALL_THROW_INFO( GetDevice( gfx )->CreateBuffer( &descInputBuffer, &subresInputData, &pIndexBuffer ) );
	}
}