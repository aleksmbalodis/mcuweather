import mongoose from 'mongoose'

const connect = 'mongodb+srv://Maid-Bot:6jnkR6ugqJcxci5f@cluster0.njiyf.mongodb.net/mcuweather'

export default mongoose.createConnection(connect,{
    useNewUrlParser: true,
    useUnifiedTopology: true
})