//
// Created by Pablo Ramon on 20/3/17.
//

#include "GapStructure.hpp"

/**
* @brief Creates a middle pyramid structure with a random height
*/
Structures::
GapStructure::GapStructure() : Structures::BaseStructure()
{
    int width=K_DEFAULT_WIDTH;
    int minJump=K_DEFAULT_MIN_JUMP;
    int maxJump=K_DEFAULT_MAX_JUMP;
    int minRest=K_DEFAULT_MIN_REST;
    int maxRest=K_DEFAULT_MAX_REST;

    this->_height = 1;
    this->_width = width;
    this->_data.resize(this->_height);
    this->_data[0].resize(this->_width, false);

    int position=0;
    int available=this->_width-position;
    while(available>0){
        int max_jump;
        if(available>maxJump){
            max_jump=maxJump;
        }else{
            max_jump=available;
        }
        //Put rand gap from 0 to available
        int jump = rand() % (max_jump-minJump +1)+minJump;
        int newPosition=position+jump;
        for(int i=position;i<=newPosition-1;i++){
            this->_data[0][i]=7;
        }
        position=newPosition;
        available=this->_width-position;
        if(available==0){
            break;
        }


        //Put a rest
        int max_rest;
        if(available>maxRest){
            max_rest=maxRest;
        }else{
            max_rest=available;
        }
        int rest = rand() % (max_rest-minRest +1)+minRest;
        newPosition=position+rest;
        position=newPosition;
        available=this->_width-position;

    }


}
Structures::
GapStructure::GapStructure(unsigned short int p_width,unsigned short int p_max_jump,unsigned short int p_min_jump,unsigned short int p_min_rest,unsigned short int p_max_rest ) : Structures::BaseStructure()
{
    int width=p_width;
    int minJump=p_min_jump;
    int maxJump=p_max_jump;
    int minRest=p_min_rest;
    int maxRest=p_max_rest;

    this->_height = 1;
    this->_width = width;
    this->_data.resize(this->_height);
    this->_data[0].resize(this->_width, false);

    int position=0;
    int available=this->_width-position;
    while(available>0){
        int max_jump;
        if(available>maxJump){
            max_jump=maxJump;
        }else{
            max_jump=available;
        }
        //Put rand gap from 0 to available
        int jump = rand() % (max_jump-minJump +1)+minJump;
        int newPosition=position+jump;
        for(int i=position;i<=newPosition-1;i++){
            this->_data[0][i]=7;
        }
        position=newPosition;
        available=this->_width-position;
        if(available==0){
            break;
        }


        //Put a rest
        int max_rest;
        if(available>maxRest){
            max_rest=maxRest;
        }else{
            max_rest=available;
        }
        int rest = rand() % (max_rest-minRest +1)+minRest;
        newPosition=position+rest;
        position=newPosition;
        available=this->_width-position;

    }

}

