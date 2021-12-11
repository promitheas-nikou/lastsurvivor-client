#pragma once
template<typename C>
class Reflection
{
public:
	template<typename ...CtorParams>
	inline C* MakeInstance(CtorParams... params);

	template<typename I>
	void Init(I& data);
};

template<typename C>
template<typename ...CtorParams>
inline C* Reflection<C>::MakeInstance(CtorParams... params)
{
	return new C(params...);
}

template<typename C>
template<typename I>
void Reflection<C>::Init(I& data)
{
	C::Init(data);
}

