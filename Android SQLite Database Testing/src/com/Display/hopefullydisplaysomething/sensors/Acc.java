package com.Display.hopefullydisplaysomething.sensors;

public class Acc {
	 //private variables
    int _id;
    float _value_x;
    float _value_y;
    float _value_z;
    
    
    public Acc(int id, float _value_x,float _value_y,float _value_z){
        this._id = id;
        this._value_x = _value_x;
        this._value_y = _value_y;
        this._value_z = _value_z;
    }
    
    public Acc(float _value_x,float _value_y,float _value_z){
        this._value_x = _value_x;
        this._value_y = _value_y;
        this._value_z = _value_z;
    }
    
	// getting ID
    public int getID(){
        return this._id;
    }
    // setting id
    public void setID(int id){
        this._id = id;
    }    
	// getting value
    public float getValueX(){
        return this._value_x;
    }
    public float getValueY(){
        return this._value_y;
    }
    public float getValueZ(){
        return this._value_z;
    }
    // setting value
    public void setValueX(float value_x){
        this._value_x = value_x;
    }
    public void setValueY(float value_y){
        this._value_y = value_y;
    }   
    public void setValueZ(float value_z){
        this._value_z = value_z;
    }   
}
