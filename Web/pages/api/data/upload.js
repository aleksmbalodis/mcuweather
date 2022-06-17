import { add, list } from "../../../db/dataManager"

const AcessToken = `:Pt/c'd>.6.wh-V5`


//Asks for a form to add data to database
export default async function handler(req, res) {

    switch (req.method) {

        case "POST": {
            //deconstructs access and data from request body
            const {acess, data} = req.body
            // console.log(req.body)
            // console.log(acess)

            //check if access token is correct before proceeding
            if(acess === AcessToken)
            {
                //check if data is present
                if(data) 
                {
                    const { status, message } = await add(data)
                    res.status(status).json(message)
                }
                //returns error if data isnt defined
                else
                {
                    res.status(400).json({message: "Mising parameters"})
                }
            }
            //returns error if access code is incorrect
            else 
            {
                res.status(403).json({message: "Acess Denied", status: 403})
            }
            break;
        }
        default : {
            //returns error message
                res.status(405)
        }
    }
  }