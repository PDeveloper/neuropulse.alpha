#pragma once
namespace np
{
	class EventType;
	class Event
	{
	public:

		np::EventType* type;

		Event(np::EventType* type);
		~Event(void);
	};
}
