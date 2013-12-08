package com.Display.hopefullydisplaysomething.displayList;

import java.util.List;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.TextView;

import com.Display.hopefullydisplaysomething.R;
import com.Display.hopefullydisplaysomething.handlers.AccDatabaseHandler;
import com.Display.hopefullydisplaysomething.sensors.Acc;

public class AccSensorList extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_acc_sensor_list);
	}
	
	@Override
	protected void onResume(){
		super.onResume();
		TextView accDataList = (TextView)findViewById(R.id.accDataList);
		AccDatabaseHandler ldb = new AccDatabaseHandler (this);
		List<Acc> temp = ldb.getAllAccs();
		long size = temp.size();
		if(size>0){
			String AccListString = "\n";
			Acc lig; //"lig" is a temp Acc objest
			for(int i=0;i<size;i++){
				lig = temp.get(i);//get the sensor out of the list and store in temp
				AccListString = AccListString+"x: "+lig.getValueX()+" y: "+lig.getValueY()+" z: "+lig.getValueZ();
				AccListString = AccListString + "\n";
			}
			accDataList.setText("Sensor List:"+AccListString);
		}
		ldb.close();

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_acc_sensor_list, menu);
		return true;
	}

}
