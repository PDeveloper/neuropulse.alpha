#include <vector>

#pragma once
namespace np
{
	class ComponentProperty;

	class ComponentInterface
	{
	public:

		std::vector<ComponentProperty*>* properties; 

		ComponentInterface()
		{
		  properties = new std::vector<ComponentProperty*>();
		}

		void addProperty(ComponentProperty* property)
		{
			properties->push_back(property);
		}
		

	private:
		

	};
}