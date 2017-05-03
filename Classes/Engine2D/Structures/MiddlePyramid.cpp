/**
 * @file   MiddlePyramid.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  MiddlePyramid class implementation
 */

#include "MiddlePyramid.hpp"

/** 
* @brief Creates a middle pyramid structure with a random height
*/
Structures::
MiddlePyramid::MiddlePyramid() : Structures::BaseStructure() 
{
	/*this->_height = K_DEFAULT_WIDTH;
	this->_width = this->_height;
	this->_data.resize(this->_height);
	unsigned int j, startInRow= this->_height-1;
	this->_vectorCollisionables.resize(this->_height);

	for(int i=_height-1; i>=0; --i) {

		this->_data[i].resize(this->_width, false);
		for(j=startInRow; j<this->_width; ++j) {
			if(j==startInRow || j==this->_width-1){
				this->_data[i][j] = 1;
			}
			else{
				this->_data[i][j] = 5;
			}

		}

		--startInRow;
	}*/
    
    this->_width=K_DEFAULT_WIDTH;
    this->_height = 2;
    this->_data.resize(this->_height);
    this->_vectorCollisionables.resize(this->_width);
    for(int i=_height-1; i>=0; --i) {
        this->_data[i].resize(this->_width, false);
    }
    this->_data[0][0]=1;
    this->_data[0][1]=1;
    this->_data[0][2]=5;
    
    this->_data[1][0]=0;
    this->_data[1][1]=0;
    this->_data[1][2]=1;
}
Structures::
MiddlePyramid::MiddlePyramid(unsigned short int width) : Structures::BaseStructure()
{
    if(width%2==0){
        this->_width=width-1;
    }else{
        this->_width=width;
    }
  
    if(this->_width==3){
        this->_height = 2;
        this->_data.resize(this->_height);
        this->_vectorCollisionables.resize(this->_width);
        for(int i=_height-1; i>=0; --i) {
            this->_data[i].resize(this->_width, false);
        }
        this->_data[0][0]=1;
        this->_data[0][1]=1;
        this->_data[0][2]=5;
        
        this->_data[1][0]=0;
        this->_data[1][1]=0;
        this->_data[1][2]=1;
        
    }
    if(this->_width==5){
        this->_height = 3;
        this->_data.resize(this->_height);
        this->_vectorCollisionables.resize(this->_width);
        for(int i=_height-1; i>=0; --i) {
            this->_data[i].resize(this->_width, false);
        }
        this->_data[0][0]=1;
        this->_data[0][1]=1;
        this->_data[0][2]=5;
        this->_data[0][3]=5;
        this->_data[0][4]=5;
        
        this->_data[1][0]=0;
        this->_data[1][1]=0;
        this->_data[1][2]=1;
        this->_data[1][3]=1;
        this->_data[1][4]=5;
        
        this->_data[2][0]=0;
        this->_data[2][1]=0;
        this->_data[2][2]=0;
        this->_data[2][3]=0;
        this->_data[2][4]=1;
        
        
    }
    
    if(this->_width==7){
        this->_height = 4;
        this->_data.resize(this->_height);
        this->_vectorCollisionables.resize(this->_width);
        for(int i=_height-1; i>=0; --i) {
            this->_data[i].resize(this->_width, false);
        }
        this->_data[0][0]=1;
        this->_data[0][1]=1;
        this->_data[0][2]=5;
        this->_data[0][3]=5;
        this->_data[0][4]=5;
        this->_data[0][5]=5;
        this->_data[0][6]=5;
        
        this->_data[1][0]=0;
        this->_data[1][1]=0;
        this->_data[1][2]=1;
        this->_data[1][3]=1;
        this->_data[1][4]=5;
        this->_data[1][5]=5;
        this->_data[1][6]=5;
        
        
        this->_data[2][0]=0;
        this->_data[2][1]=0;
        this->_data[2][2]=0;
        this->_data[2][3]=0;
        this->_data[2][4]=1;
        this->_data[2][5]=1;
        this->_data[2][6]=5;
        
        this->_data[3][0]=0;
        this->_data[3][1]=0;
        this->_data[3][2]=0;
        this->_data[3][3]=0;
        this->_data[3][4]=0;
        this->_data[3][5]=0;
        this->_data[3][6]=1;
        
    }
    
    if(this->_width==9){
        this->_height = 5;
        this->_data.resize(this->_height);
        this->_vectorCollisionables.resize(this->_width);
        for(int i=_height-1; i>=0; --i) {
            this->_data[i].resize(this->_width, false);
        }
        this->_data[0][0]=1;
        this->_data[0][1]=1;
        this->_data[0][2]=5;
        this->_data[0][3]=5;
        this->_data[0][4]=5;
        this->_data[0][5]=5;
        this->_data[0][6]=5;
        this->_data[0][7]=5;
        this->_data[0][8]=5;
        
        this->_data[1][0]=0;
        this->_data[1][1]=0;
        this->_data[1][2]=1;
        this->_data[1][3]=1;
        this->_data[1][4]=5;
        this->_data[1][5]=5;
        this->_data[1][6]=5;
        this->_data[1][7]=5;
        this->_data[1][8]=5;
        
        this->_data[2][0]=0;
        this->_data[2][1]=0;
        this->_data[2][2]=0;
        this->_data[2][3]=0;
        this->_data[2][4]=1;
        this->_data[2][5]=1;
        this->_data[2][6]=5;
        this->_data[2][7]=5;
        this->_data[2][8]=5;
        
        this->_data[3][0]=0;
        this->_data[3][1]=0;
        this->_data[3][2]=0;
        this->_data[3][3]=0;
        this->_data[3][4]=0;
        this->_data[3][5]=0;
        this->_data[3][6]=1;
        this->_data[3][7]=1;
        this->_data[3][8]=5;
        
        this->_data[4][0]=0;
        this->_data[4][1]=0;
        this->_data[4][2]=0;
        this->_data[4][3]=0;
        this->_data[4][4]=0;
        this->_data[4][5]=0;
        this->_data[4][6]=0;
        this->_data[4][7]=0;
        this->_data[4][8]=1;
        
        
        
    }
	/*this->_height = width;
	this->_width = this->_height;
	this->_data.resize(this->_height);
	unsigned int j, startInRow= this->_height-1;
	this->_vectorCollisionables.resize(this->_height);

	for(int i=_height-1; i>=0; --i) {

		this->_data[i].resize(this->_width, false);
		for(j=startInRow; j<this->_width; ++j) {
			if(j==startInRow || j==this->_width-1){
				this->_data[i][j] = 1;
			}
			else{
				this->_data[i][j] = 5;
			}
		}

		--startInRow;
	}*/
    
}
