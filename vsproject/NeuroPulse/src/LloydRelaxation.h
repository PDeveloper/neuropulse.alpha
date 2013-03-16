#include <vector>
#include <algorithm>

#include <boost/polygon/point_data.hpp>

#include <boost/polygon/voronoi.hpp>

#include <AdvancedOgreFramework.hpp>

#pragma once
namespace np
{

	template<typename PointType>
	class LloydRelaxation
	{
	public:
	
		LloydRelaxation(void)
		{
		}
	
		~LloydRelaxation(void)
		{
		}
		
		void relax( std::vector<boost::polygon::point_data<PointType>> &points, double minX, double minY, double maxX, double maxY)
		{
			typedef boost::polygon::point_data<PointType> point_type;

			std::vector<point_type> result;
			
			boost::polygon::voronoi_diagram<PointType> vd;
			boost::polygon::construct_voronoi< std::vector<point_type>::iterator, boost::polygon::voronoi_diagram<PointType>>( points.begin(), points.end(), &vd);
			
			int numPoints;
			double ax;
			double ay;

			/*
			int result2 = 0;
			for ( boost::polygon::voronoi_diagram<PointType>::const_vertex_iterator it = vd.vertices().begin();
				it != vd.vertices().end(); ++it)
			{
				const boost::polygon::voronoi_diagram<PointType>::vertex_type &vertex = *it;
				const boost::polygon::voronoi_diagram<PointType>::edge_type *edge = vertex.incident_edge();

				if ( vertex.)

				// This is convenient way to iterate edges around Voronoi vertex.
				do
				{
					edge = edge->rot_next();
				}
				while (edge != vertex.incident_edge());
			}

			*/

			OgreFramework::getSingletonPtr()->m_pLog->logMessage( "HERE I AM YOU MOTHER FUCKER FUCKER FUCKER!!!!!");

			for ( boost::polygon::voronoi_diagram<PointType>::const_cell_iterator it = vd.cells().begin();
				it != vd.cells().end(); ++it)
			{
				const boost::polygon::voronoi_diagram<PointType>::cell_type &cell = *it;

				if ( cell.contains_point())
				{
					const boost::polygon::voronoi_diagram<PointType>::edge_type *edge = cell.incident_edge();

					std::size_t index = it->source_index();

					numPoints = 0;
					ax = 0.0;
					ay = 0.0;

					do
					{
						if ( edge->vertex1() != NULL)
						{
							ax += std::min( std::max( edge->vertex1()->x(), minX), maxX);
							OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (Ogre::Real)edge->vertex1()->x()));
							ay += std::min( std::max( edge->vertex1()->y(), minY), maxY);
							OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (Ogre::Real)edge->vertex1()->y()));
							numPoints++;
						}
						else
						{
							
						}

						edge = edge->next();
					}
					while ( edge != cell.incident_edge());

					//point_type centroid( ax / (double)numPoints, ay / (double)numPoints);

					//result.push_back( centroid);

					points[index].x( ax / (double)numPoints);
					points[index].y( ay / (double)numPoints);
				}
			}
			
			/*for ( int i = 0; i < points.size(); i++)
			{
				points[i] = result[i];
			}*/
		}
	};
}

