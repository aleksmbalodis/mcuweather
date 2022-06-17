var mongoose = require('mongoose')

const connect = 'mongodb+srv://Maid-Bot:6jnkR6ugqJcxci5f@cluster0.njiyf.mongodb.net/mcuweather'



var conn = () => {
    // console.log(mongoose)
    //Server connection
    return mongoose.createConnection(connect, {
        useNewUrlParser: true
    });  
} 
//exports as module
export default conn