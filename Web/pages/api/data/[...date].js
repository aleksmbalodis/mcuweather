export default function handler(req, res) {
    const { date } = req.query

    console.log(date)

    res.json({Post: date.join(', ')})
  }