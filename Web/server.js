const express = require('express');

const app = express();

app.get('/api/weather', (req, res) => {
    const weather = { weather: [
        {date: 22, temperature: 22, humidity: 80},
        {date: 23, temperature: 18, humidity: 60},
        {date: 24, temperature: 15, humidity: 50}
    ]
};

    res.json(weather);
});

const port = 5001;

app.listen(port, () => console.log(`Server started on port ${port}`))