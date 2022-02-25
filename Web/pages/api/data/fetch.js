import { list } from "../../../db/dataManager"


export default async function handler(req, res) {
    
    if (req.method === "POST")
    {
        // console.log(req.body)
        const { status, data } = await list(req.body)

        res.status(status).json(data)
        
    } else 
    {
        res.status(400).json({message: "Bad Request", status: 400})
    }
  }