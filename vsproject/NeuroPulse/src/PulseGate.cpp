#include "PulseGate.h"
#include "ConstructComponent.h"
#include "Construct.h"

void np::PulseGate::inPulse(np::Pulse* pulse)
{
	if(isConnected)
	{
		if(mode == MODE_INPUT)
		{
			//Probably not do anything
		}
		else if(mode == MODE_OUTPUT)
		{
			//Take, put directly into the input
		}
	}
}

void np::PulseGate::outPulse(np::Pulse* pulse)
{
	if(isConnected)
	{
		if(mode == MODE_INPUT)
		{
			for(int i=0; i<constructInput->buffer.size(); i++)
			{
				//add to pulse constructInput->buffer.at(i);
				constructInput->buffer.empty();
			}
		}
		else if(mode == MODE_OUTPUT)
		{
			//Take, put directly into the input
		}
	}
}

void np::PulseGate::connect(ConstructInput* input)
{
	mode = MODE_OUTPUT;

	constructOutput = new ConstructOutput(input->resourceType, input->maxBufferSize);

	constructOutput->connect(input);

	isConnected = true;
}

void np::PulseGate::connect(ConstructOutput* output)
{
	mode = MODE_INPUT;

	constructInput = new ConstructInput(output->resourceType, output->maxBufferSize);

	constructInput->connect(output);

	isConnected = true;
}

void np::PulseGate::disconnect()
{
	if(mode == MODE_INPUT)
	{
		constructOutput->disconnect();	

		delete constructOutput;

	}
	else if(mode == MODE_OUTPUT)
	{
		constructInput->disconnect();

		delete constructInput;
	}

	isConnected = false;
}
