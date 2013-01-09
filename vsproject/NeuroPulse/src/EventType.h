#include <string>

#pragma once
namespace np
{
	class EventManager;
	class EventType
	{
	public:

		size_t id;

		EventType( size_t id);
		~EventType(void);
	};
}
