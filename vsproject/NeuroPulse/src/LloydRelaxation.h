#pragma once
#include <vector>
#include <algorithm>

#include <boost/polygon/point_data.hpp>

#include <boost/polygon/voronoi.hpp>

#include <AdvancedOgreFramework.hpp>
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

			OgreFramework::getSingletonPtr()->m_pLog->logMessage( "STARTING VORONOI RELAXTION YOOO!");

			for ( boost::polygon::voronoi_diagram<PointType>::const_cell_iterator it = vd.cells().begin();
				it != vd.cells().end(); ++it)
			{
				OgreFramework::getSingletonPtr()->m_pLog->logMessage("CELL");
				const boost::polygon::voronoi_diagram<PointType>::cell_type &cell = *it;

				if ( cell.contains_point())
				{
					const boost::polygon::voronoi_diagram<PointType>::edge_type *edge = cell.incident_edge();
					
					const boost::polygon::voronoi_diagram<PointType>::edge_type *prev;
					const boost::polygon::voronoi_diagram<PointType>::edge_type *next;

					std::size_t index = cell.source_index();

					numPoints = 0;
					ax = 0.0;
					ay = 0.0;

					do
					{
						//if ( edge->is_primary())
						//{
							double cx, cy;
							double vx, vy;
							double bx, by;
							double t1, t2, t;

							if ( edge->is_finite())
							{
								cx = edge->vertex0()->x();
								cy = edge->vertex0()->y();
								/*
								OgreFramework::getSingletonPtr()->m_pLog->logMessage("finite");
								OgreFramework::getSingletonPtr()->m_pLog->logMessage(
									Ogre::StringConverter::toString((float)(cx)) +
									" : " +
									Ogre::StringConverter::toString((float)(cy))
									);
									*/
								if ( isPointWithin( cx, cy, minX, minY, maxX, maxY))
								{
									ax += cx;
									ay += cy;
									numPoints++;
								}
								else
								{
									prev = edge->prev();
									next = edge->next();

									if ( !prev->is_infinite())
									{
										double px, py;
										px = prev->vertex0()->x();
										py = prev->vertex0()->y();

										if ( isPointWithin( px, py, minX, minY, maxX, maxY))
										{
											vx = cx - px;
											vy = cy - py;

											if ( vx < 0) bx = minX - px;
											else if ( vx > 0) bx = maxX - px;
											else bx = 0.0;

											if ( vy < 0) by = minY - py;
											else if ( vy > 0) by = maxY - py;
											else by = 0.0;

											t1 = bx / vx;
											t2 = by / vy;

											if ( t1 <= t2) t = t1;
											else t = t2;

											ax += px + t * vx;
											ay += py + t * vy;
											numPoints++;
										}
									}

									if ( !next->is_infinite())
									{
										double nx, ny;
										nx = next->vertex0()->x();
										ny = next->vertex0()->y();

										if ( isPointWithin( nx, ny, minX, minY, maxX, maxY))
										{
											vx = cx - nx;
											vy = cy - ny;

											if ( vx < 0) bx = minX - nx;
											else if ( vx > 0) bx = maxX - nx;
											else bx = 0.0;

											if ( vy < 0) by = minY - ny;
											else if ( vy > 0) by = maxY - ny;
											else by = 0.0;

											t1 = bx / vx;
											t2 = by / vy;

											if ( t1 <= t2) t = t1;
											else t = t2;

											ax += nx + t * vx;
											ay += ny + t * vy;
											numPoints++;
										}
									}
								}
							}
							else
							{
								if ( edge->vertex0() != NULL)
								{
									cx = edge->vertex0()->x();
									cy = edge->vertex0()->y();

									if ( isPointWithin( cx, cy, minX, minY, maxX, maxY))
									{
										ax += cx;
										ay += cy;
										numPoints++;

										point_type p0 = points[ edge->cell()->source_index()];
										point_type p1 = points[ edge->twin()->cell()->source_index()];

										vx = p0.y() - p1.y();
										vy = p1.x() - p0.x();

										if ( vx < 0) bx = minX - cx;
										else if ( vx > 0) bx = maxX - cx;
										else bx = 0.0;

										if ( vy < 0) by = minY - cy;
										else if ( vy > 0) by = maxY - cy;
										else by = 0.0;

										t1 = bx / vx;
										t2 = by / vy;

										if ( t1 <= t2) t = t1;
										else t = t2;
										/*
										OgreFramework::getSingletonPtr()->m_pLog->logMessage("vertex1 was infinite");
										OgreFramework::getSingletonPtr()->m_pLog->logMessage(
											Ogre::StringConverter::toString((float)(cx + t * vx)) +
											" : " +
											Ogre::StringConverter::toString((float)(cy + t * vy))
											);
											*/
										ax += cx + t * vx;
										ay += cy + t * vy;
										numPoints++;
									}
								}
								else if ( edge->vertex1() != NULL)
								{
									cx = edge->vertex1()->x();
									cy = edge->vertex1()->y();

									if ( isPointWithin( cx, cy, minX, minY, maxX, maxY))
									{
										point_type p0 = points[ edge->cell()->source_index()];
										point_type p1 = points[ edge->twin()->cell()->source_index()];

										vx = p1.y() - p0.y();
										vy = p0.x() - p1.x();

										if ( vx < 0) bx = minX - cx;
										else if ( vx > 0) bx = maxX - cx;
										else bx = 0.0;

										if ( vy < 0) by = minY - cy;
										else if ( vy > 0) by = maxY - cy;
										else by = 0.0;

										t1 = bx / vx;
										t2 = by / vy;

										if ( t1 <= t2) t = t1;
										else t = t2;
										/*
										OgreFramework::getSingletonPtr()->m_pLog->logMessage("vertex0 was infinite");
										OgreFramework::getSingletonPtr()->m_pLog->logMessage(
											Ogre::StringConverter::toString((float)(cx + t * vx)) +
											" : " +
											Ogre::StringConverter::toString((float)(cy + t * vy))
											);
											*/
										ax += cx + t * vx;
										ay += cy + t * vy;
										numPoints++;
									}
								}
							//}
						}

						edge = edge->next();
					}
					while ( edge != cell.incident_edge());

					if ( (float)points[index].x() > 300 || (float)points[index].y() > 300)
					{
						OgreFramework::getSingletonPtr()->m_pLog->logMessage("previous centroid:");
						OgreFramework::getSingletonPtr()->m_pLog->logMessage(
							Ogre::StringConverter::toString( (float)points[index].x()));
						OgreFramework::getSingletonPtr()->m_pLog->logMessage(
							Ogre::StringConverter::toString( (float)points[index].y()));
					}

					if ( numPoints > 0)
					{
						points[index].x( ax / (double)numPoints);
						points[index].y( ay / (double)numPoints);
					}

					if ( (float)points[index].x() > 300 || (float)points[index].y() > 300)
					{
						OgreFramework::getSingletonPtr()->m_pLog->logMessage("centroid:");
						OgreFramework::getSingletonPtr()->m_pLog->logMessage(
							Ogre::StringConverter::toString( (float)points[index].x()));
						OgreFramework::getSingletonPtr()->m_pLog->logMessage(
							Ogre::StringConverter::toString( (float)points[index].y()));
					}
				}
			} // end of for loop
		}

	private:
		bool isPointWithin( double x, double y, double minX, double minY, double maxX, double maxY)
		{
			return ( x >= minX && x <= maxX && y >= minY && y <= maxY);
		}
	};
}

