/**
 * This class is responsible for a Light Sensor Database.
 * This class can only handle ONE database
 * It would uses the Light class to manipulate datas
 */

package com.Display.hopefullydisplaysomething.handlers;

import java.util.ArrayList;
import java.util.List;

import com.Display.hopefullydisplaysomething.sensors.Light;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class LightDatabaseHandler  extends SQLiteOpenHelper{
	// All Static variables
    // Database Version
    private static final int DATABASE_VERSION = 1;
 
    // Database Name
    public static final String DATABASE_NAME = "LightSensorDatabaseManager";
 
    // Contacts table name
    private static final String TABLE_CONTACTS = "LightDatas";
 
    // Contacts Table Columns names
    private static final String KEY_ID = "id";
    private static final String KEY_VALUE = "value";
    
    
    public LightDatabaseHandler(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // Creating Tables, REAL is for float
    @Override
    public void onCreate(SQLiteDatabase db) {
        String CREATE_CONTACTS_TABLE = "CREATE TABLE " + TABLE_CONTACTS + "("
                + KEY_ID + " INTEGER PRIMARY KEY," + KEY_VALUE + " REAL" + ")";
        db.execSQL(CREATE_CONTACTS_TABLE);
    }

    // Upgrading database
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Drop older table if existed
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_CONTACTS);
 
        // Create tables again
        onCreate(db);
    }
    
    /* All CRUD(Create, Read, Update, Delete) Operations
    */

   // Adding new light to database
   public void addLight(Light light) {
       SQLiteDatabase db = this.getWritableDatabase();

       ContentValues values = new ContentValues();
       values.put(KEY_VALUE, light.getValue()); // value of the light sensor

       // Inserting Row
       db.insert(TABLE_CONTACTS, null, values);
       db.close(); // Closing database connection
   }
   
   // Getting single contact
   public Light getLight(int id) {
       SQLiteDatabase db = this.getReadableDatabase();

       Cursor cursor = db.query(TABLE_CONTACTS, new String[] { KEY_ID,KEY_VALUE}, KEY_ID + "=?",
               new String[] { String.valueOf(id) }, null, null, null, null);
       if (cursor != null)
           cursor.moveToFirst();

       Light light = new Light(Integer.parseInt(cursor.getString(0)), cursor.getFloat(1));//assuming that 0 and 1 are the index of id and value
       // return contact
       return light;
   }
   
   // Getting All light sensor values
   public List<Light> getAllLights() {
       List<Light> lightList = new ArrayList<Light>();
       // Select All Query
       String selectQuery = "SELECT  * FROM " + TABLE_CONTACTS;

       SQLiteDatabase db = this.getWritableDatabase();
       Cursor cursor = db.rawQuery(selectQuery, null);

       // looping through all rows and adding to list
       if (cursor.moveToFirst()) {
           do {
               Light light = new Light(Integer.parseInt(cursor.getString(0)), cursor.getFloat(1));
               // Adding contact to list
               lightList.add(light);
           } while (cursor.moveToNext());
       }

       // return contact list
       return lightList;
   }
   
   
   

}
