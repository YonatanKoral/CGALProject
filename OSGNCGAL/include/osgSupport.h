#pragma once
#include <osg/Object>
namespace osg
{
	template<typename T, typename From>
	ref_ptr<T> cast_ref(const From *from)
	{
		ref_ptr<T> t = dynamic_cast<T*>(from);
		return t;
	}


	template<typename T, typename From>
	ref_ptr<T> cast_ref(ref_ptr<From> from)
	{
		ref_ptr<T> t = dynamic_cast<T*>(from.get());
		return t;
	}

	template<typename T,typename ... Arg>
	ref_ptr<T> make_ref(Arg&& ... arg)
	{
		ref_ptr<T> t = new T(std::forward<Arg>(arg)...);
		return t;
	}
}