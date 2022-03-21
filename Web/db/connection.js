var mongoose = require('mongoose')

const connect = 'mongodb+srv://Maid-Bot:6jnkR6ugqJcxci5f@cluster0.njiyf.mongodb.net/mcuweather'



var conn = () => {
    // console.log(mongoose)
    return mongoose.createConnection(connect, {
        useNewUrlParser: true
    });  
} 

export default conn