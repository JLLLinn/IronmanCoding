package com.Display.hopefullydisplaysomething;

import java.io.File;
import java.io.FileOutputStream;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.Display.hopefullydisplaysomething.displayList.AccSensorList;
import com.Display.hopefullydisplaysomething.displayList.LightSensorList;
import com.Display.hopefullydisplaysomething.handlers.AccDatabaseHandler;
import com.Display.hopefullydisplaysomething.handlers.LightDatabaseHandler;
import com.Display.hopefullydisplaysomething.sensors.Acc;
import com.Display.hopefullydisplaysomething.sensors.Light;

public class DisplayData extends Activity implements SensorEventListener{
	final static int OBSERVING=-1;
	final static int SAVING=1;
	private int observeMode=OBSERVING;
	TextView lightSensorView,accSensorView,oriSensorView,magSensorView;
	SensorManager sensorManager;
	Sensor lightSensor,accSensor,oriSensor,magSensor;
	//for saving data
	LightDatabaseHandler ldb= new LightDatabaseHandler(this);;
	AccDatabaseHandler adb= new AccDatabaseHandler(this);;
	float tempLight[];
	int lcurrentpos;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.show_sensors_data);//have to put this on the first row. But WHY??
		
		
		/*used for calculating average*/
		tempLight= new float[10];
		lcurrentpos=0;
		//
		sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);//sensor manager is the GOD of sensors!! haha
		lightSensorView = (TextView) findViewById(R.id.lightSensor);//initiate lightsensor textview
		accSensorView = (TextView) findViewById(R.id.accSensor);
		oriSensorView = (TextView) findViewById(R.id.oriSensor);
		magSensorView = (TextView) findViewById(R.id.magSensor);
		this.displayAvilableSensorData();//this would display the number of sensors and sensor names
		lightSensor = sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);
		accSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		oriSensor = sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
		magSensor = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
		
		File dbFile = getDatabasePath("AccSensorDatabaseManager");
		Log.i("hey!",dbFile.getAbsolutePath());
	}
	@Override
	protected void onResume(){
		super.onResume();
		sensorManager.registerListener(this,lightSensor,SensorManager.SENSOR_DELAY_NORMAL);
		sensorManager.registerListener(this,accSensor,SensorManager.SENSOR_DELAY_NORMAL);
		sensorManager.registerListener(this,magSensor,SensorManager.SENSOR_DELAY_NORMAL);
		sensorManager.registerListener(this,oriSensor,SensorManager.SENSOR_DELAY_NORMAL);
	}
	@Override
	protected void onPause() {
		super.onPause();
		sensorManager.unregisterListener(this);
		ldb.close();
		adb.close();
		//Log.d("hey!", "database closed");
	}
	
	@Override
	public void onSensorChanged(SensorEvent event){
		Sensor tempSen=event.sensor;
		if(this.observeMode==DisplayData.OBSERVING){
			switch(tempSen.getType()){
				case Sensor.TYPE_LIGHT:{ 
					float lux = event.values[0];
					lightSensorView.setText("Light Sensor Value: "+lux);
					break;
				}
				case Sensor.TYPE_ACCELEROMETER:{
					accSensorView.setText("Accelerometer Sensor Value: \n(x-axis)"+event.values[0]+"\n(y-axis) "+event.values[1]+"\n(z-axis) "+event.values[2]);
					break;
				}
				case Sensor.TYPE_GYROSCOPE:{
					oriSensorView.setText("GYROSCOPE Vector Sensor Value (rad/s): \n(x-axis)"+event.values[0]+"\n(y-axis) "+event.values[1]+"\n(z-axis) "+event.values[2]);
					break;
				}
				case Sensor.TYPE_MAGNETIC_FIELD:{
					magSensorView.setText("Magnetic Field Sensor Value: \n(x-axis)"+event.values[0]+"\n(y-axis) "+event.values[1]+"\n(z-axis) "+event.values[2]);
					break;
				}
				default:{
					lightSensorView.setText("SOMETHING GOES WRONG");
					break;
				}
			}
		}else{
			if(this.observeMode==DisplayData.SAVING){
				switch(tempSen.getType()){
				case Sensor.TYPE_LIGHT:{
					float lux = event.values[0];
					lightSensorView.setText("Light Sensor Value: "+lux);
					ldb.addLight(new Light (lux));
					/*if(lcurrentpos<9){
						tempLight[lcurrentpos]=lux;
					}else{//calculate the average of 10 consecutive values
						float sum = 0;
						for(int i=0; i<10;i++)
							sum+=tempLight[i];
						float avg = sum/10;
						ldb.addLight(new Light (avg));
						lcurrentpos=0;//set it back to 0
					}*/
					break;
				}
				case Sensor.TYPE_ACCELEROMETER:{
					accSensorView.setText("Accelerometer Sensor Value: \n(x-axis)"+event.values[0]+"\n(y-axis) "+event.values[1]+"\n(z-axis) "+event.values[2]);
					adb.addAcc(new Acc(event.values[0],event.values[1],event.values[2]));
					//Log.d("ACC", "Hey!!!");
					break;
				}
				case Sensor.TYPE_GYROSCOPE:{
					oriSensorView.setText("GYROSCOPE Vector Sensor Value (rad/s): \n(x-axis)"+event.values[0]+"\n(y-axis) "+event.values[1]+"\n(z-axis) "+event.values[2]);
					
					break;
				}
				case Sensor.TYPE_MAGNETIC_FIELD:{
					magSensorView.setText("Magnetic Field Sensor Value: \n(x-axis)"+event.values[0]+"\n(y-axis) "+event.values[1]+"\n(z-axis) "+event.values[2]);
					
					break;
				}
				default:{
					lightSensorView.setText("SOMETHING GOES WRONG");
					break;
				}
			}
			}
		}
	}
	private void displayAvilableSensorData(){
		TextView sensorNumberView = (TextView) findViewById(R.id.sensorNumber);
		TextView sensorListView = (TextView) findViewById(R.id.sensorList);
		
	
		List<Sensor> sensorList = sensorManager.getSensorList(Sensor.TYPE_ALL);//store the sensor list in a List
		
		sensorNumberView.setText("Currently "+sensorList.size()+" sensors are available");
		
		
		if (sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT) != null){
			  System.out.println("Success! There's a LIGHT SENSOR: "+sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT).getName());
		}else {
			  System.out.println("Failure! No LIGHT SENSOR.");
		}

		if(sensorList.size()>0){
			String sensorListString = "\n";
			Sensor temp; //"temp" is a sensor
			for(int i=0;i<sensorList.size();i++){
				temp = sensorList.get(i);//get the sensor out of the list and store in temp
				sensorListString = sensorListString+temp.getName();
				sensorListString = sensorListString + "\n";
			}
			sensorListView.setText("Sensor List:"+sensorListString);
		}else{
			sensorListView.setText("Sensor List: No Sensors Available");
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	@Override
	public void onAccuracyChanged(Sensor arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}

	
	@Override
	public void onStop(){
		super.onStop();
		//this.deleteDatabase(LightDatabaseHandler.DATABASE_NAME);//start a NEW database every time the app is invoked again
		//Log.d("hey","database deleted");
	}
	
	//called when the saveData button clicked
	public void saveData(View view) {
		Button but = (Button) findViewById(R.id.saveorcancel);
		this.observeMode=0-this.observeMode;
		if(this.observeMode==OBSERVING){
			Toast toast = Toast.makeText(this, "Now Observing", Toast.LENGTH_SHORT);
			toast.show();
			but.setText("Click to Save");
		}else if(this.observeMode==SAVING){
			Toast toast = Toast.makeText(this, "Now Saving Data", Toast.LENGTH_SHORT);
			toast.show();
			but.setText("Click to Observe");
		}
		
	}
	public void displayLight(View view) {
		Intent intent = new Intent(this, LightSensorList.class);
		startActivity(intent);
	}
	public void displayAcc(View view) {
		Intent intent = new Intent(this, AccSensorList.class);
		startActivity(intent);
	}
	
}
