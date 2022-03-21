import { add, list } from "../../../db/dataManager"
import { validateDate } from "../../../components/regex"


export default async function handler(req, res) {
  
  if(req.method === "GET")
  {
    const { date } = req.query
    console.log(validateDate(date[0]))  ///Remove later
    if(!validateDate(date[0]) || !validateDate(date[1])) res.status(400).json({Message:"Error queriying"}) //Validates Query dates
    let data = await list({from: date[0], to: date[1]}) //filters data
    // console.log(data)
    res.status(200).json(data)// return data as result
  }
  else {
    res.status(403) // calls a bad request
  }
    
  }

