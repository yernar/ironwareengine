/*!
 * \file Drawable.h
 * \date 2020/09/23 5:49
 *
 * \author Yernar Aldabergenov
 * Contact: yernar.aa@gmail.com
 *
 * \brief A header that contains a drawable class
 *
 * \note It contains: pIndexBuffer, as it's needed to get its count.
 * *				  binds collection that stores various bindable types in it.
*/
#pragma once

#include "Graphics.h"
#include "Bindable.h"
#include "CommonMacros.h"

#include <DirectXMath.h>

#include <memory>

/*!
 * \class Drawable
 *
 * \ingroup Drawables
 *
 * \brief A drawable abstract class that controls(partly) the graphics pipeline and provides
 * * an interface for the other geometry object types
 *
 * \author Yernar Aldabergenov
 *
 * \date September 2020
 *
 * Contact: yernar.aa@gmail.com
 *
 */
class Drawable
{
public:
	Drawable() = default;
	Drawable( const Drawable& ) = delete;
	virtual ~Drawable() = default;

	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	void Draw( Graphics& gfx ) const IFNOEXCEPT;
	Bindable* AddBind( std::shared_ptr<Bindable> bind ) IFNOEXCEPT;

protected:
	/**
	 * @brief Retrieves specified bindable from binds collection
	 * @tparam T required bindable type
	 * @return pointer to the bindable type, if it was found
	*/
	template<typename T>
	T* QueryBindable() const;

protected:
	const class IndexBuffer* pIndexBuffer = nullptr;

private:
	std::vector<std::shared_ptr<Bindable>> binds;
};

template<typename T>
T* Drawable::QueryBindable() const
{
	for( const auto& pb : binds )
	{
		if( auto pT = dynamic_cast<T*>( pb.get() ) )
		{
			return pT;
		}
	}
	return nullptr;
}