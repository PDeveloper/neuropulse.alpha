

#pragma once
namespace np
{

	class ConstructInput;

	class ConstructOutput
	{
	public:

		np::ConstructInput* input;

		ConstructOutput(void);
		~ConstructOutput(void);
	};
}