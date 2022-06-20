var mongoose = require('mongoose')

const connect = ''



var conn = () => {
    // console.log(mongoose)
    //Server connection
    return mongoose.createConnection(connect, {
        useNewUrlParser: true
    });  
} 
//exports as module
export default conn