/**
 * This class maintains a data type : light sensor data
 */
package com.Display.hopefullydisplaysomething.sensors;

public class Light {
	 //private variables
    int _id;
    float _value;
    
    public Light(int id, float _value){
        this._id = id;
        this._value = _value;
    }
    
    public Light(float _value){
        this._value = _value;
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
    public float getValue(){
        return this._value;
    }
    // setting id
    public void setValue(float value){
        this._value = value;
    }    
}
