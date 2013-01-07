#include "WorldGenerator.h"

#include <TransformComponent.h>

#include <ac\es.h>
#include <OgreProcedural\Procedural.h>

#include <vector>
#include <boost\random.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

np::WorldGenerator::WorldGenerator(void)
{
}


np::WorldGenerator::~WorldGenerator(void)
{
}

void np::WorldGenerator::generateWorld( np::GameObjectFactory* factory)
{
	int numNodes = 9;

	std::vector< Ogre::Vector2> positions;

	positions.push_back( Ogre::Vector2( 0, 0));

	for ( int i = 0; i < numNodes - 1; i++)
	{
		double rads = ( double(i) / double(numNodes)) * M_PI * 2.0;

		positions.push_back( Ogre::Vector2( 300 * std::cos( rads), 300 * std::sin( rads)));
	}

	for ( int i = 0; i < numNodes; i++)
	{
		ac::es::EntityPtr node = factory->createNodeEntity( positions.at(i).x, positions.at(i).y, std::max<double>( 0.0, std::sin( double( i * 63.49))), 100.0);
	}
}