/**
 * @file   BaseStructure.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class interface
 */

#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <Engine2D/TiledMap/BasicBlock.hpp>

namespace Structures {

	/**
	* @short Class BaseStructure, all structures use this parent class
	*/
	class BaseStructure
	{
		protected:

			/** @short Vector of data structure info */
			std::vector< std::vector<unsigned int> > _data;

			/** @short Vector of collisinable object */
			std::vector<TiledMap::BasicBlock> _vectorCollisionables;

			/** @short Width of structure */
			unsigned int _width;

			/** @short Height of structure */
			unsigned int _height;

		public:

			/** @short Creates a new base structure */
		    BaseStructure();

		    /** @short Delete a base structure */
		    ~BaseStructure();

			/** @short Get the width of structure */
		    unsigned int getWidth() const;

		    /** @short Get the height of structure */
		    unsigned int getHeight() const;

		    /** @short Get the data info of structure */
		    std::vector< std::vector<unsigned int> > getData() const;

			/** @short Get the data of the collisionable vector */
			std::vector< TiledMap::BasicBlock > getCollisionableVector() const;

		    /** @short Get the info of a position in structure */
            unsigned int getDataAt(const unsigned int row, const unsigned int column) const;

			/** @short Convert this class in a string */
			std::string toString() const;
	};
}
