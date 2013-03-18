#include <ac/es.h>
#include <list>
#include <limits>

#include <ResourcePacket.h>
#include <ResourceRequirement.h>

#pragma once
namespace np
{

	enum TransferSuccess
	{
		TYPE_CONFLICT,
		PARTIAL,
		FULL
	};

	class BufferComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(BufferComponent)
	public:

		np::ResourceRequirement& getTypes();
		double getSpaceLeft( np::ResourceType* type);
		double getNormalSpaceLeft();

		bool isEmpty();

		np::TransferSuccess addPacket( np::ResourcePacket* packet);
		np::TransferSuccess addPackets( std::list<np::ResourcePacket*>* packets);

		np::ResourcePacket* getPacket( np::ResourceType* type, double amount);
		np::ResourcePacket* getPacket( np::ResourceType* type);
		np::ResourcePacket* getPacket();

		np::ResourcePacket* getNextPacketOf( const np::ResourceRequirement* requirements);

		std::list<np::ResourcePacket*> getPackets( double amount, const np::ResourceRequirement* requirements);
		std::list<np::ResourcePacket*> getPackets( double amount);
		std::list<np::ResourcePacket*> getPackets();
		std::list<np::ResourcePacket*> getPackets( const np::ResourceRequirement* requirements);

		double getAmountOf( np::ResourceType* type);

		BufferComponent( np::ResourceRequirement types, double size = std::numeric_limits<double>::infinity());
		~BufferComponent(void);
		np::TransferSuccess appendPacket( np::ResourcePacket* packet );
	private:
		double totalSpace;
		np::ResourceRequirement types;
		std::list<np::ResourcePacket*> buffer;
	};
}
