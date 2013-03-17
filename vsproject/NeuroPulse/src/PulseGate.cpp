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
			output->target->putBuffer(pulse->getResource(output->resourceType, output->getBufferFreeSpace()));
		}
	}
}

void np::PulseGate::outPulse(np::Pulse* pulse)
{
	if(isConnected)
	{
		if(mode == MODE_INPUT)
		{
			std::list<np::ResourcePacket*>::iterator i;

			for(i = input->buffer.begin(); i != input->buffer.end(); ++i)
			{
				pulse->addPacket((*i));

				i = input->buffer.erase(i);
			}
		}
		else if(mode == MODE_OUTPUT)
		{
			//Take, put directly into the input
			output->target->putBuffer( pulse->getResource( output->resourceType, output->getBufferFreeSpace()));
		}
	}
}

void np::PulseGate::connect(ConstructInput* input)
{
	mode = MODE_OUTPUT;

	output = new ConstructOutput(input->resourceType, input->maxBufferSize);

	output->connect(input);

	isConnected = true;
}

void np::PulseGate::connect(ConstructOutput* output)
{
	mode = MODE_INPUT;

	input = new ConstructInput(output->resourceType, output->maxBufferSize);

	input->connect(output);

	isConnected = true;
}

void np::PulseGate::disconnect()
{
	if(mode == MODE_INPUT)
	{
		output->disconnect();	

		delete output;

	}
	else if(mode == MODE_OUTPUT)
	{
		input->disconnect();

		delete input;
	}

	isConnected = false;
}
