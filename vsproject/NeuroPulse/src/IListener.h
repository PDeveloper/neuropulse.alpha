#pragma once
namespace np
{
	template <typename T>
	class IListener
	{
	public:

		virtual void dispatchListener( T& param);

	};
}
