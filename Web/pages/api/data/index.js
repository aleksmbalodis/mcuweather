import { add, list } from "../../../db/dataManager"

export default async function handler(req, res) {

    switch (req.method) {

        //returns full list of data
        case "GET": {
            const data = await list()
            // console.log(data)
            //returns data
            res.status(200).json(data)
            break;
        } 
        default : {
            //return error
                res.status(405)
        }
    }
  }