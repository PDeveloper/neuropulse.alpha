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

void np::WorldGenerator::generateWorld( np::NeuroWorld* neuroWorld)
{
	np::NeuroWorldSettings* settings = neuroWorld->settings;
	np::GameObjectFactory* factory = neuroWorld->gameObjectFactory;

	Ogre::Light* directionalLight = factory->createLight( "SunLight");
	Ogre::Entity* entGround = factory->createGround();
	
	int numNodes = settings->numberOfNodes;

	boost::random::mt19937 mt;
	boost::random::uniform_real_distribution<double> distribution;

	struct point2d {
		float	x, y;
	};

	int numPoints = 0;
	point2d *vertices = new point2d[numNodes];
	ac::es::EntityPtr *nodes = new ac::es::EntityPtr[numNodes];

	double ax = 0.0;
	double ay = 0.0;

	for ( int i = 0; i < numNodes; i++)
	{
		vertices[i].x = distribution( mt) * 600 - 300;
		vertices[i].y = distribution( mt) * 600 - 300;
		//distribution( mt);
		//distribution( mt);

		ax += vertices[i].x;
		ay += vertices[i].y;
	}

	ax = ax / numNodes;
	ay = ay / numNodes;

	for ( int i = 0; i < 8; i++)
	{
		for ( int j = 0; j < numNodes; j++)
		{
			double vx = 0.0;
			double vy = 0.0;
			double dx = 0.0;
			double dy = 0.0;

			for ( int k = 0; k < numNodes; k++)
			{
				if ( j == k) continue;

				dx = ( vertices[j].x - vertices[k].x);
				dy = ( vertices[j].y - vertices[k].y);
				vx += 1 / ( dx * dx);
				vy += 1 / ( dy * dy);
			}

			vertices[j].x += vx * 1000;
			vertices[j].y += vy * 1000;
		}
	}

	for ( int i = 0; i < numNodes; i++)
	{
		double rOutput = 0.0;

		if ( i == 0) rOutput = 60.0;

		nodes[i] = factory->createNodeEntity( vertices[i].x, vertices[i].y, rOutput, distribution( mt) * 100 + 60);
		neuroWorld->nodes.push_back( nodes[i]);
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
				np::ConnectionBase* base1 = new np::ConnectionBase( e1);
				np::ConnectionBase* base2 = new np::ConnectionBase( e2);
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

void np::WorldGenerator::generateWorld2( np::NeuroWorld* neuroWorld)
{
	np::NeuroWorldSettings* settings = neuroWorld->settings;
	np::GameObjectFactory* factory = neuroWorld->gameObjectFactory;

	int numNodes = settings->numberOfNodes;
	
	ac::es::EntityPtr *nodes = new ac::es::EntityPtr[numNodes];
	
	std::vector<Ogre::Vector2> positions;

	nodes[0] = factory->createNodeEntity( 0, 0, 60.0, 100.0);

	positions.push_back( Ogre::Vector2( 0, 0));

	for ( int i = 1; i < numNodes; i++)
	{
		double rads = ( double(i) / double(numNodes)) * M_PI * 2.0;

		positions.push_back( Ogre::Vector2( 300 * std::cos( rads), 300 * std::sin( rads)));

		nodes[i] = factory->createNodeEntity( positions.back().x, positions.back().y, 0.0, 100.0);
	}

	for ( int i = 1; i < numNodes; i++)
	{
		ac::es::EntityPtr e1 = nodes[0];
		ac::es::EntityPtr e2 = nodes[i];

		np::NodeComponent* node1		= e1->getComponent<np::NodeComponent>();
		np::TransformComponent* transform1 = e1->getComponent<np::TransformComponent>();
		np::OutputComponent* output1	= e1->getComponent<np::OutputComponent>();

		np::NodeComponent* node2		= e2->getComponent<np::NodeComponent>();
		np::TransformComponent* transform2 = e2->getComponent<np::TransformComponent>();
		np::OutputComponent* output2	= e2->getComponent<np::OutputComponent>();

		np::ConnectionBase* base1 = new np::ConnectionBase( e1);
		np::ConnectionBase* base2 = new np::ConnectionBase( e2);
		base1->connect( base2);

		output1->addConnection( base1);
		output2->addConnection( base2);

		factory->createConnectionEntity( transform1, transform2);
	}

	for ( int i = 1; i < numNodes; i++)
	{
		ac::es::EntityPtr e1 = nodes[i];
		ac::es::EntityPtr e2;
		if ( i < numNodes - 1) e2 = nodes[i + 1];
		else e2 = nodes[1];

		np::NodeComponent* node1		= e1->getComponent<np::NodeComponent>();
		np::TransformComponent* transform1 = e1->getComponent<np::TransformComponent>();
		np::OutputComponent* output1	= e1->getComponent<np::OutputComponent>();

		np::NodeComponent* node2		= e2->getComponent<np::NodeComponent>();
		np::TransformComponent* transform2 = e2->getComponent<np::TransformComponent>();
		np::OutputComponent* output2	= e2->getComponent<np::OutputComponent>();

		np::ConnectionBase* base1 = new np::ConnectionBase( e1);
		np::ConnectionBase* base2 = new np::ConnectionBase( e2);
		base1->connect( base2);

		output1->addConnection( base1);
		output2->addConnection( base2);

		factory->createConnectionEntity( transform1, transform2);
	}
}