/**
 * This activity is responsible for display a light sensor database
 */

package com.Display.hopefullydisplaysomething.displayList;

import java.util.List;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.TextView;

import com.Display.hopefullydisplaysomething.R;
import com.Display.hopefullydisplaysomething.handlers.LightDatabaseHandler;
import com.Display.hopefullydisplaysomething.sensors.Light;

public class LightSensorList extends Activity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_light_sensor_list);
	}
	
	@Override
	protected void onResume(){
		super.onResume();
		TextView lightDataList = (TextView)findViewById(R.id.lightDataList);
		LightDatabaseHandler ldb = new LightDatabaseHandler (this);
		List<Light> temp = ldb.getAllLights();
		long size = temp.size();
		if(size>0){
			String LightListString = "\n";
			Light lig; //"lig" is a temp Light objest
			for(int i=0;i<size;i++){
				lig = temp.get(i);//get the sensor out of the list and store in temp
				LightListString = LightListString+lig.getValue();
				LightListString = LightListString + "\n";
			}
			lightDataList.setText("Sensor List:"+LightListString);
		}
		ldb.close();

	}
	
	@Override 
	protected void onPause(){
		super.onPause();
		
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_light_sensor_list, menu);
		return true;
	}

}
