import { add, list } from "../../../db/dataManager"

const AcessToken = `:Pt/c'd>.6.wh-V5`


//Asks for a form to add data to database
export default async function handler(req, res) {

    switch (req.method) {

        case "POST": {
            const {acess, data} = req.body
            console.log(req.body)
            console.log(acess)

            if(acess === AcessToken)
            {
                if(data) 
                {
                    const { status, message } = await add(data)
                    res.status(status).json(message)
                }
                else
                {
                    res.status(400).json({message: "Mising parameters"})
                }
            }
            else 
            {
                res.status(403).json({message: "Acess Denied", status: 403})
            }
            break;
        }
        default : {
                res.status(405)
        }
    }
  }