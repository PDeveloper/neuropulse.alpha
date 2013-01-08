#include "WorldGenerator.h"

#include <OutputComponent.h>
#include <ConnectionBase.h>

#include <ac\es.h>
#include <OgreProcedural\Procedural.h>

#include <vector>
#include <boost\random\uniform_real_distribution.hpp>
#include <boost\random\mersenne_twister.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <delaunay.h>

#include <AdvancedOgreFramework.hpp>

np::WorldGenerator::WorldGenerator(void)
{
}


np::WorldGenerator::~WorldGenerator(void)
{
}

void np::WorldGenerator::generateWorld( np::GameObjectFactory* factory, const int numNodes)
{
	boost::random::mt19937 mt;
	boost::random::uniform_real_distribution<double> distribution;
	
	struct point2d {
		float	x, y;
	};

	int numPoints = 0;
	point2d *vertices = new point2d[numNodes];
	ac::es::EntityPtr *nodes = new ac::es::EntityPtr[numNodes];

	for ( int i = 0; i < numNodes; i++)
	{
		vertices[i].x = distribution( mt) * 600 - 300;
		vertices[i].y = distribution( mt) * 600 - 300;
		distribution( mt);
		double rOutput = 0.0;
		if ( i == 0) rOutput = 0.5;

		nodes[i] = factory->createNodeEntity( vertices[i].x, vertices[i].y, rOutput, distribution( mt) * 80 + 60);
		if ( i == 0) nodes[i]->getComponent<TransformComponent>()->position.y = 15;
	}

	int *faces = NULL;
	int numFaces = delaunay2d( (float*)vertices, numNodes, &faces);

	int offset = 0;

	for ( int i = 0; i < numFaces; i++)
	{
		int numVerts = faces[offset];
		offset++;

		for( int j = 0; j < numVerts; j++ )
		{
			int p0 = faces[offset + j];
			int p1 = faces[offset + ( j + 1) % numVerts];

			ac::es::EntityPtr e1 = nodes[p0];
			ac::es::EntityPtr e2 = nodes[p1];

			np::NodeComponent* node1		= e1->getComponent<np::NodeComponent>();
			np::TransformComponent* transform1 = e1->getComponent<np::TransformComponent>();
			np::OutputComponent* output1	= e1->getComponent<np::OutputComponent>();

			np::NodeComponent* node2		= e2->getComponent<np::NodeComponent>();
			np::TransformComponent* transform2 = e2->getComponent<np::TransformComponent>();
			np::OutputComponent* output2	= e2->getComponent<np::OutputComponent>();

			if ( !output1->hasConnection( node2))
			{
				np::ConnectionBase* base1 = new np::ConnectionBase( node1);
				np::ConnectionBase* base2 = new np::ConnectionBase( node2);
				base1->connect( base2);

				output1->addConnection( base1);
				output2->addConnection( base2);

				factory->createConnectionEntity( transform1, transform2);
			}
		}

		offset += numVerts;
	}

	// clean up!
	delete vertices;
	delete faces;
	delete nodes;
}