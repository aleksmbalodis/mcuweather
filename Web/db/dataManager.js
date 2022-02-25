import mongoose from 'mongoose';
import connection from './connection';
const { Schema } = mongoose;

export const dataSchema = new Schema({
    date: Date,
    // time: Mixed,
    temperature: Number,
    humidity: Number,
    brightness: Number
})


const model = connection.model("data", dataSchema, "data")


export const add = async ({date, temperature, humidity, brightness}) => {

    if(!date || !temperature || !humidity || !brightness) return {status: 400, message: "Mising parameters"}

    try {
        await model.create({
            date,
            temperature,
            humidity,
            brightness
        })
        return {status: 200, message:"Data Uploaded"}
    }
    catch (err) {
        console.log(err)
        return {status: 500, message: "Unknown error"}
    }
    
}

export const list = async (date) =>
{
    if(date)
    {
        return await model.find({date:{$gte: date.from, $lte: date.to}})
    } else {
        return await model.find()
    }
}

export const remove = async (_id) => {
    try 
    {
        await model.deleteOne({_id})
        return {message: "Record deleted"}
    }
    catch (error)
    {
        console.log(error)
        return {message: "Deletion failed"}
    }
    
}