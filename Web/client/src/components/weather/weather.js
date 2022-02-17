import React, {useState, useEffect} from 'react'
import "./weather.css"

export default function Weather() {
    const [error, setError] = useState(null);
    const [isLoaded, setIsLoaded] = useState(false);
    const [weather, setWeather] = useState([]);

    useEffect(() => {
        fetch('/api/weather')
            .then(res => {
                res.json().then(json => console.log(json))
            })
            .then(
                (result) => {   
                    setIsLoaded(true);
                    setWeather(result);
                    console.log(result)
                },
                (error) => {
                    setIsLoaded(true);
                    setError(error);
                    
                }
            )
    }, [])
    
    if (error) {
        return <div>Error: {error.message}</div>
    }  else if (!isLoaded) {
        return <div>Loading...</div>
    } else {
        return (
            <ul>
                {console.log(weather)}
                {weather.map(item => (
                    <li key={item.date}>
                        {item.date} {item.temperature} {item.humidity}
                    </li>
                ))}
            </ul>
        )
    }
}
