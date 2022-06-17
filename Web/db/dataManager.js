import mongoose from 'mongoose';
import conn from './connection';
const { Schema } = mongoose;

//schema created for storing data
export const dataSchema = new Schema({
    date: Date,
    temperature: Number,
    humidity: Number,
    brightness: Number
})

//creates a connection module which saves data in data table
const model = conn().model("data", dataSchema, "data")

//creates a new row in database
export const add = async ({date, temperature, humidity, brightness}) => {

    //Checks if data collumns are valid 
    if(!date || !temperature || !humidity || !brightness) return {status: 400, message: "Mising parameters"}

    try {
        //Creates a row for database before uploading
        await model.create({
            date,
            temperature,
            humidity,
            brightness
        })
        return {status: 200, message:"Data Uploaded"}
    }
    //catches error and returns it to client
    catch (err) {
        console.log(err)
        return {status: 500, message: "Unknown error"}
    }
    
}

//returns filtered or not filtered array of data from database
export const list = async (filter) =>
{
    var data
    //checks if filter object is populated
    if (filter) {
        //queries database for the filter data
        data = await model.find({ date: {
            $gte: filter.from,
            $lt: filter.to
        }})
    } 
    else {
        //returns whole table without filter
        data = await model.find({})
    }

    
    //returns final data
    return JSON.stringify(data)
    
}

//removes selected row
export const remove = async (_id) => {
    try 
    {
        //Deletes chosen row
        await model.deleteOne({_id})
        return {message: "Record deleted"}
    }
    catch (error)
    {
        //upon error message is returned
        console.log(error)
        return {message: "Deletion failed"}
    }
    
}