import { add } from "../../../db/dataManager"


const AcessToken = `:Pt/c'd>.6.wh-V5`


export default function handler(req, res) {
    
    if (req.method === "POST")
    {
        const {Token, data} = req.body
        console.log(Token)

        if(Token === AcessToken)
        {
            if(data) 
            {
                const { status, message } = add(data)
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
    } else 
    {
        res.status(404).json({message: "Request not found", status: 404})
    }
  }