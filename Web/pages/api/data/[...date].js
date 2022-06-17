import { add, list } from "../../../db/dataManager"
import { validateDate } from "../../../components/regex"


export default async function handler(req, res) {
  
  if(req.method === "GET")
  {
    //deconstructs date element from whole query
    const { date } = req.query
    // console.log(validateDate(date[0]))  ///Remove later
     //Validates Query dates
    if(!validateDate(date[0]) || !validateDate(date[1])) res.status(400).json({Message:"Error queriying"})
    //filters data
    let data = await list({from: date[0], to: date[1]}) 
    // console.log(data)
    // return data as result
    res.status(200).json(data)
  }
  else {
    // calls a bad request
    res.status(403) 
  }
    
  }

