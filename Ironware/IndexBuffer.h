/*!
 * \file IndexBuffer.h
 * \date 2020/09/23 5:19
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A header that contains a (bindable) indexbuffer class
 *
*/
#pragma once

#include "Bindable.h"
#include "BindableCollection.h"
#include "IronUtils.h"

/*!
 * \class IndexBuffer
 *
 * \ingroup Bindables
 *
 * \brief An IndexBuffer wrapper class that will be bound in process of graphics pipeline
 * * and store vertex indices in it.
 *
 * \author Yernar Aldabergenov
 *
 * \date September 2020
 *
 * Contact: yernar.aa@gmail.com
 *
 */
class IndexBuffer : public Bindable
{
public:
	IndexBuffer( Graphics& gfx, const std::vector<uint16_t>& indices );
	IndexBuffer( Graphics& gfx, const std::wstring& tag, const std::vector<uint16_t>& indices );

	void Bind( Graphics& gfx ) IFNOEXCEPT override { GetContext( gfx )->IASetIndexBuffer( pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u ); }
	UINT GetCount() const noexcept { return count; }
	static std::shared_ptr<IndexBuffer> Resolve( Graphics& gfx, const std::wstring& tag, const std::vector<uint16_t>& indices );
	std::wstring GetUID() const noexcept override { return GenerateUID_( tag ); }

	template<TPACK Ignore>
	static std::wstring GenerateUID( const std::wstring& tag, Ignore&&... ignore )
	{
		return GenerateUID_( tag );
	}

private:
	static std::wstring GenerateUID_( const std::wstring& tag ) noexcept { return GET_CLASS_WNAME( IndexBuffer ) + L"#" + tag; }

protected:
	std::wstring tag;
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};

