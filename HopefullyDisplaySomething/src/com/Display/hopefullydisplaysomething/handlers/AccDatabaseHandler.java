package com.Display.hopefullydisplaysomething.handlers;

import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import com.Display.hopefullydisplaysomething.sensors.Acc;

public class AccDatabaseHandler extends SQLiteOpenHelper{
	// All Static variables
    // Database Version
    private static final int DATABASE_VERSION = 2;
 
    // Database Name
    public static final String DATABASE_NAME = "AccSensorDatabaseManager";
 
    // Contacts table name
    private static final String TABLE_CONTACTS = "AccDatas";
 
    // Contacts Table Columns names
    private static final String KEY_ID = "id";
    private static final String KEY_VALUE_X = "value_x";
    private static final String KEY_VALUE_Y = "value_y";
    private static final String KEY_VALUE_Z = "value_z";
    
    
    public AccDatabaseHandler(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // Creating Tables, REAL is for float
    @Override
    public void onCreate(SQLiteDatabase db) {
        String CREATE_CONTACTS_TABLE = "CREATE TABLE " + TABLE_CONTACTS + "("
                + KEY_ID + " INTEGER PRIMARY KEY," + KEY_VALUE_X + " REAL," + KEY_VALUE_Y + " REAL," +  KEY_VALUE_Z + " REAL"+");";
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

   // Adding new Acc to database
   public void addAcc(Acc acc) {
       SQLiteDatabase db = this.getWritableDatabase();

       ContentValues values = new ContentValues();
       values.put(KEY_VALUE_X, acc.getValueX()); // value of the acc sensor
       values.put(KEY_VALUE_Y, acc.getValueY());
       values.put(KEY_VALUE_Z, acc.getValueZ());

       // Inserting Row
       db.insert(TABLE_CONTACTS, null, values);
       db.close(); // Closing database connection
   }
   
   // Getting single contact
   public Acc getAcc(int id) {
       SQLiteDatabase db = this.getReadableDatabase();

       Cursor cursor = db.query(TABLE_CONTACTS, new String[] { KEY_ID,KEY_VALUE_X,KEY_VALUE_Y,KEY_VALUE_Z}, KEY_ID + "=?",
               new String[] { String.valueOf(id) }, null, null, null, null);
       if (cursor != null)
           cursor.moveToFirst();

       Acc acc = new Acc(Integer.parseInt(cursor.getString(0)), cursor.getFloat(1), cursor.getFloat(2),cursor.getFloat(3));//assuming that 0 and 1 are the index of id and value
       // return contact
       return acc;
   }
   
   // Getting All acc sensor values
   public List<Acc> getAllAccs() {
       List<Acc> accList = new ArrayList<Acc>();
       // Select All Query
       String selectQuery = "SELECT  * FROM " + TABLE_CONTACTS;

       SQLiteDatabase db = this.getWritableDatabase();
       Cursor cursor = db.rawQuery(selectQuery, null);

       // looping through all rows and adding to list
       if (cursor.moveToFirst()) {
           do {
               Acc acc = new Acc(Integer.parseInt(cursor.getString(0)), cursor.getFloat(1), cursor.getFloat(2),cursor.getFloat(3));
               // Adding the row to list
               accList.add(acc);
           } while (cursor.moveToNext());
       }

       // return contact list
       return accList;
   }
   
}
